/******************************************************************************
 *
 *  File Name   : JBEvaluator.h
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

#ifndef _JBEVALUATOR_H
#define _JBEVALUATOR_H

#include "IEvaluator.h"
#include <set>

using namespace std;

/*
 * A Jacks or Better video poker evaluator. Simply create an instance and use
 * the evaluate function to evaluate hands.
 */
class JBEvaluator : public IEvaluator
{
    public:
        /*
         * All possible hands
         */
        static const int NO_HAND;
        static const int ROYAL_FLUSH;
        static const int STRAIGHT_FLUSH;
        static const int FOUR_OF_A_KIND;
        static const int FULL_HOUSE;
        static const int FLUSH;
        static const int STRAIGHT;
        static const int THREE_OF_A_KIND;
        static const int TWO_PAIR;
        static const int JACKS_OR_BETTER;

        JBEvaluator();
        
        virtual ~JBEvaluator();
        
        /*
         * Given a 5 card poker hand, this function will evaluate the hand based
         * on Jacks or Better rules. The returning integer corresponds with the
         * rank of the hand. All hand ranks are defined as constants in this
         * file.
         *
         * Parameters:
         *      hand (int *) - 5 card poker hand to evaluate
         *
         * Returns:
         *      Integer representing the ranking of the poker hand based on
         *      Jacks or Better rules.
         */
        virtual int evaluate(int* hand);
    
    private:
        static const set<int> m_straights;
        static const int m_naturalRoyal;
        int m_flushHash;
        int m_straightHash;
        int m_hash4;
        int m_hash3;
        int m_hash2;
        int evalHand();
        int numBits(int n);
};

#endif

