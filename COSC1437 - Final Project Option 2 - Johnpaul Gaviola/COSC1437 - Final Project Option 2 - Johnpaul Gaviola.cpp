// COSC1437 - Final Project Option 2 - Johnpaul Gaviola.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <stdlib.h>     //for using the function sleep
using namespace std;


//Writes dialouge to iostream one at a time 
void writeDialouge(string inpText, bool keyContinue)
{
    cout << inpText << endl;
    if (keyContinue) { system("pause");}
}

int main()
{
    //Intro sequence... for main menu 

    //Will make a class file solely for dialouge soon...
    string introText1 = "The morning sun strikes through your window. Landing itself on not only the floor, but grazing your closed eyes, just enough to bring you out of your deep slumber.";
    string introText2 = "You step out of your bed, and head to the restroom to freshenup...";
    string introText3 = "Time to get ready for another day in the Saderan Empire's most popular tavern, 'Happy Hour'.";

    writeDialouge(introText1, true);
    writeDialouge(introText2, true);
    writeDialouge(introText3, true);

    

    return 0;
} 

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
