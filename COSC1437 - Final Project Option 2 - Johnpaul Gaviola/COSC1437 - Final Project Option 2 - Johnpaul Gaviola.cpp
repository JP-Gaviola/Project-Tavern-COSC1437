// COSC1437 - Final Project Option 2 - Johnpaul Gaviola.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <fstream>
#include <ostream>
#include <sstream>

#include "DialougeClass.h"
#include "GameStats.h"
#include "PlayerStats.h"
#include "TimeClass.h"
#include "Water.h";



using namespace std;


int main()
{
    //Menu sequence////////////////////////////////////////////////////////////////////
    string userChoice = "";
    Dialouge diaObj;
    bool loadgame = false;

    diaObj.printLogo();
    diaObj.writeDialouge("The Saderan Empire's finest tavern awaits you!", false);
    diaObj.writeDialouge("Options: New Game / Load Game / Exit", false);

    
    while (userChoice != "HoshinoIchika1289189274891274812740127102957124")
    {
        diaObj.askUserChoice(userChoice);

        if (userChoice == "New Game")
        {
            break;
        }
        else if (userChoice == "Load Game")
        {
            //Do later, when we have saving
            loadgame = true;
            break;
        }
        else if (userChoice == "Exit")
        {
            diaObj.writeDialouge("See you next time!", false);
            return 0;
        }

    }

    //Creating game elements
    //Can add loading text later
    //Objects
    GameStats gameStats;
    PlayerStats playerStats;

    if (loadgame)
    {
        //Load objects respectively
    }

    //cout << gameStats.getDay();
    //lets assume we're making a drink
    // Water newDrink;
    // cout << newDrink.prepareItem() << endl;


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
