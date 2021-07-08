#include "GameFunctionsVariables.h"

#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

// Variables
// Variables are clustered in groups according to their use in the program (order is not alphabetically)

// Number Guessing Game
int score{};
int option{};
int upperBound{};
int lowerBound{0};
int randomNumber{};
int numberOfGuesses{0};

// The following two variables are necessary to compare the current guess with the previous guess in order to determine whether or not the current guess is closer to the secret number than the previous guess
int currentGuess{};

// Set to "-1" to cover the case when the first guess is out of range
// Consequently, in the following iteration, it is not possible to make the comparison of "currentGuess" to "previousGuess" because the previous guess is invalid
// The comparison of the current guess to previous guess is only made with valid values, i.e. only the latest valid "currentGuess" is compared with the latest "previousGuess"
int previousGuess{-1};

int numberOfHints{0};
int hintPointsCost{};
int hintEligibility{};
int hintDecision{};

//Prime Factors Game
int betAmount{};
int betLimit{};
int gameDecision{};
int primeFactorsGuess{};

int primeFactorsRange{};
int primeFactorsCount{};
std::vector <int> primeFactors{};

// Functions
// Functions are ordered alphabetically

// This function contains all rules for the game
void gameRules()
{
    std::cout << "\nThis is a guessing game. The program will generate a random number within a specified range of values and you have to guess what this number is.";
    std::cout << "\nThe program compares your current guess with your previous guess and informs you whether the current guess is closer to (warmer) or farther away from (colder) the random number.";
    std::cout << "\nYou can choose one out of three game setups and, in case you finish the first game with a positive number of points, you can choose to play a bonus game.";
    std::cout << "\n\nIMPORTANT: In the first game, each guess costs you 1 point.";
    std::cout << "\n\nAfter every 5th guess, you have the option to purchase a hint in exchange for some points. Each hint will provide a higher level of detail about where the random number is located but the higher level of detail comes at a higher price.";
    std::cout << "\nHint 1: for the price of 2 points, you get information about the quartile of the range where the random number is located.";
    std::cout << "\nHint 2: for the price of 5 points, you get information about the decile of the range where the random number is located.";
    std::cout << "\nHint 3: for the price of 10 points, you get information about the percentile of the range where the random number is located.";
    std::cout << "\nPlease note that there is a maximum of three hints and that you cannot skip a hint to get to the next one - in other words, in order to get to the third hint, you first need to purchase hint 1 and 2.";
    std::cout << "\n\n\nLET'S START!\n";
}

// This function is used to return a value that is evaluated in order to assess whether or not the player is eligible for using hints
// In case the player has already used three hints, the variable "hintPointsCost" is set one unit above the player's current score in order to make the player ineligible => see function "hintPointsRequirements": switch, default value
int hintCheckEligibility(int hintPointsCost, int score)
        {
            if(score >= hintPointsCost)
            {
                return 1;
            }
            else
            {
                return 0;
            }
        }

// This function shows the decile of the current range value in which the random number is located
void hintDecile(int randomNumber, int upperBound)
{
    int x{};
    int y{};
    for(int i{1}; i <= 10; i++)
        {
            x = round((upperBound / 10)) * (10 - i);
            y = x + round(upperBound / 10);

            if(randomNumber >= x)
            {
                std::cout << "\nHint:\nThe random number is located in the range [" << x << ", " << y << "]!";
                break;
            }
            else
            {
                continue;
            }
        }
}

// Based on how many hints the player has already used, the player is offered a particular hint
// Note: the order of hints remains unchanged, meaning that if a player rejects a hint, the player is provided the same hint again next time (the player cannot jump to another hint)
void hintInfo(int numberOfHints, int hintPointsCost)
{
    switch(numberOfHints)
    {
    case 0:
        std::cout << "\nYou can get a hint that shows you in which quartile of the total range of values the random number is located.\nThis hint will cost you " << hintPointsCost << " points.";
        break;
    case 1:
        std::cout << "\nYou can get a hint that shows you in which decile of the total range of values the random number is located.\nThis hint will cost you " << hintPointsCost << " points.";
        break;
    case 2:
        std::cout << "\nYou can get a hint that shows you in which percentile of the total range of values the random number is located.\nThis hint will cost you " << hintPointsCost << " points.";
        break;
    default:
        break;
    }
}

