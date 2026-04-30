// COSC1437 - Final Project Option 2 - Johnpaul Gaviola.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <fstream>
#include <ostream>
#include <sstream>
#include <thread>
#include <chrono>
#include <vector>
#include <cstdlib>
#include <ctime>   

#include "DialougeClass.h"
#include "GameStats.h"
#include "PlayerStats.h"
#include "TimeClass.h"
#include "ElapsedTime.h"


///Order Items
#include "OrderItem.h"
#include "Water.h"
#include "Bread.h"
#include "Fish.h"

///Customers
#include "Customer.h"
#include "TownResident.h"
#include "Ingis.h"


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

void selectRandomCustomer(Customer*& baseCust, int playerRep)
{
    if (baseCust != nullptr) { delete baseCust; baseCust = nullptr; }

        //Math rand with seed on current system time 
        srand(time(0));

        int randomNum = std::rand() % 2 + 1; //1 to 2

        switch (randomNum) {
        case 1:
            baseCust = new TownResident;
            break;
        case 2:
            baseCust = new Ingis;
            break;
        }
   
}

OrderItem* stringToOrderItem(string inp)
{
    OrderItem* newItem = nullptr;
    if (inp == "Water")
    {
        newItem = new Water;
    }
    else if (inp == "Bread")
    {
        newItem = new Bread;
    }
    else if (inp == "Fish")
    {
        newItem = new Fish;
        
    }
    return newItem;
}

void createOrder(Customer*& currCustomer, int playerExp, vector<OrderItem*>& order)
{
    int PrefCosts = 0;
    int budget = currCustomer->getBudget();
    //Add preferences first if they pass the exp check 
    for (int i = 0; i < currCustomer->getPrefSize(); i++)
    {
        OrderItem* currentItem = stringToOrderItem(currCustomer->getPrefAt(i));
        
        if (currentItem->getExpNeeded() <= playerExp)
        {
            
            
            PrefCosts += currentItem->getCost();
            
            order.push_back(currentItem);
        }
    }
    budget -= PrefCosts;
    //cout << "Customer Budget: " << budget << endl;
    //cout << "Test : " << order[0]->getName() << endl;



    //ADDLATER Add one random item if to order if not strictly preferences / exp req is met 
    if (currCustomer->getOnlyPref() == false)
    {

    }
}

void askSelectOrder(Dialouge& diaObj, GameStats* gameStats, PlayerStats* playerStats, vector<OrderItem*> prepOrder, TimeClass& timeClass)
{
    int i;
    string prepped = "";
    string diaChoiceLocal;
    
    do
    {
        prepped = "";
        for (i = 0; i < prepOrder.size(); i++)
        {
            prepped += prepOrder[i]->getName() + " R: " + to_string(prepOrder[i]->getItemScore()) + " | ";
        }

        diaObj.writeDialouge("//////////////PREP///////////////", false, false);
        diaObj.writeDialouge("Current Time: " + getTime(timeClass), false, false);
        diaObj.writeDialouge("Currently Prepped: " + prepped, false, true);
        diaObj.writeDialouge("What item would you like to prepare/do?", false, true);
        diaObj.writeDialouge("Water - Bread - Fish(E:10) - Cake - Meat - Submit Order - Remove Item", false, false);

        diaObj.askUserChoice(diaChoiceLocal);
        if (diaChoiceLocal == "Water")
        {
            //check stock later move it to player stats
            //Stock check passed
            Water* tempWater = new Water;
            tempWater->prepareItem();
            prepOrder.push_back(tempWater);
        }
        else if (diaChoiceLocal == "Bread")
        {
            Bread* tempBread = new Bread;
            tempBread->prepareItem();
            prepOrder.push_back(tempBread);
        }
        else if (diaChoiceLocal == "Fish")
        {
            Fish tempFish;
            if (playerStats->getExp() > tempFish.getExpNeeded())
            {

            }
            else
            {
                diaObj.writeDialouge("Not Enough Experience!", false, true);
            }
        }
        else if (diaChoiceLocal == "Remove Item")
        {
            diaObj.writeDialouge("What number item would you like to remove? (0,1,2,3...)", false, true);
            diaObj.writeDialouge("Currently Prepped: " + prepped, false, true);
            diaObj.askUserChoice(diaChoiceLocal);
            int converted = stoi(diaChoiceLocal);
            if (converted >= 0 && converted < prepOrder.size())
            {
                swap(prepOrder[converted], prepOrder.back());
                prepOrder.pop_back();
            }
            else
            {
                diaObj.writeDialouge("Invalid - No items removed.", false, true);
            }
        }
    } while (diaChoiceLocal != "Submit Order");
    
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
    string diaChoiceMain;

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
    //Gameplay Elements
    vector<OrderItem*> currentOrder;
    vector<OrderItem*> currentPrep;
    
    
    //Gameplay loop starts!
    diaObj.writeDialouge("You finish final preparations, all you need to do now is flip the open sign...", true, true);
    diaObj.writeDialouge("Let's do this!", false, true);
    printStatus(diaObj, gameStats, playerStats, timeClass);

    thread t1(&TimeClass::startTime, &timeClass);
    

    //Gameplay loop 
    while (gameResult == -1) //Only continue if time isnt 21
    {
        
        //Main game! 
        while (timeClass.reachedEnd == false)
        {
           
            //FIXME: add random customer picker later 
            Customer* currCustomer = nullptr;
            
            selectRandomCustomer(currCustomer, playerStats->getRep());
             
            diaObj.writeDialouge("The Tavern door swings open...", false, true);

            diaObj.writeDialouge("CUSTOMER: " + currCustomer->getName(), false, true);
            diaObj.writeDialouge(currCustomer->getDEnter(), false, true);

            if (playerStats->getRep() > currCustomer->getMinRep())
            {
                diaObj.writeDialouge("Take their order? | Yes, No", false, true);
                do
                {
                    diaObj.askUserChoice(diaChoiceMain);
                    if (diaChoiceMain == "No")
                    {
                        diaObj.writeDialouge(currCustomer->getDdeclined(), false, true);
                        break;
                    }
                } while (diaChoiceMain != "Yes");
            }
            else
            {
                diaObj.writeDialouge(currCustomer->getDrepTooLow(), false, true);
                diaObj.writeDialouge("Reputation is too low to serve this customer!", false, true);
                continue;
            }
            if (diaChoiceMain == "No") { continue; }
           
            createOrder(currCustomer, playerStats->getExp(), currentOrder);
            //Ordering sequence!!
            diaObj.writeDialouge("Current Time: " + getTime(timeClass), false, false);
            diaObj.writeDialouge(currCustomer->getDstartOrder(), false, true);
            diaObj.writeDialouge("///////////ORDER///////////", false, false);
            for (int i = 0; i < currentOrder.size(); i++)
            {
                
                diaObj.writeDialouge(currentOrder[i]->getName(), false, true);
            }
            diaObj.writeDialouge("///////////ORDER///////////", false, false);

            askSelectOrder(diaObj, gameStats, playerStats, currentPrep, timeClass);

            diaObj.writeDialouge(currCustomer->getDsubmitOrder(), false, false);

            //Grade order 

            int custGrade = 0;

            //FIXME TOMORROW, add rating system check calandar for next

            
        }


        //Day ended!!
        if (gameResult == 1)
        {
            //Passed quota
        }
        else if (gameResult == 2)
        {
            //failed
        }
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

