/******************************************************************************
 *
 *  File Name   : JBEvaluator.cpp
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

#include "JBEvaluator.h"
#include "PlayingCard.h"
#include <set>
#include <iostream>

using namespace std;

const int JBEvaluator::NO_HAND          = 0;
const int JBEvaluator::ROYAL_FLUSH      = 1;
const int JBEvaluator::STRAIGHT_FLUSH   = 2;
const int JBEvaluator::FOUR_OF_A_KIND   = 3;
const int JBEvaluator::FULL_HOUSE       = 4;
const int JBEvaluator::FLUSH            = 5;
const int JBEvaluator::STRAIGHT         = 6;
const int JBEvaluator::THREE_OF_A_KIND  = 7;
const int JBEvaluator::TWO_PAIR         = 8;
const int JBEvaluator::JACKS_OR_BETTER  = 9;

// Hash values that indicate a straight has been acheived. More specifically
// if a hand hashes to one of these values, it is a sequential set of cards.
// This has does not differentiate between straights and straight flushes.
const set<int> JBEvaluator::m_straights = { 
    4111,31,62,124,248,496,992,1984,3968,7936
};

// Hash value for a royal flush
const int JBEvaluator::m_naturalRoyal = 7936;

JBEvaluator::JBEvaluator()
{
    m_flushHash = 0;
    m_straightHash = 0;
    m_hash4 = 0;
    m_hash3 = 0;
    m_hash2 = 0;
};

JBEvaluator::~JBEvaluator()
{
    //...
};

int JBEvaluator::evaluate(int* hand)
{
    // Suit and rank mask used to filter a card to get only repsective data
    int suitMask = 0xF0000;
    int rankMask = 0x0FFFF;
    
    // A flush is present if only all cards have the same suit. Thus, if this
    // hash is non-zero a flush is present.
    m_flushHash = (hand[0] & hand[1] & hand[2] & hand[3] & hand[4]) & suitMask;
    
    // Calculate the straight hash based on ranks only. Compare against
    // m_straights to see if the hand is a straight.
    m_straightHash = (hand[0] | hand[1] | hand[2] | hand[3] | hand[4]) & rankMask;

    // Hash for 4 of the same rank
    m_hash4 = 0;
    for (int a = 0; a < 2; a++)
        for (int b = a+1; b < 3; b++)
            for (int c = b+1; c < 4; c++)
                for (int d = c+1; d < 5; d++)
                    m_hash4 |= hand[a] & hand[b] & hand[c] & hand[d];
    m_hash4 &= rankMask;
    
    // Hash for 3 of the same rank
    m_hash3 = 0;
    for (int a = 0; a < 3; a++)
        for (int b = a+1; b < 4; b++)
            for (int c = b+1; c < 5; c++)
                m_hash3 |= hand[a] & hand[b] & hand[c];
    m_hash3 &= rankMask;

    // Hash for pairs of the same rank. Note if 1 bit is set in the hash, then
    // a pair exist. If n bits are set in the hash, then n pairs exist.
    m_hash2 = 0;
    for (int a = 0; a < 4; a++)
        for (int b = a+1; b < 5; b++)
            m_hash2 |= hand[a] & hand[b];
    m_hash2 &= rankMask;

    // Let's start the evaluation!
    return evalHand();
};

/*
 * Function must be only used after all hashes have been calculated. It uses
 * the member hashes to evalaute the hand passed into evalaute() last.
 * 
 * Returns:
 *      Hand ranking based on Jacks or Better rules.
 */
int JBEvaluator::evalHand()
{
    if (m_straights.find(m_straightHash) != m_straights.end() && m_flushHash) {
        if (m_straightHash == m_naturalRoyal)
            return ROYAL_FLUSH;
        else
            return STRAIGHT_FLUSH;
    }
    else if (m_hash4) {
        return FOUR_OF_A_KIND;
    }
    // A full house consists of a two pair and three of a kind
    else if (m_hash3 && numBits(m_hash2) == 2) {
        return FULL_HOUSE;
    }
    else if (m_flushHash) {
        return FLUSH;
    }
    else if (m_straights.find(m_straightHash) != m_straights.end()) {
        return STRAIGHT;
    }
    else if (m_hash3) {
        return THREE_OF_A_KIND;
    }
    else if (numBits(m_hash2) == 2) {
        return TWO_PAIR;
    }
    else if (m_hash2 >= PlayingCard::JACK) {
        return JACKS_OR_BETTER;
    }
    else {
        return NO_HAND;
    }
};

/*
 * Given an input n, get the number of bits set in n.
 * 
 * Parameters:
 *      n (int) - integer to count set bits
 *
 * Returns:
 *      Number of set bits in argument n.
 */
int JBEvaluator::numBits(int n)
{
    if (n)
        return (n & 0x1) + numBits(n >> 1);
    else
        return 0;
};
