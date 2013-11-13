/******************************************************************************
 *
 *  File Name   : Analyze5.cpp
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
 * Routine to test HandAnalysis. Draws a random hand and analyzes the best
 * hold for the given hand.
 */

#include <iostream>
#include <iomanip>
#include <string>
#include <map>
#include "HandAnalysis.h"
#include "IEvaluator.h"
#include "JBEvaluator.h"
#include "PlayingCardDeck.h"
#include "PlayingCard.h"
#include "DWEvaluator.h"

using namespace std;

int main()
{
   /*
    * Jacks or Better
    */
    
    // Jacks or Better full pay
    const map<int,int> paytable_9_6 = {
        { JBEvaluator::NO_HAND,         0   },
        { JBEvaluator::ROYAL_FLUSH,     800 },
        { JBEvaluator::STRAIGHT_FLUSH,  50  },
        { JBEvaluator::FOUR_OF_A_KIND,  25  },
        { JBEvaluator::FULL_HOUSE,      9   },
        { JBEvaluator::FLUSH,           6   },
        { JBEvaluator::STRAIGHT,        4   },
        { JBEvaluator::THREE_OF_A_KIND, 3   },
        { JBEvaluator::TWO_PAIR,        2   },
        { JBEvaluator::JACKS_OR_BETTER, 1   }
    };

    IEvaluator* evaluator = new JBEvaluator();
    HandAnalysis analyzer(evaluator, &paytable_9_6);

   /*
    * Deuces Wild
    */

    // // Deuces Wild full pay
    // const map<int, int> paytable_decues = {
    //     { DWEvaluator::NO_HAND,             0   },
    //     { DWEvaluator::NATURAL_ROYAL_FLUSH, 800 },
    //     { DWEvaluator::FOUR_DEUCES,         200 },
    //     { DWEvaluator::WILD_ROYAL_FLUSH,    25  },
    //     { DWEvaluator::FIVE_OF_A_KIND,      15  },
    //     { DWEvaluator::STRAIGHT_FLUSH,      9   },
    //     { DWEvaluator::FOUR_OF_A_KIND,      5   },
    //     { DWEvaluator::FULL_HOUSE,          3   },
    //     { DWEvaluator::FLUSH,               2   },
    //     { DWEvaluator::STRAIGHT,            2   },
    //     { DWEvaluator::THREE_OF_A_KIND,     1   }
    // };
    // 
    // IEvaluator* evaluator = new DWEvaluator();
    // HandAnalysis analyzer(evaluator, &paytable_decues);
    
    // Init deck of card and shuffle
    int* deck = PlayingCardDeck::deckOfCards();
    PlayingCardDeck::shuffle(deck);
    
    // Choose top five cards of deck as your starting poker hand
    int hand[] = { deck[0], deck[1], deck[2], deck[3], deck[4] };
    cout << "My hand is ";
    PlayingCard::printHand(hand, 5);

    // Calculate all expected values
    map<vector<int>, double> evs = analyzer.handEVs(hand);
    for (pair<vector<int>, double> kvPair : evs) {
        cout << analyzer.holdDescription(hand, get<0>(kvPair));
        cout << "\tExpected Value: " << get<1>(kvPair) << endl;
    }
    
    // What's the best hold?
    vector<int> bestHold = analyzer.bestHold(hand);
    cout << endl << "The best hold is: ";
    cout << analyzer.holdDescription(hand, bestHold) << endl;
    
    delete [] deck;
    delete evaluator;

    return 0;
}
