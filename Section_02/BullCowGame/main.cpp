#pragma once

#include "FBullCowGame.h"

#include <iostream>
#include <string>

using FText = std::string;
using int32 = int;

void PrintIntro();
void PlayGame();
void PrintGameSummary();
bool AskToPlayAgain();

FText GetValidGuess();

void PrintBack(const FBullCowCount &Count, const FText &Guess);

FBullCowGame BCGame;

int main()
{
	PrintIntro();
	PlayGame();
	PrintGameSummary();
	while (AskToPlayAgain())
	{
		BCGame.Reset();
		std::cout << std::endl;
		PrintIntro();
		PlayGame();
		PrintGameSummary();
	}
	return 0;
}

void PlayGame()
{
	// Main Loop
	//loop asking for guesses while the game is not won and there are still turns/tries remaining
	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= BCGame.GetMaxTries())
	{
		FText Guess = GetValidGuess();

		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);
		PrintBack(BullCowCount, Guess);
		std::cout << std::endl;
	}
	return;
}

void PrintGameSummary()
{
	if (BCGame.IsGameWon())
	{
		std::cout << "Congratulations!" << std::endl;
	}
	else
	{
		std::cout << "You Lose!" << std::endl;
	}
	return;
}

//Prints the game introduction paragraph
void PrintIntro()
{
	std::cout << "Welcome to Bulls and Cows\n";
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength();
	std::cout << " letter isogram I'm thinking of?\n";
	std::cout << std::endl;
	return;
}

bool AskToPlayAgain()
{
	std::cout << "Do you want to play again? (y/n) ";
	std::string Response = "";
	std::getline(std::cin, Response);
	return Response[0] == 'y' || Response[0] == 'Y';
}

//Gets a guess from the user, returns as a string.
std::string GetValidGuess()
{
	FText Guess = "";
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	while (Status != EGuessStatus::OK)
	{
		std::cout << "(try " << BCGame.GetCurrentTry() << " of " << BCGame.GetMaxTries() << ") Enter your guess: ";
		std::getline(std::cin, Guess);

		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status) 
		{
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << "-letter isogram.\n" << std::endl;
			break;
		case EGuessStatus::Not_Alpha:
			std::cout << "Please enter alphabetical characters only.\n" << std::endl;
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter an isogram, only use each letter once.\n" << std::endl;
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please use lowercase letters only.\n" << std::endl;
			break;
		}
	}
	return Guess;
}


//Repeats a user's guess back to them.
void PrintBack(const FBullCowCount &Count, const FText &Guess)
{
	// repeat the guess back to them
	std::cout << "Your guess was: " << Guess << std::endl;
	std::cout << "Bulls: " << Count.Bulls << ", Cows: " << Count.Cows << "." << std::endl;

	return;
}