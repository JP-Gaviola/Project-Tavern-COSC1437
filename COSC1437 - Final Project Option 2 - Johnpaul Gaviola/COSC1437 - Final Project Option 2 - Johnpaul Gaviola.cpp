// COSC1437 - Final Project Option 2 - Johnpaul Gaviola.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <fstream>
#include <ostream>
#include <sstream>
#include <thread>
#include <chrono>

#include "DialougeClass.h"
#include "GameStats.h"
#include "PlayerStats.h"
#include "TimeClass.h"
#include "Water.h"


using namespace std;

int generateQuota(int day)
{
    int baseQuota = (day * 10) + 20;
    return (baseQuota) + (baseQuota * 0.5);
}

string getTime(TimeClass& timeClass)
{
    string timeTemp = "";
    timeTemp += to_string(timeClass.Hour) + ":";
    if (timeClass.Min == 0)
    {
        timeTemp += "00";
    }
    else if (timeClass.Min < 10 && timeClass.Min > 0)
    {
        timeTemp += "0" + to_string(timeClass.Min);
    }
    else
    {
        timeTemp += to_string(timeClass.Min);
    }

    return timeTemp;
}

void endTime(TimeClass& timeClass, thread& t1)
{
    timeClass.timeActive = false;
    timeClass.Hour = 9;
    timeClass.Min = 0;
    t1.detach();
}

void printStatus(Dialouge& diaObj, GameStats* gameStats, PlayerStats* playerStats, TimeClass& timeClass)
{
    diaObj.writeDialouge("////////////////Game Stats///////////////////", false, false);
    diaObj.writeDialouge("Current Earnings: " + to_string(gameStats->getEarnings()), false, false);
    diaObj.writeDialouge("Quota: " + to_string(gameStats->getQuota()), false, false);
    diaObj.writeDialouge("Current Time: " + getTime(timeClass), false, false);
    diaObj.writeDialouge("Happy Hour: " + to_string(gameStats->checkHappyHour()), false, false);
    diaObj.writeDialouge("////////////////Player Stats/////////////////", false, false);
    diaObj.writeDialouge("Total Money: " + to_string(playerStats->getGold()), false, false);
    diaObj.writeDialouge("Experience: " + to_string(playerStats->getExp()), false, false);
    diaObj.writeDialouge("Reputation: " + to_string(playerStats->getRep()), false, false);
    diaObj.writeDialouge("Proficency: " + to_string(playerStats->getProf()), false, false);
    
}


int main()
{
    //Menu sequence////////////////////////////////////////////////////////////////////
    string userChoice = "";
    Dialouge diaObj;
    bool loadgame = false;

    diaObj.printLogo();
    diaObj.writeDialouge("The Saderan Empire's finest tavern awaits you!", false, true);
    diaObj.writeDialouge("Options: New Game / Load Game / Exit", false, true);

    do
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
            diaObj.writeDialouge("See you next time!", false, true);
            return 0;
        }
    } while (userChoice != "Exit");

    //Creating game elements
    //Can add loading text later
    //Objects
    GameStats* gameStats = nullptr;
    PlayerStats* playerStats = nullptr;
    TimeClass timeClass;

    if (loadgame)
    {
        //Load objects respectively

    }
    else
    {
        //New game
        gameStats = new GameStats;
        playerStats = new PlayerStats;
    }
    //Load game objects
    int gameResult = -1;

    //Start the game!

    if (gameStats->getDay() == 0)
    {
        //Intro sequence
        //New game
        
        diaObj.writeDialouge("Blahblah intro sequence", false, true);
    }
    else
    {
        //loaded game
    }
    gameStats->setQuota(generateQuota(gameStats->getDay()));

    
    //Gameplay loop starts!
    diaObj.writeDialouge("You finish final preparations, all you need to do now is flip the open sign...", true, true);
    diaObj.writeDialouge("Let's do this!", false, true);
    printStatus(diaObj, gameStats, playerStats, timeClass);

    thread t1(&TimeClass::startTime, &timeClass);
    

    //Gameplay loop 
    while (timeClass.reachedEnd == false)
    {
        //Main game! 
    }

    //cout << gameStats.getDay();
    //lets assume we're making a drink
    // Water newDrink;
    // cout << newDrink.prepareItem() << endl;

    delete playerStats;
    delete gameStats;
    endTime(timeClass, t1);
    return 0;
} 

