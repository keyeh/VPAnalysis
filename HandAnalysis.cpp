/******************************************************************************
 *
 *  File Name   : HandAnalysis.cpp
 *
 *  Created By  : Niral Bhalodia
 *
 *  Copyright (c) 2013 Niral Bhalodia. All rights reserved.
 *
 *  This is free software. Permission is granted to redistribute and/or modify
 *  this code under the terms of the MIT License as published by opensource.org.
 *  This software is provided without warranty.
 *
 ******************************************************************************/

#include "HandAnalysis.h"
#include "PlayingCardDeck.h"
#include <math.h>
#include <vector>
#include "JBEvaluator.h"
#include "PlayingCard.h"

using namespace std;

HandAnalysis::HandAnalysis(IEvaluator* evaluator, const map<int, int>* paytable)
{
    m_evaluator = evaluator;
    m_paytable = paytable;
    enumerateHoldMasks();
};


HandAnalysis::~HandAnalysis()
{
    //...
};


void HandAnalysis::enumerateHoldMasks()
{
    int row = 32;
    int col = 5;
    for (int i = 0; i < row; i++) {
        vector<int> innerVec(col);
        m_holdMasks.push_back(innerVec);
    }

    // Enumerate all possible 32 masks 1 bit at a time. This loop
    // expoloits the symmetry of vector to be assembled by the end.
    // Resulting output of the loop will be a fully enumerated vector
    // m_holdMasks with values: 00000, 00001, 00010, 00011, 00100, etc...
    for (int position = 0; position < 5; position++) {
        int partition = (int) pow(2, (5 - position - 1));
        for (int i = 0; i < partition; i++) {
            int binaryDigit = 0;
            for (int j = i; j < 32; j+= partition) {
                m_holdMasks[j][position] = binaryDigit;
                binaryDigit ^= 1;
            }
        }
    }
};


const vector<vector<int> > & HandAnalysis::getHoldMasks()
{
    return m_holdMasks;
};


/*
 * Given a hand and which cards to hold, return all possible hands that can be
 * drawn. This accounts for elimination of dead cards.
 * 
 * Parameters:
 *      hand (int*) - five card poker hand to fill based on held cards
 *
 *      holdMask (vector<int>) - cards to hold in hand
 *
 * Returns:
 *      Vector of vectors where each inner vector represnts a possible drawn
 *      hand.
 */
vector<vector<int> > HandAnalysis::fillHand(int* hand, vector<int> holdMask)
{
    int myHand[5]; // array of cards that have been held.
    int index = 0;
    for (int i = 0; i < 5; i++)
        if (holdMask[i])
            myHand[index++] = hand[i];

    // Create a new deck of cards and remove all dead cards (or cards in the
    // hand)
    vector<int> deck = PlayingCardDeck::vectorOfCards();
    for (int i = 0; i < 5; i++) {
        deck.erase(std::remove(deck.begin(), deck.end(), hand[i]), deck.end());
    }

    /*
     * Depending on the number of cards needed, enumerate the hand
     * approriately.
     */
    vector<vector<int> > hands;
    int cardsNeeded = 5 - index;
    if (cardsNeeded == 0) {
        hands.push_back({ myHand[0], myHand[1], myHand[2],
            myHand[3], myHand[4] });
    }
    else if (cardsNeeded == 1) {
        for (int a = 0; a < deck.size(); a++)
            hands.push_back({ myHand[0], myHand[1], myHand[2],
                myHand[3], deck[a] });
    }
    else if (cardsNeeded == 2) {
        for (int a = 0; a < deck.size() - 1; a++)
            for (int b = a+1; b < deck.size(); b++)
                hands.push_back({ myHand[0], myHand[1], myHand[2],
                    deck[a], deck[b] });
    }
    else if (cardsNeeded == 3) {
        for (int a = 0; a < deck.size() - 2; a++)
            for (int b = a+1; b < deck.size() - 1; b++)
                for (int c = b+1; c < deck.size(); c++)
                    hands.push_back({ myHand[0], myHand[1], deck[a],
                        deck[b], deck[c] });
    }
    else if (cardsNeeded == 4) {
        for (int a = 0; a < deck.size() - 3; a++)
            for (int b = a+1; b < deck.size() - 2; b++)
                for (int c = b+1; c < deck.size() - 1; c++)
                    for (int d = c+1; d < deck.size(); d++)
                        hands.push_back({ myHand[0], deck[a], deck[b],
                            deck[c], deck[d] });
    }
    else if (cardsNeeded == 5) {
        for (int a = 0; a < deck.size() - 4; a++)
            for (int b = a+1; b < deck.size() - 3; b++)
                for (int c = b+1; c < deck.size() - 2; c++)
                    for (int d = c+1; d < deck.size() - 1; d++)
                        for (int e = d+1; e < deck.size();  e++)
                            hands.push_back({ deck[a], deck[b], deck[c],
                                deck[d], deck[e] });
    }

    return hands;
};


double HandAnalysis::expectedReturn(int* hand, vector<int> holdMask)
{
    vector<vector<int> > possibleHands = fillHand(hand, holdMask);
    int newHand[5];
    double sum = 0.0;

    for (int i = 0; i < possibleHands.size(); i++) {
        int payout = m_paytable->at(m_evaluator->evaluate(&possibleHands[i][0]));
        sum += payout;
    }

    return sum / possibleHands.size();
};


vector<int> HandAnalysis::bestHold(int* hand)
{
    double maxEv = -1.0;
    int bestMaskIndex = -1;
    for (int i = 0; i < m_holdMasks.size(); i++) {
        double ev = expectedReturn(hand, m_holdMasks[i]);
        if (ev > maxEv) {
            maxEv = ev;
            bestMaskIndex = i;
        }
    }
    
    return m_holdMasks[bestMaskIndex];
};


string HandAnalysis::holdDescription(int* hand, vector<int> holdMask)
{
    string description = "";
    for (int i = 0; i < 5; i++) {
        if (holdMask[i]) {
            description += PlayingCard::cardDescription(hand[i]) + " ";
        } else {
            description += "-- ";
        }
    }
    
    return description;
};


map<vector<int>,double> HandAnalysis::handEVs(int* hand)
{
    map<vector<int>,double> evs;
    for (int i = 0; i < m_holdMasks.size(); i++) {
        evs[m_holdMasks[i]] = expectedReturn(hand, m_holdMasks[i]);
    }
    
    return evs;
};


map<vector<int>,vector<double> > HandAnalysis::fullAnalysis(int* hand)
{
    map<vector<int>,vector<double> > analysis;
    
    for (int i = 0; i < m_holdMasks.size(); i++) {
        vector<double> results(m_paytable->size() + 1, 0);
        vector<vector<int> > possibleHands = fillHand(hand, m_holdMasks[i]);
        double sum = 0.0;
        
        // go through all possible hands and keep count of each poker rank
        for (int j = 0; j < possibleHands.size(); j++) {
            int rank = m_evaluator->evaluate(&possibleHands[j][0]);
            double payout = m_paytable->at(rank);
            sum += payout;
            results[rank + 1]++;
        }
        
        // index 0 is the overall expected return
        results[0] = sum / possibleHands.size();
        analysis[m_holdMasks[i]] = results;
    }
    
    return analysis;
};

