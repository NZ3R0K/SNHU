/*
Name		: Nathan Hallam
Course		: IT-132
Data		: 24th March, 2024
Project NO	: 3-2
File Name	: HallamNathan_TicTacToe.cpp
Description : Follow along with the comments to finish the program by inserting missing code marked by TODO.
			  Marked TODOs list below:
			  1. Write declaration for checkForWinner line 26
			  2. drawBoard on line 36
			  3. checkForValidMove on line 44
			  4. Interpret code in checkForWinner start line 74 end line 100
			  5. name function based on declaration for checkValidMove on line 121
*/



#include <iostream>
using namespace std;

char boardTile[10] = { 'o', '1', '2', '3', '4', '5', '6', '7', '8', '9' };

//Write the function declarations
bool checkValidMove(int);
void drawBoard();
int checkForWinner();

int main()
{
	int player = 1, i, choice;
	char mark;
	bool isMoveValid = false;
	do
	{
		//draws the game board
		drawBoard();

		player = (player % 2) ? 1 : 2;
		cout << "Player " << player << ", enter a number:  ";
		cin >> choice;
		mark = (player == 1) ? 'X' : 'O';

		//Check if move is valid
		isMoveValid = checkValidMove(choice);

		if (isMoveValid){
			boardTile[choice] = mark;
		}
		else{
			cout << "Invalid move ";
			player--;
			cin.ignore();
			cin.get();
		}

		i = checkForWinner();
		player++;
	} while (i == -1);

	drawBoard();
	if (i == 1)
		cout << "==>Player " << --player << " wins!";
	else
		cout << "==>Game draw";
	cin.ignore();
	cin.get();
	return 0;
}

// Check the board for a winner.
// Returning a -1 is keep playing
// Returning a 0 is a draw (or cat wins)
// Returning a 1 shows a winner
int checkForWinner()
{
	//Check for win
	if ((boardTile[1] == boardTile[2] && boardTile[2] == boardTile[3])		//Row 1 fill
		|| (boardTile[4] == boardTile[5] && boardTile[5] == boardTile[6])	//Row 2 fill
		|| (boardTile[7] == boardTile[8] && boardTile[8] == boardTile[9])	//Row 3 fill
		|| (boardTile[1] == boardTile[4] && boardTile[4] == boardTile[7])	//Column 1 fill
		|| (boardTile[2] == boardTile[5] && boardTile[5] == boardTile[8])	//Column 2 fill
		|| (boardTile[3] == boardTile[6] && boardTile[6] == boardTile[9])	//Column 3 fill
		|| (boardTile[1] == boardTile[5] && boardTile[5] == boardTile[9])	//Top Left to Bottom Right Fill
		|| (boardTile[3] == boardTile[5] && boardTile[5] == boardTile[7]))	//Top Right to Bottom Left Fill
	{
		return 1;
	}
	//Check for cat
	else if (boardTile[1] != '1' && boardTile[2] != '2' && boardTile[3] != '3'
		&& boardTile[4] != '4' && boardTile[5] != '5' && boardTile[6] != '6'
		&& boardTile[7] != '7' && boardTile[8] != '8' && boardTile[9] != '9')
	{
		return 0;
	}
	//Continue game
	else
	{
		return -1;
	}
}

//  Draw the board with the player marks
void drawBoard()
{
	system("cls");
	cout << "\n\n\tTic Tac Toe\n\n";
	cout << "Player 1 has 'X'  -  Player 2 has 'O'" << endl << endl;
	cout << endl;
	cout << "     |     |     " << endl;
	cout << "  " << boardTile[1] << "  |  " << boardTile[2] << "  |  " << boardTile[3] << endl;
	cout << "_____|_____|_____" << endl;
	cout << "     |     |     " << endl;
	cout << "  " << boardTile[4] << "  |  " << boardTile[5] << "  |  " << boardTile[6] << endl;
	cout << "_____|_____|_____" << endl;
	cout << "     |     |     " << endl;
	cout << "  " << boardTile[7] << "  |  " << boardTile[8] << "  |  " << boardTile[9] << endl;
	cout << "     |     |     " << endl << endl;
}

//Check if the player's move is valid or if the tile has already been taken
bool checkValidMove(int choice)
{
	bool isValid = false;
	char aChar = '0' + choice;

	if (choice > 0 && choice <= 9) {
		if (boardTile[choice] == aChar){
			isValid = true;
		}
	}

	return isValid;
}