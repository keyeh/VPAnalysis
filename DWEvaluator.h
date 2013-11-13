/******************************************************************************
 *
 *  File Name   : DWEvaluator.h
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

#ifndef _DWEVALUATOR_H
#define _DWEVALUATOR_H

#include "IEvaluator.h"
#include <vector>
#include <map>

using namespace std;

/*
 * A Deuces Wild video poker evaluator. Simply create an instance and use the
 * evaluate function to evaluate hands.
 */
class DWEvaluator : public IEvaluator
{  
    public:
        /*
         * All possible hands
         */
        static const int NO_HAND;
        static const int NATURAL_ROYAL_FLUSH;
        static const int FOUR_DEUCES;
        static const int WILD_ROYAL_FLUSH;
        static const int FIVE_OF_A_KIND;
        static const int STRAIGHT_FLUSH;
        static const int FOUR_OF_A_KIND;
        static const int FULL_HOUSE;
        static const int FLUSH;
        static const int STRAIGHT;
        static const int THREE_OF_A_KIND;
    
        /*
         * Default constructor.
         */
        DWEvaluator();
        
        virtual ~DWEvaluator();
        
        /*
         * Given an array of 5 cards, this function will evaluate the poker
         * hand based on Deuces Wild hands. The function will return an integer
         * number representing the rank of the hand as defined by the above
         * constants.
         * 
         * Parameters:
         *      hand (int*) - 5 card poker hand to evaluate.
         *
         * Returns:
         *      Integer represting the hand ranking with respect to Deuces Wild
         *      rules.
         */
        virtual int evaluate(int* hand);
    
    private:
        static const int m_straights[8192][4];
        static const int m_royalFlush;

        int numBits(int n);
        int evaluate();
        void reset();
        
        vector<int> m_nonDeuceCards;
        int m_numDeuces;
        int m_uniqueHash;
        int m_flushHash;
        int m_hash5;
        int m_hash4;
        int m_hash3;
        int m_hash2;
};

#endif
