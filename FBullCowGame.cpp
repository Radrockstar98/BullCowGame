#include "FBullCowGame.h"
#include <map>
#define TMap std::map

using int32 = int;

FBullCowGame::FBullCowGame() {Reset();} // default constructor

int32 FBullCowGame::GetCurrentTry() const {return MyCurrentTry;}
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const {return bGameIsWon;}

int32 FBullCowGame::GetMaxTries() const 
{
	TMap<int32, int32> WordLengthToMaxTries{ {3,4}, {4,7}, {5,10}, {6,16}, {7,20} };
	return WordLengthToMaxTries[MyHiddenWord.length()];
}

void FBullCowGame::WordBank(int32 WORD_LENGTH)
{
	TMap<int32, FString> WordLengthtoHiddenWord{ {3,"spy"}, {4,"like"}, {5,"agent"}, {6,"guitar"}, {7,"planets"} };
	MyHiddenWord = WordLengthtoHiddenWord[WORD_LENGTH];
	return;
}

void FBullCowGame::Reset()
{	
	MyCurrentTry = 1;
	bGameIsWon = false;
	return;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if (!IsIsogram(Guess)) 	// if the guess isn't an isogram 
	{
		return EGuessStatus::Not_Isogram;
	} 
	else if (!IsLowercase(Guess)) // if the guess isn't all lowercase
	{
		return EGuessStatus::Not_Lowercase;
	}
	else if (Guess.length() != GetHiddenWordLength()) // if the guess length is wrong
	{
		return EGuessStatus::Wrong_Length;
	}
	else //return OK
	{
		return EGuessStatus::OK;
	}
}

// receives a valid guess, incriments and returns count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;
	FBullCowCount BullCowCount;
	int32 WordLength = MyHiddenWord.length(); // assuming the same length as guess

	// loop through all letters in the hidden word
	for (int32 MHWChar = 0; MHWChar < WordLength; MHWChar++)
	{
		// compare letters against the guess
		for (int32 GChar = 0; GChar < WordLength; GChar++)
		{
			// if they match then
			if (Guess[GChar] == MyHiddenWord[MHWChar])
			{
				// if they are in the same place
				if (MHWChar == GChar)
				{
					BullCowCount.Bulls++; // incriment bulls
				} 
				else 
				{
					BullCowCount.Cows++; // incriment cows
				} 
			}
		}
	}
	if(BullCowCount.Bulls == WordLength){bGameIsWon = true;} // when the bulls and word length are the same
	else{bGameIsWon = false;} // when the bulls and word length is not the same
	return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Word) const
{	
	// treat 0 and 1 letter words as isograms
	if (Word.length() <= 1) { return true; }

	TMap<char, bool> LetterSeen; // setup our map
	for (auto Letter : Word) 	// for all letters of the word
	{
		Letter = tolower(Letter); // handle mixed case
		if (LetterSeen[Letter]) // if the letter is in the map
		{
			return false; // we do NOT have an isogram
		}
		else
		{
			LetterSeen[Letter] = true; // add the letter to the map
		}
	}
	return true; // for example in cases where /0 is entered
}


bool FBullCowGame::IsLowercase(FString Word) const
{
	for (auto Letter : Word)
	{
		if (!islower(Letter)) // if not a lowercase letter
		{
			return false;
		}
	}
	return true;
}