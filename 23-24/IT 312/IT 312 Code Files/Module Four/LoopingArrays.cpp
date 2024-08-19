// LoopingArrays.cpp : This program loops through to create an array based on user input and then 
// sorts the array in order of smallest integer to largest.  Format the code following the code
// styling document.
//


#include <iostream>
#include <cstdlib>
using namespace std;

void main()
{
int array[10], t;
for (int x = 0; x<10; x++){
cout << "Enter Integer No. " << x + 1 << " : " << endl;
cin >> array[x];}
for (int x = 0; x<10; x++){
for (int y = 0; y<9; y++){
if (array[y]>array[y + 1]){
t = array[y];
array[y] = array[y + 1];
array[y + 1] = t;}}}
cout << "Array in ascending order is : ";
for (int x = 0; x<10; x++)
cout << endl << array[x];
return;}