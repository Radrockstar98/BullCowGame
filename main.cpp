/* This is the console executable, that makes use of the BullCow class
This acts as the view in a MVC pattern, and is responsible for all
user interaction. For game logic see the FBullCowGame class.
*/

#include <iostream>
#include <string>
#include "FBullCowGame.h"

using FText = std::string;
using int32 = int;

void PrintIntro();
void PlayGame();
FText GetValidGuess();
bool AskToPlayAgain();
void PrintGameSummary();
void GetGameDifficulty();

FBullCowGame BCGame; // instantiate a new game

// the main function and starting place for the program
int main()
{
	std::cout << BCGame.GetCurrentTry();

	bool bPlayAgain = false;
	do
	{
		PrintIntro();
		GetGameDifficulty();
		PlayGame();
		bPlayAgain = AskToPlayAgain();
	} while (bPlayAgain);

	std::cout << std::endl;
	// hold the screen
	std::cin.get();
	return 0; // exit the application
}

// the entry point for our application
void PrintIntro()
{
	std::cout << "Welcome to Bulls and Cows, a fun word game.\n";
	std::cout << std::endl;
	std::cout << "          }   {         ___ " << std::endl;
	std::cout << "          (o o)        (o o) " << std::endl;
	std::cout << "   /-------\\ /          \\ /-------\\ " << std::endl;
	std::cout << "  / | BULL |O            O| COW  | \\ " << std::endl;
	std::cout << " *  |-,--- |              |------|  * " << std::endl;
	std::cout << "    ^      ^              ^      ^ " << std::endl;
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength();
	std::cout << " letter isogram I'm thinking of?\n";
	std::cout << std::endl;
	return;
}

void PlayGame()
{
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();

	// loop asking for guess while the game is NOT won
	// and there are still guesses remaining
		while(!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries)
		{
			FText Guess = GetValidGuess();

			// submit valid guess to the game 
			FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);

			std::cout << "Bulls = " << BullCowCount.Bulls;
			std::cout << ". Cows = " << BullCowCount.Cows << "\n\n";
		}
		PrintGameSummary();
		return;
}

// loop continually until a valid guess is entered
FText GetValidGuess() 
{
	FText Guess = "";

	EGuessStatus Status = EGuessStatus::Invalid_Status;
	do
	{
		// get a guess from the player
		int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout << "Try " << CurrentTry << " of " << BCGame.GetMaxTries();
		std::cout << ". \nEnter your guess: ";
		std::getline(std::cin, Guess);

		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status)
		{
		/*case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n\n";
			break;*/
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter a word with no repeating letters.\n\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter only lowercase letters.\n\n";
			break;
		default:
			// assume the guess is valid
			break;
		}
	} while (Status != EGuessStatus::OK); // keep looping until we get no errors
	return Guess;
}

// to see if the player wants to go again
bool AskToPlayAgain()
{
	std::cout << "Do you want to play again with the same word (y/n)? ";
	FText Response = "";
	std::getline(std::cin, Response);
	return (Response[0] == 'y') || (Response[0] == 'Y');
}

void PrintGameSummary()
{
	if (BCGame.IsGameWon()) // for when they win
	{
		std::cout << "Congratulations on guessing the word, you beast!!\n\n";
	}
	else // for when they lose
	{
		std::cout << "Hard luck on not guessing the right word, better luck next time...\n\n";
	}
	return;
}

void GetGameDifficulty()
{
	int32 DiffWord_Length = 3;
	constexpr int32 DiffMaxWord_Length = 7;
	do
	{
		std::cout << "How long of a word do you want to go up against? (enter 3 through 7): ";
		std::cin >> DiffWord_Length;
		if (DiffWord_Length < 3 || DiffWord_Length > DiffMaxWord_Length)
		{
			std::cout << "you entered an incorrect length. Let's try again\n";
		}
	} while (DiffWord_Length < 3 || DiffWord_Length > DiffMaxWord_Length);
	BCGame.WordBank(DiffWord_Length);
	std::cout << std::endl;
	return;
}
