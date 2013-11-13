/******************************************************************************
 *
 *  File Name   : PlayingCard.cpp
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

#include "PlayingCard.h"
#include <iostream>
#include <set>
#include <map>
#include <string>

using namespace std;

const int TOTAL_RANKS = 13;
const int TOTAL_SUITS = 4;

const int PlayingCard::DEUCE    = 0x0001;
const int PlayingCard::TREY     = 0x0002;
const int PlayingCard::FOUR     = 0x0004;
const int PlayingCard::FIVE     = 0x0008;
const int PlayingCard::SIX      = 0x0010;
const int PlayingCard::SEVEN    = 0x0020;
const int PlayingCard::EIGHT    = 0x0040;
const int PlayingCard::NINE     = 0x0080;
const int PlayingCard::TEN      = 0x0100;
const int PlayingCard::JACK     = 0x0200;
const int PlayingCard::QUEEN    = 0x0400;
const int PlayingCard::KING     = 0x0800;
const int PlayingCard::ACE      = 0x1000;

const int PlayingCard::CLUB     = 0x080000;
const int PlayingCard::DIAMOND  = 0x040000;
const int PlayingCard::HEART    = 0x020000;
const int PlayingCard::SPADE    = 0x010000;

const set<int> PlayingCard::ALL_RANKS = {
    DEUCE, TREY, FOUR, FIVE, SIX, SEVEN,
    EIGHT, NINE, TEN, JACK, QUEEN, KING,
    ACE
};

const set<int> PlayingCard::ALL_SUITS = {
    CLUB, DIAMOND, HEART, SPADE
};

const map<int, string> PlayingCard::RANK_DESCRIPTIONS = {
    { DEUCE,    "2" },
    { TREY,     "3" },
    { FOUR,     "4" },
    { FIVE,     "5" },
    { SIX,      "6" },
    { SEVEN,    "7" },
    { EIGHT,    "8" },
    { NINE,     "9" },
    { TEN,      "T" },
    { JACK,     "J" },
    { QUEEN,    "Q" },
    { KING,     "K" },
    { ACE,      "A" }
};

const map<int, string> PlayingCard::SUIT_DESCRIPTIONS = {
    { CLUB,     "C" },
    { DIAMOND,  "D" },
    { HEART,    "H" },
    { SPADE,    "S" }
};

void PlayingCard::printHand(int* hand, int size)
{
    int rankMask = 0x0FFFF;
    int suitMask = 0xF0000;
    
    for (int i = 0; i < size; i++) {
        string rank = RANK_DESCRIPTIONS.at(hand[i] & rankMask);
        string suit = SUIT_DESCRIPTIONS.at(hand[i] & suitMask);
        cout << rank << suit << " ";
    }
    cout << endl;
};

string PlayingCard::cardDescription(int card)
{
    int rankMask = 0x0FFFF;
    int suitMask = 0xF0000;
    
    string rank = RANK_DESCRIPTIONS.at(card & rankMask);
    string suit = SUIT_DESCRIPTIONS.at(card & suitMask);
    
    return rank + suit;
};

