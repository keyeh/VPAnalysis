/******************************************************************************
 *
 *  File Name   : PlayingCard.h
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

#ifndef _PLAYINGCARD_H
#define _PLAYINGCARD_H

#include <set>
#include <map>
#include <string>

using namespace std;

/*
 * A playing card class. Defines the standard 13 ranks and 4 suits used
 * is a playing card deck. A playingcard is an unique int mask to represent
 * said card. Any valid playingcard can be constructed by combining a
 * specific rank and suit via bitwise or. That is, a playing card is just
 * rank | suit. This class consists of essential constants needed to 
 * create a playing card mask.
 *
 * The representation of a PlayingCards bits is as follows:
 *
 *  +-------------------------------------------+
 *  | xxxxxxxx | xxxxCDHS | xxxAKQJT | 98765432 |
 *  +-------------------------------------------+
 *
 * where S = suit, R = rank, and x = irrelevant. Suit and rank bits are one-hot
 * coded exclusively.
 */
class PlayingCard 
{
    public:
        static const int TOTAL_RANKS;   // Number of ranks (13)
        static const int TOTAL_SUITS;   // Number of suits (4)
        
        /*
         * Ranks
         */
        static const int DEUCE;
        static const int TREY;
        static const int FOUR;
        static const int FIVE;
        static const int SIX;
        static const int SEVEN;
        static const int EIGHT;
        static const int NINE;
        static const int TEN;
        static const int JACK;
        static const int QUEEN;
        static const int KING;
        static const int ACE;
        
        /*
         * Suits
         */
        static const int CLUB;
        static const int DIAMOND;
        static const int HEART;
        static const int SPADE;
        
        // A collection of all (13) possible ranks of a standard deck
        static const set< int> ALL_RANKS;
        
        // A collection of all (4) standard suits of a playing card deck
        static const set< int> ALL_SUITS;
        
        // Single char description of ranks
        static const map< int, string> RANK_DESCRIPTIONS;
        
        // Single char suit description
        static const map< int, string> SUIT_DESCRIPTIONS;
        
        /*
         * Prints the entire description of a hand (or set of cards). Each
         * card is separated by a single whitespace.
         *
         * Parameters:
         *      hand (int*) - array of cardmasks
         *      size (int) - size of the array
         */
        static void printHand(int* hand, int size);
        
        /*
         * Given a card mask, print a 2-char string defining the playing
         * card.
         *
         * Returns:
         *      String representation of hand. (C++ string)
         */
        static string cardDescription(int card);
};

#endif

