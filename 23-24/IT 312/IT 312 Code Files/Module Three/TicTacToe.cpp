// TicTacToe.cpp: Follow along with the comments to create a fully functional Tic Tac Toe game
// that uses function calls.  Each function will get called multiple times during the execution 
// of the code, however, the code itself only needed to be written once.  Also notice the use of 
// an array to store the contents of the board.  The comments marked with a TODO denote where code
// needs to be added.


#include <iostream>
using namespace std;

char boardTile[10] = { 'o', '1', '2', '3', '4', '5', '6', '7', '8', '9' };

//Write the function declarations
bool checkValidMove(int);
void drawBoard();
//TODO: Write the declaration for the function that checks for a winner

int main()
{
	int player = 1, i, choice;
	char mark;
	bool isMoveValid = false;
	do
	{
		//TODO: Call the function that draws the game board

		player = (player % 2) ? 1 : 2;
		cout << "Player " << player << ", enter a number:  ";
		cin >> choice;
		mark = (player == 1) ? 'X' : 'O';

		//TODO: Call the checkValidMove function, make sure to save the return value in one of the variables

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
	//TODO: Read through the code in this function.  Based on the commented rules before the function, determine 
	//what type of return statement belongs in each of the comments below.
	if ((boardTile[1] == boardTile[2] && boardTile[2] == boardTile[3])
		|| (boardTile[4] == boardTile[5] && boardTile[5] == boardTile[6])
		|| (boardTile[7] == boardTile[8] && boardTile[8] == boardTile[9])
		|| (boardTile[1] == boardTile[4] && boardTile[4] == boardTile[7])
		|| (boardTile[2] == boardTile[5] && boardTile[5] == boardTile[8])
		|| (boardTile[3] == boardTile[6] && boardTile[6] == boardTile[9])
		|| (boardTile[1] == boardTile[5] && boardTile[5] == boardTile[9])
		|| (boardTile[3] == boardTile[5] && boardTile[5] == boardTile[7]))
	{
		//Insert return statement
	}
	else if (boardTile[1] != '1' && boardTile[2] != '2' && boardTile[3] != '3'
		&& boardTile[4] != '4' && boardTile[5] != '5' && boardTile[6] != '6'
		&& boardTile[7] != '7' && boardTile[8] != '8' && boardTile[9] != '9')
	{
		//Insert return statement
	}
	else
	{
		//Insert return statement
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
//TODO: Based on the function initiation at the beginning of the program, write the function signature, make sure the variable names are consistent

{
	bool isValid = false;
	char aChar = '0' + choice;
	if (choice > 0 && choice <= 9){
		if (boardTile[choice] == aChar){
			isValid = true;
		}
	}

	return isValid;
}