#ifndef __BULL_COW_GAME_H__
#define __BULL_COW_GAME_H__

#include <string>

using FString = std::string;
using int32 = int;

//Bulls and Cows initialized to Zero
struct FBullCowCount 
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum class EGuessStatus
{
	Invalid_Status,
	OK,
	Not_Isogram,
	Wrong_Length,
	Not_Lowercase,
	Not_Alpha
};

enum class EResetStatus
{
	OK
};

class FBullCowGame 
{
public:
	FBullCowGame();

	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;


	bool IsGameWon() const;
	EGuessStatus CheckGuessValidity(FString Guess) const;

	void Reset(); //TODO make a more rich return value.

	FBullCowCount SubmitValidGuess(FString Guess);


private:
	int32 MyCurrentTry;
	FString MyHiddenWord;
	bool bGameIsWon;

	bool IsIsogram(const FString Word) const;
	bool IsLowercase(const FString &Word) const;
	bool IsAlpha(const FString &Word) const;
};

#endif
