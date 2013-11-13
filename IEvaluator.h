/******************************************************************************
 *
 *  File Name   : IEvaluator.h
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

#ifndef _IEVALUATOR_H
#define _IEVALUATOR_H

/*
 * This class serves as a basic interface for all evaluator classes. Thus,
 * can be used to easily switch one evaluator with another.
 */
class IEvaluator
{
    public:
        /*
         * Evaluate the video poker hand that is inputted based on a given set
         * of rules.
         *
         * Parameters:
         *      int* - hand to evaluate (typically 5 card hand)
         *
         * Returns:
         *      Integer representation of the hand rank.
         */
        virtual int evaluate(int*) = 0;
        
        /*
         * Deafult destructor
         */
        virtual ~IEvaluator(void) {};
};

#endif
