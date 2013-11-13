/******************************************************************************
 *
 *  File Name   : Eval5Deuces.cpp
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
 * Routine to test the Deuces Wild evaluator by looping over all 2,598,960 
 * possible five card hands and calculating each hand's distinct value and 
 * displaying the frequency count of each hand type.
 */

#include <iostream>
#include <iomanip>
#include <string>
#include "PlayingCardDeck.h"
#include "IEvaluator.h"
#include "DWEvaluator.h"
#include "PlayingCard.h"

using namespace std;

int main()
{
    // Create deck of cards
    int* deck = PlayingCardDeck::deckOfCards();
    
    // Array to hold frequency count of all ranked hands
    int freq[11];
    for (int i = 0; i < 11; i++)
        freq[i] = 0;
    
    // Evaluate all 5 card hands
    int hand[5];
    IEvaluator* evaluator = new DWEvaluator();
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

    string hand_name[] = { "Nothing:", "Natural Royal Flush:", "Four Deuces",
        "Royal Flush", "Five of a Kind", "Straight Flush",
        "Four of a Kind", "Full House", "Flush", "Straight",
        "Three of a Kind"
    };

    // Output the results
    int sum = 0;
    cout << "------------------------------" << endl;
    cout << "Results" << endl;
    cout << "------------------------------" << endl;
    cout << setfill(' ');
    for (int i = 0; i < 11; i++) {
        sum += freq[i];
        cout << setw(20) << hand_name[i] << setw(10) << freq[i] << endl;
    }
    cout << "------------------------------" << endl;
    cout << setw(20) << "Total:" << setw(10) << sum << endl;
    
    // Cleanup
    delete deck;
    delete evaluator;
    
    return 0;
}

