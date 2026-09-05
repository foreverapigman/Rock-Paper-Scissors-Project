#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>
#include <random>
using namespace std;

int playerScore = 0;
int computerScore = 0;
int ties = 0;
int roundNumber = 1;
int playerChoice, computerChoice;
bool gameOver = false;

void displayMenu()
{
	cout << "\n------------------------------------------------------\nWelcome to Round " << roundNumber << " of Rock, Paper, Scissors!\n";
	cout << "Please choose an option:\n";
	cout << "(1) Rock\n";
	cout << "(2) Paper\n";
	cout << "(3) Scissors\n";
	cout << "(4) Quit\n\n";
}

string toLowerCase(const string& input) { //this function was taken from the internet
	string result = input;
	transform(result.begin(), result.end(), result.begin(),
		[](unsigned char c) { return tolower(c); });
	return result;
}

string validOptions[8] = { "rock", "r", "paper", "p", "scissors", "s", "quit", "q" };

int checkIfValidOption(string playerChoice)
{
	for (int i = 0; i < 8; i++) {
		if (toLowerCase(playerChoice) == validOptions[i]) {
			return (i);
		}
	}
	return -1;
}

int getPlayerChoice()
{
	string tempPlayerChoice;
	while (true) {
		cin >> tempPlayerChoice;
		if (checkIfValidOption(tempPlayerChoice) != -1) {
			int choiceIndex = checkIfValidOption(tempPlayerChoice);
			if (choiceIndex == 0 || choiceIndex == 1) {
				playerChoice = 1;
				return playerChoice;
			}
			else if (choiceIndex == 2 || choiceIndex == 3) {
				playerChoice = 2;
				return playerChoice;
			}
			else if (choiceIndex == 4 || choiceIndex == 5) {
				playerChoice = 3;
				return playerChoice;
			}
			else if (choiceIndex == 6 || choiceIndex == 7) {
				gameOver = true;
				return -1;
			}
		}
		else {
			try {
				int choiceInt = stoi(tempPlayerChoice);
				if (stoi(tempPlayerChoice) >= 1 && stoi(tempPlayerChoice) <= 3) {
					playerChoice = choiceInt;
					return playerChoice;
				}
				else if (stoi(tempPlayerChoice) == 4) {
					gameOver = true;
					return -1;
				}
				else {
					cout << "Invalid option. Please choose again.\n";
				}
			}
			catch (exception& e) {
				cout << "Invalid option. Please choose again.\n";
			}
		}
	}
}

int getComputerChoice() //the code for this function was taken from the internet
{
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int> dist(1, 3);
	int randomNum = dist(gen);
	computerChoice = randomNum;
	return randomNum;
}

int determineWinner(int pChoice, int cChoice)
{
	int winner = 0;
	if (pChoice == cChoice) {
		winner = 0; //tie
	}
	else if ((pChoice == 1 && cChoice == 3) || (pChoice == 2 && cChoice == 1) || (pChoice == 3 && cChoice == 2)) {
		winner = 1; //player wins
	}
	else {
		winner = 2; //computer wins
	}
	return winner;
}

void displayResults(int winner, bool final)
{
	if (final) {
		cout << "\n------------------------------------------------------\nThanks for playing! Final scores:\n";
		cout << "Player Wins: " << playerScore << "\nComputer Wins: " << computerScore << "\nTies: " << ties << "\nTotal Rounds: " << roundNumber - 1 << "\n\n";
		if (playerScore > computerScore) {
			cout << "You win the tournament!\n";
		}
		else if (playerScore < computerScore) {
			cout << "The computer wins the tournament!\n";
		}
		else {
			cout << "The tournament is a tie!\n";
		}
	}
	else {
		if (playerChoice == 1) {
			cout << "\nYou chose Rock.\n\n";
		}
		else if (playerChoice == 2) {
			cout << "\nYou chose Paper.\n\n";
		}
		else if (playerChoice == 3) {
			cout << "\nYou chose Scissors.\n\n";
		}
		if (computerChoice == 1) {
			cout << "The computer chose Rock.\n\n";
		}
		else if (computerChoice == 2) {
			cout << "The computer chose Paper.\n\n";
		}
		else if (computerChoice == 3) {
			cout << "The computer chose Scissors.\n\n";
		}
		if (winner == 0) {
			cout << "It's a tie!\n\n";
			ties++;
		}
		else if (winner == 1) {
			cout << "You win round " << roundNumber << "!\n\n";
			playerScore++;
		}
		else if (winner == 2) {
			cout << "The computer wins round " << roundNumber << "!\n\n";
			computerScore++;
		}
		cout << "Player Wins: " << playerScore << "\nComputer Wins: " << computerScore << "\nTies: " << ties << "\n";
	}
}

int main()
{
	while (!gameOver) {
		displayMenu();
		if (getPlayerChoice() == -1) {
			displayResults(-1, true);
			break;
		}
		getComputerChoice();
		displayResults(determineWinner(playerChoice, computerChoice), false);
		roundNumber++;
	}
}