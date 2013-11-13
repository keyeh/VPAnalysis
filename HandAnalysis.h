/******************************************************************************
 *
 *  File Name   : HandAnalysis.h
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

#ifndef _HANDANALYSIS_H
#define _HANDANALYSIS_H

#include "IEvaluator.h"
#include <vector>
#include <map>
#include <string>

using namespace std;

/*
 * Class to analyze hands. Analyze any video poker hand and find the best
 * way to play it. That is, find which cards to hold and which cards to draw.
 * This analyzer takes in any video poker evalautor and associated paytable.
 */
class HandAnalysis
{
    public:
        /*
         * Default constructor. Note, the evaluator's outputs must map
         * onto the paytable approriately. That is, be sure the evaluator
         * and paytable are aligned with each other.
         *
         * Parameters:
         *      evaluator (IEvaluator*) - hand evaluator used for all hands
         *          analyzed with this logic.
         *
         *      paytable (const map<int, int>) - paytable where key represents
         *          hand rank and value represent payout
         */
        HandAnalysis(IEvaluator* evaluator, const map<int,int>* paytable);

        ~HandAnalysis();

        /*
         * With any 5 card video poker hand, there are a total of 32 ways to
         * hold the cards.
         *
         * Returns:
         *      A vector of vectors that where each vector represents a
         *      particular hold mask.
         */
        const vector<vector<int> > & getHoldMasks();
        
        /*
         * Expected return based on evaluating the hand and holding the
         * cards specificed by the vector. The expected return is based on
         * the evalautor of the object as well as the member paytable.
         *
         * Parameters:
         *      hand (int*) - five card poker hand to evaluate
         *
         *      holdMask (vector<int>) - vector masks that represent which cards
         *          to hold.
         *
         * Returns:
         *      The expected return of the hand when holding specified cards.
         */
        double expectedReturn(int* hand, vector<int> holdMask);

        /*
         * Go through all possible hold alignments and find the "best" one.
         * That is, find the hold that gives the highest expected return for the
         * given hand.
         *
         * Parameters:
         *      hand (int*) - Five card poker hand
         *
         * Returns:
         *      Hold mask representing which cards to hold in order to get the
         *      maximum expected return.
         */
        vector<int> bestHold(int* hand);
        
        /*
         * Print out the hand showing only cards held.
         *
         * Parameters:
         *      hand (int*) - five card poker hand
         *      holdMask (vector<int>) - vector representing which cards are
         *          held.
         *
         * Returns:
         *      String description of the cards held. (C++ string)
         */
        static string holdDescription(int* hand, vector<int> holdMask);
        
        /*
         * This function outputs a map of all possible holds and their
         * associated expected values of the inputed hand. The hand must be 5
         * cards.
         *
         * Parameters:
         *      hand (int*) - five card poker hand
         *
         * Returns:
         *      Map where key is a specific hold mask and associated value is
         *      the corresponding expected value with such cards were held.
         */
        map<vector<int>,double> handEVs(int* hand);
        
        /*
         * Fully exhaustive analysis. Each hold possibility of the inputted hand
         * is mapped to a vector that details the hold's expected return and the
         * number of hands possible for each poker rank.
         *
         * Parameters:
         *      hand (int*) - five card poker hand to analyze
         * 
         * Returns:
         *      Map with full analysis of the hand. The key is a specific hold
         *      mask and its associated key is a vector of analysis information
         *      of the evaluation. The 0th index of this vector contains the
         *      expected return. Indicies 1 to n represent the frequency count
         *      of each hand ranking possible with the given hold.
         */
        map<vector<int>,vector<double> > fullAnalysis(int* hand);

    private:
        IEvaluator* m_evaluator;
        const map<int, int>* m_paytable;
        vector<vector<int> > m_holdMasks;
        void enumerateHoldMasks();
        vector<vector<int> > fillHand(int* hand, vector<int> holdMask);
};

#endif

