/*Copyright (c) 2015 Southern New Hampshire University

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/


#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;
int main()
{
//Seed the random number generator
srand(time(0));
int selectedNumber = rand()%20+1;int numberOfTries = 0;int inputtedGuess;
cout << "Guess My Number Game\n\n";
//Ask the user for a value until the correct number is entered
do{
cout << "Enter a guess between 1 and 20:";
cin >> inputtedGuess;
++numberOfTries;
if(inputtedGuess>20 || inputtedGuess<1) {cout << "Your guess is out of range. \n\n";}
else if (inputtedGuess > selectedNumber){cout << "Too high!\n\n";}
else if (inputtedGuess < selectedNumber){cout << "Too low!\n\n";}
} while (inputtedGuess != selectedNumber);
//Congratulate the user and end the program
cout << "\nCongratulations! You solved it in " << numberOfTries << " tries!\n";
return 0;
}