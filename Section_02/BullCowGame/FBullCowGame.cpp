#pragma once

#include "FBullCowGame.h"
#include <map>
#define TMap std::map

using FString = std::string;
using int32 = int;

void FBullCowGame::Reset()
{
	MyCurrentTry = 1;
	MyHiddenWord = "planet";
	bGameIsWon = false;
	return;
}

FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;
	FBullCowCount BullCowCount;

	int32 GuessLength = Guess.length();
	for (int32 i = 0; i < GetHiddenWordLength(); i++)
	{
		for (int32 j = 0; j < GuessLength; j++)
		{
			if (Guess[j] == MyHiddenWord[i])
			{
				if (i == j)
				{
					BullCowCount.Bulls++;
				}
				else
				{
					BullCowCount.Cows++;
				}
			}
		}
	}
	if (BullCowCount.Bulls == GetHiddenWordLength()) { bGameIsWon = true; }
	return BullCowCount;
}

bool FBullCowGame::IsIsogram(const FString Word) const
{
	if (Word.length() <= 1) { return true; }
	TMap<char, bool> LetterSeen;

	for (auto Letter : Word)
	{
		Letter = tolower(Letter);
		if (LetterSeen[Letter]) { return false; } 
		else { LetterSeen[Letter] = true; }
	}
	return true;
}

bool FBullCowGame::IsLowercase(const FString & Word) const
{
	for (auto Letter : Word)
	{
		if (!islower(Letter)) { return false; }
	}
	return true;
}

bool FBullCowGame::IsAlpha(const FString & Word) const
{
	for (auto Letter : Word)
	{
		if (!isalpha(Letter)) { return false; }
	}
	return true;
}

FBullCowGame::FBullCowGame() { Reset(); }

int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const { return bGameIsWon; }

int32 FBullCowGame::GetMaxTries() const 
{
	TMap<int32, int32> WordLengthToMaxTries{ {3,4}, {4,7}, {5,10}, {6,16}, {7,20} };
	return WordLengthToMaxTries[GetHiddenWordLength()]; 
}


EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if (GetHiddenWordLength() != Guess.length())
	{
		return EGuessStatus::Wrong_Length;
	}
	else if (!IsLowercase(Guess))
	{
		return EGuessStatus::Not_Lowercase;
	}
	else if (!IsAlpha(Guess))
	{
		return EGuessStatus::Not_Alpha;
	}
	else if (!IsIsogram(Guess))
	{
		return EGuessStatus::Not_Isogram;
	}

	return EGuessStatus::OK;
}
