/*
Name		: Nathan Hallam
Course		: IT-132
Data		: 24th March, 2024
Project NO	: 3-2
File Name	: HallamNathan_AnArrayOfTreasure.cpp
Description : Using a boolean array, track user inputs to determine what "chests" have been found with only one chest containing a level.
              Decided to add more content to the program by having it choose a random chest from 1-5 and the program continues to loop until the user decides to quit.
              Program will track users level, amount of guesses taken to reach their current point, and the guess accuracy - statistics listed at program close.
*/

#include <cstdlib>
#include <iostream>
#include <string>                                           //needed for stoi() function
using namespace std;

//Prints all unselected chests to the console
void printAvailableChests(bool chests[], int chestArrLength = -1) {
    
    std::cout << "(";    //Start text container

    for (int i = 0; i < chestArrLength; i++) {

        //If chest has not been opened, print to console position in array
        if (chests[i] != true) {
            std::cout << " " << i + 1;
        }
    }

    std::cout << " ) " << endl;  //End text container
}


int main() {
    std::cout << "Program Start!\n";

    bool chests[5] = { false };                             //Initializes array of chests
    string userInput;                                       //Stores user input
    int randomNumber = -1,                                  //Stores a random number to initialize the loot chest
        chestArrLength = sizeof(chests) / sizeof(*chests),  //Cache length of array for use in operations
        level = 0,                                          //Current level
        guesses = 0;                                        //Number of guesses taken
    double guessAccuracy = 0;                               //How well the user guessed what the correct chest was

    //Generate random number
    srand(time(nullptr));                                   //Set a random seed based on current time
    randomNumber = rand() % chestArrLength;                 //Generate a random number from 0 - array length

    //Core loop
    do {
        loop_start: ;                                       //Used by input not int guard clause to leave for loop

        std::cout << "\nType 'Q' to quit program" << endl;  //Prompt to quit program
        std::cout << "Select a chest from the selection ";  //Prompt for input

        //Get available chests based on length of array
        printAvailableChests(chests, chestArrLength);

        cin >> userInput;                                   //Store input

        //Guard Clause: Check if closing application
        if (userInput == "q" || userInput == "Q") {
            break;  //Break out of while loop, skip everything below
        }

        //Guard Caluse: Input is not an int
        for (char l : userInput) {
            //If character in string is a number, continue checking
            if (isdigit(l)) {
                continue;
            }

            //Prompt user for proper input
            std::cout << "\nDidn't realize there was a chest called that...\n"
                 << "Choose an actual chest this time ";

            printAvailableChests(chests, chestArrLength);

            goto loop_start;
        }

        //Guard Claus: Input out of range
        if (stoi(userInput) <= 0 || stoi(userInput) > chestArrLength) {
            //Prompt user for proper input
            std::cout << "\nYou have chosen a mystical chest that does not exist!\n" 
                 << "Choose a chest that is on your plane of existance ";

            printAvailableChests(chests, chestArrLength);

            std::cout << endl;

            continue;
        }

        //Guard Clause: Chest already selected
        if (chests[(stoi(userInput)) - 1] == true) {
            //Prompt user for proper input
            std::cout << "\nThere appears to be nothing in this chest...\n"
                 << "\nOh wait... this looks familiar... You already opened this one!"
                 << "\nChoose a chest that has not already been opened! ";

            printAvailableChests(chests, chestArrLength);

            std::cout << endl;

            continue;
        }

        std::cout << "You opened a chest..." << endl;       //Print chest as opened
        chests[stoi(userInput) - 1] = true;                 //Set chest to be opened

        //If selected prize chest
        if (stoi(userInput) == randomNumber + 1) {
            
            level++;

            std::cout << "\nThere appears to be loot in this chest...\n"
                 << "\You leveled up to level "
                 << level
                 << "\nNew chests are available to you!";
            
            std::cout << endl;

            randomNumber = rand() % chestArrLength;         //Generate a random number from 0 - array length

            for (int i = 0; i < chestArrLength; i++) {
                chests[i] = false;
            }
        }
        //If not prize chest
        else {
            
            std::cout << "\nThere appears to be nothing of too much interest in this chest...\n"
                 << "\nPerhaps another chest has what you are looking for?";

            std::cout << endl;
        }

        guesses++;                                          //Increment guesses taken

    } while (userInput != "q" && userInput != "Q");


    //Ending statistics
    guessAccuracy = static_cast<double>(level) / guesses * 100;

    std::cout << "\n\nYou quit with\n"
        << level
        << " levels\n"
        << guesses
        << " guesses\n"
        << guessAccuracy 
        << "% accuracy\n";

    return 0;
}