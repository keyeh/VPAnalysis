/******************************************************************************
 *
 *  File Name   : PlayingCardDeck.h
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

#ifndef _PLAYINGCARDDECK_H
#define _PLAYINGCARDDECK_H

#include <vector>

using namespace std;

/*
 * A playing card deck. Includes functions to create a standard deck of playing
 * cards (excluding jokers). The functions create all 52 cards with traditional
 * suits and ranks as defined in PlayingCard.h.
 */
class PlayingCardDeck
{
    public:
        static const int TOTAL_CARDS;   // 52 cards in a standard deck
        
        /*
         * Creates all 52 standard cards found in a playing card deck, and
         * returns array of cards. Standard deck is 4 suits and 13 ranks.
         * 
         * Returns:
         *      Array of 52 cards
         */
        static int* deckOfCards();
        
        /*
         * Creates 52 card deck and returns a vector to represent the deck.
         *
         * Returns:
         *      Vector of 52 card masks
         */
        static vector<int> vectorOfCards();
        
        /*
         * A very basic shuffle that takes an array as argument and "shuffles"
         * the contents. The randomization algorithm used is the Knuth Shuffle.
         *
         * Parameters:
         *      cards (int *) - array of cards to shuffle
         */
        static void shuffle(int* cards);
};

#endif

