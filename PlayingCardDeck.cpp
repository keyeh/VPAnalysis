/******************************************************************************
 *
 *  File Name   : PlayingCardDeck.cpp
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

#include "PlayingCardDeck.h"
#include "PlayingCard.h"
#include <vector>

using namespace std;

const int PlayingCardDeck::TOTAL_CARDS = 52;

int* PlayingCardDeck::deckOfCards()
{
    int* cards = new int[TOTAL_CARDS];
    int i = 0;
    for (int suit : PlayingCard::ALL_SUITS)
        for (int rank : PlayingCard::ALL_RANKS)
            cards[i++] = suit | rank;
    return cards;
};

vector<int> PlayingCardDeck::vectorOfCards()
{
    vector<int> cards;
    for (int suit : PlayingCard::ALL_SUITS)
        for (int rank : PlayingCard::ALL_RANKS)
            cards.push_back(suit | rank);
    return cards;
};

// Knuth shuffle
void PlayingCardDeck::shuffle(int* cards)
{
   srand(time(NULL));
   for (int i = TOTAL_CARDS - 1; i >= 0; i--) {
       int j = rand() % (i + 1); // 0 <= j <= i
       int temp = cards[i];
       cards[i] = cards[j];
       cards[j] = temp;
    }
};
