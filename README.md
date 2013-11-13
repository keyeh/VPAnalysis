VPAnalyzer
===========

Video Poker Analysis and Evaluator

This code is an evaluator and analyzer for video poker games. Currently, Jacks
or Better and Deuces Wild video poker evaluations are supported. However, any
class that implements the IEvaluator interface can take advantage of the
analyzer. In the program, playing cards are represented as unique integer bit
mask depending on its suit and rank. All implementation details have been
documented inside their respective classes. The purpose of the evaluators 
(JBEvaluator and DWEvaluator) is to take a traditional 5-card poker hand and 
evaluate it based on the rules of a specific game. The evaluator exploits the 
way playing cards are represented within the program. The analyzer uses an
evaluator and a paytable to calculate the expected returns of 5-card poker
hands. It can be used to find the best possible way to play a poker hand.

There is minimal error checking and monitoring of improper input. Any such
checks should occur before making appropriate function calls.

Along with the core code, there are classes used for testing correctness and
showing sample uses of the code. Eval5.cpp, Eval5Deuces.cpp, and Analyze5.cpp
serve this purpose.