// This function shows the percentile of the current range value in which the random number is located
 void hintPercentile(int randomNumber, int upperBound)
{
    int x{};
    int y{};
    for(int i{1}; i <= 100; i++)
        {
            x = round((upperBound / 100)) * (100 - i);
            y = x + round(upperBound / 100);

            if(randomNumber >= x)
            {
                std::cout << "\nHint:\nThe random number is located in the range [" << x << ", " << y << "]!";
                break;
            }
            else
            {
                continue;
            }
        }
}

// The return value of this function is used to feed the variable hintCosts
int hintPointsRequirements(int numberOfHints, int score)
{
    switch(numberOfHints)
    {
    case 0:
        return 2;
    case 1:
        return 5;
    case 2:
        return 10;
    default:
        // In case the player has used all three hints, the return value for the variable hintCosts is set 1 unit above the player's current score, which will make the player ineligible for using hints
        return score + 1;
    }
}

// This function shows the quartile of the current range value in which the random number is located
void hintQuartile(int randomNumber, int upperBound)
{
    int x{};
    int y{};
    for(int i{1}; i <= 4; i++)
        {
            x = round((upperBound / 4)) * (4 - i);
            y = x + round(upperBound / 4);

            if(randomNumber >= x)
            {
                std::cout << "\nHint:\nThe random number is located in the range [" << x << ", " << y << "]!";
                break;
            }
            else
            {
                continue;
            }
        }
}

// Prime Factor game
// The first for loop computes the prime factors of the random number and appends each prime factor to the end of the vector
// The second for loop prints the elements of the vector (the prime factors)
// The function returns an integer value that equals the number of the vector's elements which is then used to compare it to the guess of the player
int primeFactorsGame(std::vector <int> vectorPrime, int primeFactorsRange, int randomNumber)
{
    primeFactorsRange = randomNumber;

    for(int i{2}; i <= primeFactorsRange;)
        {
            if(primeFactorsRange % i == 0)
            {
                vectorPrime.push_back(i);
                primeFactorsRange = round(primeFactorsRange / i);
                i = 2;
            }
            else
            {
                i++;
                continue;
            }
        }

    std::cout << "\nThe number " << randomNumber << " consists of " << vectorPrime.size() << " prime factor(s):\n";

    for(int i{0}; i < vectorPrime.size(); i++)
        {
            if(i == 0)
                std::cout << vectorPrime[i];
            else
            {
                std::cout << ", " << vectorPrime[i];
            }
        }

    return vectorPrime.size();
}

// This function sets up the game according to the option selected by the player
// Pass by reference is used to modify the value of the lower bound and the upper bound
int setGame(int option, int &lowerBound, int &upperBound)
{
    switch(option)
    {
    case 1:
        std::cout << "\nOption 1 was selected.";
        lowerBound = 0;
        upperBound = 100;
        return 25;
    case 2:
        std::cout << "\nOption 2 was selected.";
        lowerBound = 0;
        upperBound = 1000;
        return 35;
    case 3:
        std::cout << "\nOption 3 was selected.";
        lowerBound = 0;
        upperBound = 10000;
        return 50;
    }
}

// Based on the number of hints, the function selects which hint is selected and shown to the player
 void showHint(int numberOfHints, int randomNumber, int upperBound)
{
    switch(numberOfHints)
    {
    case 0:
        hintQuartile(randomNumber, upperBound);
        break;
    case 1:
        hintDecile(randomNumber, upperBound);
        break;
    case 2:
        hintPercentile(randomNumber, upperBound);
        break;
    default:
        break;
    }
}
