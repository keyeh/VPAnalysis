###############################################################################
#
#   File Name   : Makefile
#
#   Created By  : Niral Bhalodia
#
#   Copyright (c) 2013 Niral Bhalodia. All rights reserved.
#
#   This is free software. Permission is granted to redistribute and/or modify
#   this code under the terms of the MIT License as published by opensource.org.
#   This software is provided without warranty.
#
###############################################################################

CC= clang++
LIB_11= -std=c++11 -stdlib=libc++
FLAGS= -O3

OBJECTS= PlayingCard.o PlayingCardDeck.o JBEvaluator.o \
		 HandAnalysis.o DWEvaluator.o
SOURCES= PlayingCard.cpp PlayingCardDeck.cpp JBEvaluator.cpp HandAnalysis.cpp \
		 Eval5.cpp Analyze5.cpp DWEvaluator.cpp Eval5Deuces.cpp
RUNNERS= Eval5.o Analyze5.o Eval5Deuces.o

all : eval analyze deuces

eval: ${OBJECTS} Eval5.o
	${CC} ${LIB_11} ${FLAGS} -o eval Eval5.o ${OBJECTS}

deuces: ${OBJECTS} Eval5Deuces.o
	${CC} ${LIB_11} ${FLAGS} -o evalDeuces Eval5Deuces.o ${OBJECTS}

analyze: ${OBJECTS} Analyze5.o
	${CC} ${LIB_11} ${FLAGS} -o analyze Analyze5.o ${OBJECTS}

PlayingCard.o : PlayingCard.h
PlayingCardDeck.o : PlayingCardDeck.h PlayingCard.h
JBEvaluator.o : JBEvaluator.h PlayingCard.h
Eval5.o : JBEvaluator.h PlayingCard.h PlayingCardDeck.h DWEvaluator.h
Analysis.o : HandAnalysis.h JBEvaluator.h PlayingCardDeck.h 
HandAnalysis.o : HandAnalysis.h PlayingCardDeck.h PlayingCard.h

${OBJECTS} : ${SOURCES}
	${CC} ${LIB_11} ${FLAGS} -c ${SOURCES}

clean:
	rm -f ${OBJECTS} ${RUNNERS} eval analyze evalDeuces
