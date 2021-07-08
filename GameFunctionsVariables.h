#ifndef GAMEFUNCTIONSVARIABLES_H_INCLUDED
#define GAMEFUNCTIONSVARIABLES_H_INCLUDED

#include <vector>

// Variables
// Variables are clustered in groups according to their use in the program (order is not alphabetically)

extern int score;
extern int option;
extern int upperBound;
extern int lowerBound;
extern int randomNumber;
extern int numberOfGuesses;

extern int currentGuess;
extern int previousGuess;

extern int numberOfHints;
extern int hintPointsCost;
extern int hintEligibility;
extern int hintDecision;

//prime Factor Game
extern int betAmount;
extern int betLimit;
extern int gameDecision;
extern int primeFactorsGuess;

extern int primeFactorsRange;
extern int primeFactorsCount;
extern std::vector <int> primeFactors;

// Functions
// Functions are ordered alphabetically

void gameRules();

int hintCheckEligibility(int hintPointsCost, int score);

void hintDecile(int randomNumber, int upperBound);

void hintInfo(int numberOfHints, int hintPointsCost);

void hintPercentile(int randomNumber, int upperBound);

int hintPointsRequirements(int numberOfHints, int score);

void hintQuartile(int randomNumber, int upperBound);

int primeFactorsGame(std::vector <int> vectorPrime, int primeFactorsRange, int randomNumber);

int setGame(int option, int &lowerBound, int &upperBound);

void showHint(int numberOfHints, int randomNumber, int upperBound);

#endif // GAMEFUNCTIONSVARIABLES_H_INCLUDED
