/******************************************************************************
 *
 *  File Name   : Eval5.cpp
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

/*
 * Routine to test the Jacks or Better evaluator by looping over all 2,598,960 
 * possible five card hands and calculating each hand's distinct value and 
 * displaying the frequency count of each hand type.
 */

#include <iostream>
#include <iomanip>
#include <string>
#include "PlayingCardDeck.h"
#include "JBEvaluator.h"
#include "PlayingCard.h"
#include "IEvaluator.h"

using namespace std;

int main()
{    
    // Create deck of cards
    int* deck = PlayingCardDeck::deckOfCards();
    
    // Array for frequency counts
    int freq[10];
    for (int i = 0; i < 10; i++)
        freq[i] = 0;

    // Evaluate all 5 card hands    
    int hand[5];
    IEvaluator* evaluator = new JBEvaluator();
    for (int a = 0; a < 48; a++) {
        hand[0] = deck[a];
        for (int b = a+1; b < 49; b++) {
            hand[1] = deck[b];
            for (int c = b+1; c < 50; c++) {
                hand[2] = deck[c];
                for (int d = c+1; d < 51; d++) {
                    hand[3] = deck[d];
                    for (int e = d+1; e < 52; e++) {
                        hand[4] = deck[e];
                        int j = evaluator->evaluate(hand);
                        freq[j]++;
                    }
                }
            }
        }
    }
    

   string hand_name[] = { "Nothing:", "Royal Flush:", "Straight Flush:", 
                         "Four of a Kind:", "Full House:", "Flush", 
                         "Straight:", "Three of a Kind:", "Two Pair:", 
                         "Jacks or Better:"
                        };

    // Display results
    int sum = 0;
    cout << "-------------------------" << endl;
    cout << "Results" << endl;
    cout << "-------------------------" << endl;
    cout << setfill(' ');
    for (int i = 0; i < 10; i++) {
        sum += freq[i];
        cout << setw(17) << hand_name[i] << setw(8) << freq[i] << endl;
    }
    cout << "-------------------------" << endl;
    cout << setw(17) << "Total:" << setw(8) << sum << endl;
    
    // Cleanup
    delete deck;
    delete evaluator;
    
    return 0;
}

