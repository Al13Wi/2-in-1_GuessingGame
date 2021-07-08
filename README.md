# "2-in-1" GuessingGame
This is a "2-in-1" guessing game. The player first needs to guess a random number in a specific range of values. The player can choose one of several options concerning the range of values and purchase hints that provide information about where the random number is located. Afterwards the player may participate in a second game in which the player must guess the number of prime factors that are necessary to compute the random number of the first game. 

**Guessing Game Part 1 - *Random Number***
* In the first part of the game, the player must guess a number that is randomly allocated in a specific range of values
* At the start of the game, the player must select one of three options, each of which determines a specific range of values and a different score
* For each guess the player makes (valid and invalid), one point is deducted from the score
* For the first (valid) guess of the player, the player is informed whether or not the guess is close to the random number
* For the following guesses, the current guess is compared with the player's previous guess in order to inform the player whether the current guess is closer or farther away from the random number than the previous guess
* After every 5th guess, the player is informed about the current score and has the option to purchase a hint for the price of some points
  * Each hint will provide a higher level of detail about where the random number is located but the higher level of detail comes at a higher price
  * There is a maximum of three hints and the player cannot skip a hint to get to the next one - in other words, in order to get to the third hint, the player first needs to purchase hint 1 and 2
* The game continues until the player guesses the random number

**Guessing Game Part 2 - *Prime Factors***
* In the second part of the game, the player must guess how many prime factors the random number of the first part of the game contains 
* The player is eligible to participate in the second game, if the score is greater than zero points
* The player must first decide whether or not to participate in the second game before detailed information about this game is provided
* If the player chooses to play the second game, the bet amount must be in the range of 1 to 5
* If the player guesses the correct answer, the player receives the bet amount as reward, otherwise the points are lost
