#include "GameFunctionsVariables.h"

#include <ctime>
#include <cmath>
#include <iostream>
#include <random>
#include <vector>

using namespace std;

int main()
{
    // GAME START
    gameRules();

    while(true)
    {
        std::cout << "\n";
        std::cout << "Choose one of three options to proceed.\n";
        std::cout << "Option 1:  the value range is   [0, 100],  the initial score is: 25\n";
        std::cout << "Option 2:  the value range is  [0, 1000],  the initial score is: 35\n";
        std::cout << "Option 3:  the value range is [0, 10000],  the initial score is: 50\n";
        std::cout << "\n";
        std::cin >> option;

        if(option == 1 || option == 2 || option == 3)
        {
            break;
        }
        else
        {
            continue;
        }
    }

    score = setGame(option, lowerBound, upperBound);

    // Randomly select a number in the range of [lowerBound, upperBound]
    std::srand(std::time(nullptr));
    randomNumber = rand() % (upperBound + 1);

    std::cout << "\n\n";
    std::cout << "A number in the range from " << lowerBound << " to " << upperBound << " was randomly selected.\nYour initial score is: " << score << "\nStart guessing the random number!";

    // Start guessing
    while(true)
    {
        // Before the next guess is made, evaluate whether or not the player has the option to purchase a hint
        if(numberOfGuesses > 0 && numberOfGuesses % 5 == 0 )
        {
            std::cout << "\n\nALERT!\nYou have already made " << numberOfGuesses << " guesses. Your current score is " << score << ".\n";

            // Evaluate how much points the hint costs and assign this value to a variable that serves as argument for following functions
            hintPointsCost = hintPointsRequirements(numberOfHints, score);

            hintEligibility = hintCheckEligibility(hintPointsCost, score);

            if(hintEligibility == 0)
            {
                std::cout << "\nSorry, no more hints can be provided.";
            }
            else if(hintEligibility == 1)
            {
                hintInfo(numberOfHints, hintPointsCost);

                // Evaluate whether or not the player wants to use a hint
                while(true)
                {
                    std::cout << "\nDo you want to purchase this hint for a price of " << hintPointsCost << " points?";
                    std::cout << "\nIf yes - enter 1 || If no - enter 0\n";
                    std::cin >> hintDecision;

                    if(hintDecision == 1 || hintDecision == 0)
                    {
                        break;
                    }
                    else
                    {
                        continue;
                    }
                }

                if(hintDecision == 1)
                {
                    showHint(numberOfHints, randomNumber, upperBound);
                    numberOfHints++;
                    score -= hintPointsCost;
                }
            }
        }

        // Take the current guess as input
        std::cout << "\n\nGuess a number in the range [" << lowerBound << ", " << upperBound << "]!\n";
        std::cin >> currentGuess;

        // Make sure that the guess is in the valid range of values
        if(currentGuess < lowerBound || currentGuess > upperBound)
        {
            std::cout << "Your guess is out of range. Guess a number in the range " << lowerBound << " and " << upperBound << ".";
            numberOfGuesses++;
            score--;
            continue;
        }

        // Code only applied for the first guess // -> numberOfGuesses == 0
        // The second expression, where "previousGuess" is set to -1, is necessary to cover the case when the first guess (and possibly all following guesses) is out of range and thus invalid
        // Consequently, in the following iteration, it is not possible to make the comparison of "currentGuess" to "previousGuess" because the previous guess is invalid
        // The comparison of the current guess to previous guess is only made with valid values, i.e. only the latest valid "currentGuess" is compared with the latest "previousGuess"
        // Only when the number of guesses is greater than 1 and the previous guess is valid (previousGuess != -1) will the program jump to the "else clause"
        if(numberOfGuesses == 0 || previousGuess == -1)
        {
            if(currentGuess == randomNumber)
            {
                numberOfGuesses++;
                score--;
                break;
            }
            else if(abs(randomNumber - currentGuess) <= (upperBound / 20))
            {
                std::cout << "\nHOT! The difference to the random number is " << (upperBound / 20) << " or less!";
            }
            else if(abs(randomNumber - currentGuess) <= (upperBound / 10))
            {
                std::cout << "\nWarm! The difference to the random number is " << (upperBound / 10) << " or less!";
            }
            else if(abs(randomNumber - currentGuess) > (upperBound / 10))
            {
                std::cout << "\nCold! The difference to the random number is more than " << (upperBound / 10) << "!";
            }
            numberOfGuesses++;
            score--;
            previousGuess = currentGuess;
        }
        else
        {
            if(currentGuess == randomNumber)
            {
                numberOfGuesses++;
                score--;
                break;
            }
            else if(abs(randomNumber - currentGuess) < abs(randomNumber - previousGuess))
            {
                std::cout << "Warmer!";
            }
            // The argument after the "&&" operator assures that this event does not occur simply by guessing the same value twice in a row
            else if(abs(randomNumber - currentGuess) == abs(randomNumber - previousGuess) && currentGuess != previousGuess)
            {
                std::cout << "Remarkable! You picked a different number but the 'distance' to the random number is identical. Can you guess the random number now?";
            }
            else if(abs(randomNumber - currentGuess) == abs(randomNumber - previousGuess) && currentGuess == previousGuess)
            {
                std::cout << "You picked the same number as in the previous guess. No comment...";
            }
            else
            {
                std::cout << "Colder!";
            }
            numberOfGuesses++;
            score--;
            previousGuess = currentGuess;
        }
    }

    std::cout << "\n\nCongratulations!\nYou found the random number " << randomNumber << ".\nYou used " << numberOfHints << " hint(s) and you had to guess " << numberOfGuesses << " time(s) to find the random number.\nYour score is: " << score << "\n";

    // Assess whether the player has points left which can be used to play the second game
    if(score > 0)
    {
        betLimit = min(score, 5);
        std::cout << "\n\nDo you want to play another game? In this game you have to make one more guess.";
        std::cout << "\nYou can bet a maximum of " << betLimit << " points. If you are wrong, those points are lost. However, if you win, you get back the points you put at stake and on top of that you receive the same amount of points as a reward.";
        std::cout << "\nIf you decide to play the game, your bet amount has to be at least one point.";

        while(true)
        {
            std::cout << "\nDo you want to play?";
            std::cout << "\nIf yes - enter 1 || If no - enter 0";
            std::cout << "\n";
            std::cin >> gameDecision;
            if(gameDecision == 1 || gameDecision == 0)
            {
                break;
            }
            else
            {
                continue;
            }
        }

        if(gameDecision == 1)
        {
            std::cout << "\n\nYou decided to play the second game.";

            if(betLimit == 1)
            {
                std::cout << "\nYour current score is " << score << ". This means you can only invest 1 point.";
                betAmount = 1;
            }
            else
            {
                while(true)
                {
                    std::cout << "\nYour current score is " << score << ". This means you can invest in the range of 1 to " << betLimit << " points.";
                    std::cout << "\nHow many points do you want to invest in the bet?";
                    std::cout << "\n";
                    std::cin >> betAmount;
                    if(betAmount >= 1 && betAmount <= betLimit)
                        break;
                    else
                    {
                        continue;
                    }
                }
            }

            // Deduct the bet amount from the score
            std::cout << "\n" << betAmount << " points are at stake for the upcoming game. This amount is now deducted from your current score.";
            score -= betAmount;
            std::cout << "\nYour new score is: " << score;

            std::cout << "\n\nLet's start the second game! The random number from the previous game is " << randomNumber << ".";

            // If the random number does not contain any prime factors (0 or 1), a new number is generated. Otherwise, the number does not change.
            if(randomNumber <= 1)
            {
                std::cout << "\n\nThe number " << randomNumber << " cannot be computed using prime factors. Therefore, a new number within the range[" << lowerBound << ", " << upperBound << "] is computed.";

                while(true)
                {
                    randomNumber = rand() % (upperBound + 1);

                    if(randomNumber >= 2)
                    {
                        std::cout << "\n\nThe new number is: " << randomNumber << "\n";
                        break;
                    }
                    else
                    {
                        continue;
                    }
                }
            }

            // Prime factor game
            std::cout << "\nYou must now guess the number of prime factors necessary to compute this number. To make it a little bit easier, your guess is considered to be correct even if it deviates by 1 from the correct answer.";
            std::cout << "\nWhat is your guess - what is the number of prime factors contained in the number " << randomNumber << "?";
            std::cout << "\nEnter your guess here: ";
            std::cin >> primeFactorsGuess;

            primeFactorsCount = primeFactorsGame(primeFactors, primeFactorsRange, randomNumber);

            if(abs(primeFactorsCount - primeFactorsGuess) <= 1)
            {
                std::cout << "\n\nCongratulations! Your guess '" << primeFactorsGuess << "' was correct.\nYou won the bet and receive " << betAmount * 2 << " points.";
                score += betAmount * 2;
            }
            else
            {
                std::cout << "\n\nSorry, your guess '" << primeFactorsGuess << "' was not correct. The " << betAmount << " points used as bet amount are lost.";
            }
        }
        else
        {
            std::cout << "\n\nYou decided to not play the second game.";
        }
    }

    std::cout << "\n\n\nThe game is over. Your final score is: " << score;
    std::cout << "\n\nThank you for playing.\n";

    return 0;
}

