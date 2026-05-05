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
#include "CustomerTimer.h"
#include "InventoryManager.h"
#include "EventManager.h"

///Order Items
#include "OrderItem.h"
#include "Water.h"
#include "Bread.h"
#include "Fish.h"
#include "Cola.h"
#include "Ham.h"

///Customers
#include "Customer.h"
#include "TownResident.h"
#include "Ingis.h"
#include "PasserBy.h"
#include "HigherResident.h"
#include "SuperHighResident.h"

using namespace std;

struct {
    //GameStats
    int baseDay;
    int baseEarnings;
    //Player
    int baseExp;
    int baseGold;
    int baseRep;
    int baseProf;
    //Stock
    int baseWater;
    int baseCola;
    int baseBread;
    int baseFish;
    int baseHam;
} baseStats;

int generateQuota(int day)
{
    int baseQuota = (day * 10) + 20;
    return (baseQuota) + (baseQuota * 0.5);
    //return 5 + day; // for debug
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

int randNum(int from, int to)
{
    //Math rand with seed on current system time 
    return rand() % to + from; //1 to 2
}

void printStatus(Dialouge& diaObj, GameStats* gameStats, PlayerStats* playerStats, TimeClass& timeClass)
{
    diaObj.writeDialouge("////////////////Game Stats///////////////////", false, false);
    diaObj.writeDialouge("Day: " + to_string(gameStats->getDay()), false, false);
    diaObj.writeDialouge("Quota: " + to_string(gameStats->getQuota()), false, false);
    diaObj.writeDialouge("Today's Earnings: " + to_string(gameStats->getEarnings()), false, false);
    diaObj.writeDialouge("Current Time: " + getTime(timeClass), false, false);
    string happyStatus = "No";
    if (gameStats->checkHappyHour())
    {
        happyStatus = "Yes";
    }
    diaObj.writeDialouge("Happy Hour: " + happyStatus, false, false);
    diaObj.writeDialouge("////////////////Player Stats/////////////////", false, false);
    diaObj.writeDialouge("Total Money: " + to_string(playerStats->getGold()), false, false);
    diaObj.writeDialouge("Experience: " + to_string(playerStats->getExp()), false, false);
    diaObj.writeDialouge("Reputation: " + to_string(playerStats->getRep()), false, false);
    diaObj.writeDialouge("Proficency: " + to_string(playerStats->getProf()), false, false);
    
}

void printOrder(Dialouge& diaObj ,vector<OrderItem*> currentOrder)
{
    diaObj.writeDialouge("///////////ORDER///////////", false, false);
    for (int i = 0; i < currentOrder.size(); i++)
    {

        diaObj.writeDialouge(currentOrder[i]->getName(), false, true);
    }
    diaObj.writeDialouge("///////////ORDER///////////", false, false);
}

void selectRandomCustomer(Customer*& baseCust, int playerRep, GameStats* gameStats)
{
    if (baseCust != nullptr) { delete baseCust; baseCust = nullptr; }

    int randomNum;

    if (gameStats->getDay() == 0)
    {
        randomNum = randNum(1, 2);
    }
    else if (gameStats->getDay() == 1)
    {
        randomNum = randNum(1, 3);
    }
    else
    {
        randomNum = randNum(1, 5);
    }


        switch (randomNum) {
        case 1:
            baseCust = new TownResident;
            break;
        case 2:
            baseCust = new Ingis;
            break;
        case 3:
            baseCust = new PasserBy;
            break;
        case 4:
            baseCust = new HigherResident;
            break;
        case 5:
            baseCust = new SuperHighResident;
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
    else if (inp == "Cola")
    {
        newItem = new Cola;

    }
    else if (inp == "Ham")
    {
        newItem = new Ham;

    }
    return newItem;
}


void createOrder(Customer*& currCustomer, int playerExp, vector<OrderItem*>& order, GameStats* gameStats)
{
    int PrefCosts = 0;
    int budget = currCustomer->getBudget();
    OrderItem* currentItem;
    //Add preferences first if they pass the exp check 
    for (int i = 0; i < currCustomer->getPrefSize(); i++)
    {
        currentItem = stringToOrderItem(currCustomer->getPrefAt(i));
        
        if (currentItem->getExpNeeded() <= playerExp)
        {
            
            PrefCosts += currentItem->getCost();
            
            order.push_back(currentItem);
        }
    }
    budget -= PrefCosts;
    //cout << "Customer Budget: " << budget << endl;
    //cout << "Test : " << order[0]->getName() << endl;



    //ADDLATER Add one random item if to order based on day amount capped at 3, only bread or water / basic item
    if (currCustomer->getOnlyPref() == false)
    {
        int amtAdd = gameStats->getDay();
        if (amtAdd > 3) { amtAdd = 3; }
        if (amtAdd == 0) { return; }

        for (int i = 0; i < amtAdd; i++)
        {
            switch (randNum(1, 3))
            {
            case 1:
                currentItem = stringToOrderItem("Water");
                if (currentItem->getCost() > budget) { return; }
                order.push_back(currentItem);
                break;
            case 2:
                
                currentItem = stringToOrderItem("Bread");
                if (currentItem->getCost() > budget) { return; }
                order.push_back(currentItem);
                break;
            case 3:
                currentItem = stringToOrderItem("Cola");
                if (currentItem->getCost() > budget) { return; }
                order.push_back(currentItem);
                break;
            }
        }
    }
}

//Two functions to help with grading order
double scoreItem(double keyVal, double subVal) {
    if (keyVal == 0) return 0;

    double error = abs(keyVal - subVal) / keyVal;
    double score = 100 * (1 - error);

    if (score < 0) score = 0;
    if (score > 100) score = 100;

    return score;
}




int findIndex(const vector<OrderItem*>& table, string name) {
    for (int i = 0; i < table.size(); i++) {
        if (table[i]->getName() == name) {
            return i;
        }
    }
    return -1; // not found
}

bool is_number(const std::string& s)
{
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}


int askSelectOrder(Dialouge& diaObj, GameStats* gameStats, PlayerStats* playerStats, vector<OrderItem*> prepOrder, TimeClass& timeClass, vector<OrderItem*> currentOrder, InventoryManager& inventoryManager)
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
        string optionList = "Water(S:" + to_string(inventoryManager.getWaterStock());
        optionList += ") - Cola(S:" + to_string(inventoryManager.getColaStock());
        optionList += ") - Bread(S:" + to_string(inventoryManager.getBreadStock());
        optionList += ") - Fish(S:" + to_string(inventoryManager.getFishStock());
        optionList += ") - Ham(S:" + to_string(inventoryManager.getHamStock());
        optionList += ") -  Submit Order - Remove Item - View Order";

        diaObj.writeDialouge(optionList, false, false);

        diaObj.askUserChoice(diaChoiceLocal);
        if (diaChoiceLocal == "Water")
        {
            //Stock check 
            if (inventoryManager.getWaterStock() <= 0) { diaObj.writeDialouge("Not enough stock!", true, true); continue; }
            Water* tempWater = new Water;
            tempWater->prepareItem(playerStats);
            prepOrder.push_back(tempWater);
            inventoryManager.addWaterStock(-1);
        }
        else if (diaChoiceLocal == "Cola")
        {
            if (inventoryManager.getColaStock() <= 0) { diaObj.writeDialouge("Not enough stock!", true, true); continue; }
            Cola* tempCola = new Cola;
            tempCola->prepareItem(playerStats);
            prepOrder.push_back(tempCola);
            inventoryManager.addColaStock(-1);
        }
        else if (diaChoiceLocal == "Bread")
        {
            if (inventoryManager.getBreadStock() <= 0) { diaObj.writeDialouge("Not enough stock!", true, true); continue; }
            Bread* tempBread = new Bread;
            tempBread->prepareItem(playerStats);
            prepOrder.push_back(tempBread);
            inventoryManager.addBreadStock(-1);
        }
        else if (diaChoiceLocal == "Fish")
        {
            if (inventoryManager.getFishStock() <= 0) { diaObj.writeDialouge("Not enough stock!", true, true); continue; }
            Fish* tempFish = new Fish;
            
            tempFish->prepareItem(playerStats);
            prepOrder.push_back(tempFish);
            inventoryManager.addFishStock(-1);
        }
        else if (diaChoiceLocal == "Ham")
        {
            if (inventoryManager.getHamStock() <= 0) { diaObj.writeDialouge("Not enough stock!", true, true); continue; }
            Ham* tempHam = new Ham;

            tempHam->prepareItem(playerStats);
            prepOrder.push_back(tempHam);
            inventoryManager.addHamStock(-1);
        }


        else if (diaChoiceLocal == "Remove Item")
        {
            diaObj.writeDialouge("What number item would you like to remove? (0,1,2,3...)", false, true);
            diaObj.writeDialouge("Currently Prepped: " + prepped, false, true);
            diaObj.askUserChoice(diaChoiceLocal);
            int converted;
                if (is_number(diaChoiceLocal)) { converted = stoi(diaChoiceLocal); }
                else { converted = 99999; } //it is physically impossible to reach 99999 itenms in an order fight me
             
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
        else if (diaChoiceLocal == "View Order")
        {
            printOrder(diaObj, currentOrder);
        }
    } while (diaChoiceLocal != "Submit Order");
    
    //Player submitted Order
    //Calculate rating out of 100 and return 
    int matchCount = 0;
    double totalItemScore = 0;

    //check customer order 
    for (int i = 0; i < currentOrder.size(); i++) {
        string keyName = currentOrder[i]->getName();
        double keyVal = currentOrder[i]->getItemScore();

        int index = findIndex(prepOrder, keyName);

        if (index != -1) {
            matchCount++;

            double subVal = prepOrder[index]->getItemScore();

            double itemScore = scoreItem(keyVal, subVal);
            totalItemScore += itemScore;
        }
    }

    int totalKeyItems = currentOrder.size();

    if (totalKeyItems == 0) return 0;

    //M = match ratio
    double M =  (double)matchCount / (currentOrder.size() + prepOrder.size() - matchCount);

    //A = average score
    double A = (matchCount > 0) ? totalItemScore / matchCount : 0; //Left true, right false

    //Final score
    double finalScore = M * A;

    //Event 
    EventManager tempEvent;
    tempEvent.pickOneRandomEvent(diaObj, gameStats, playerStats, inventoryManager);

    return finalScore;

}



int askBuy(Dialouge& diaObj)
{
    diaObj.writeDialouge("How much would you like to purchase?", false, false);
    string localDiaChoice;
    diaObj.askUserChoice(localDiaChoice);
    if (is_number(localDiaChoice))
    {
        return stoi(localDiaChoice);
    }
    else
    {
        return 0;
    }
}



void enterStockingPhase(Dialouge& diaObj, GameStats* gameStats, PlayerStats* playerStats, InventoryManager& inventoryManager)
{
    //Shows a shop and current money, and exp then purcahse stuff..
    string localDiaChoice;
    do
    {
       diaObj.writeDialouge("////////////////Player Stats/////////////////", false, false);
       diaObj.writeDialouge("Total Money: " + to_string(playerStats->getGold()), false, false);
       diaObj.writeDialouge("Experience: " + to_string(playerStats->getExp()), false, false);
       diaObj.writeDialouge("Reputation: " + to_string(playerStats->getRep()), false, false);
       diaObj.writeDialouge("Proficency: " + to_string(playerStats->getProf()), false, false);
       diaObj.writeDialouge("//////////////Tavern Supply Co.///////////////", false, false);
       diaObj.writeDialouge("Water : Price: " + to_string(inventoryManager.getWaterPrice()), false, false);
       diaObj.writeDialouge("Cola : Price: " + to_string(inventoryManager.getColaPrice()), false, false);
       diaObj.writeDialouge("Bread : Price: " + to_string(inventoryManager.getBreadPrice()), false, false);
       diaObj.writeDialouge("Fish : Price: " + to_string(inventoryManager.getFishPrice()) + " : Exp: " + to_string(inventoryManager.getFishExp()), false, false);
       diaObj.writeDialouge("Ham : Price: " + to_string(inventoryManager.getHamPrice()) + " : Exp: " + to_string(inventoryManager.getHamExp()), false, false);
       diaObj.writeDialouge("//////////////Store Inventory/////////////////", false, false);
       diaObj.writeDialouge("Water : " + to_string(inventoryManager.getWaterStock()), false, false);
       diaObj.writeDialouge("Cola : " + to_string(inventoryManager.getColaStock()), false, false);
       diaObj.writeDialouge("Bread : " + to_string(inventoryManager.getBreadStock()), false, false);
       diaObj.writeDialouge("Fish : " + to_string(inventoryManager.getFishStock()), false, false);
       diaObj.writeDialouge("Ham : " + to_string(inventoryManager.getHamStock()), false, false);
       diaObj.writeDialouge("//////////////////////////////////////////////", false, false);
       diaObj.writeDialouge("Type the item you would like to stock up on. Type 'Finish' when ready to move on!", false, true);
       //For Cant afford noti
       bool inBuy = false;
       bool couldntAfford = false;
       //Cost
       int cost = 0;
       //Ask user what they want to stock
       diaObj.askUserChoice(localDiaChoice);
       if (localDiaChoice == "Finish") { break; }
       //Ask user how much they want to stock
       int localStockChoice = askBuy(diaObj);
       if (localDiaChoice == "Water")
       {
           inBuy = true;
           //Can afford?
           cost = (inventoryManager.getWaterPrice() * localStockChoice);
           if (playerStats->getGold() >= cost)
           {
               inventoryManager.addWaterStock(localStockChoice);
           }
           else
           {
               couldntAfford = true;
           }
       }
       else if (localDiaChoice == "Cola")
       {
           inBuy = true;
           cost = (inventoryManager.getColaPrice() * localStockChoice);
           if (playerStats->getGold() >= cost)
           {
               inventoryManager.addColaStock(localStockChoice);
           }
           else
           {
               couldntAfford = true;
           }
       }
       else if (localDiaChoice == "Bread")
       {
           inBuy = true;
           cost = (inventoryManager.getBreadPrice() * localStockChoice);
           if (playerStats->getGold() >= cost)
           {
               inventoryManager.addBreadStock(localStockChoice);
           }
           else
           {
               couldntAfford = true;
           }
       }
       else if (localDiaChoice == "Fish")
       {
           inBuy = true;
           if (playerStats->getExp() >= inventoryManager.getFishExp())
           {
               cost = (inventoryManager.getFishPrice() * localStockChoice);
               if (playerStats->getGold() >= cost)
               {
                   inventoryManager.addFishStock(localStockChoice);
               }
               else
               {
                   couldntAfford = true;
               }
           }
           else
           {
               diaObj.writeDialouge("Not enough Experience!", true, true);
               continue;
           }
          
       }
       else if (localDiaChoice == "Ham")
       {
           inBuy = true;
           if (playerStats->getExp() >= inventoryManager.getHamExp())
           {
               cost = (inventoryManager.getHamPrice() * localStockChoice);
               if (playerStats->getGold() >= cost)
               {
                   inventoryManager.addHamStock(localStockChoice);
               }
               else
               {
                   couldntAfford = true;
               }
           }
           else
           {
               diaObj.writeDialouge("Not enough Experience!", true, true);
               continue;
           }

       }
       if (inBuy)
       {
           if (couldntAfford)
           {
               diaObj.writeDialouge("Can't afford / invalid input!", true, true);
           }
           else
           {
               playerStats->setGold(playerStats->getGold() - cost);
               diaObj.writeDialouge("Purchase Success!", true, true);
           }
       }


    } while (localDiaChoice != "Finish");
    diaObj.writeDialouge("You walk out of the supply store and begin stocking your tavern...", true, true);

}

bool saveGame(Dialouge& diaObj, GameStats* gameStats, PlayerStats* playerStats, InventoryManager& inventoryManager)
{
    diaObj.writeDialouge("Enter save file name:", false, true);
    string fileName;
    diaObj.askUserChoice(fileName);

    ofstream saveFile;
    saveFile.open(fileName + ".txt");
    if (saveFile.is_open())
    {
        //Game Stats
        saveFile << gameStats->getDay() << endl;
        //Player stats
        saveFile << playerStats->getExp() << endl;
        saveFile << playerStats->getGold() << endl;
        saveFile << playerStats->getRep() << endl;
        saveFile << playerStats->getProf() << endl;
        //Stock
        saveFile << inventoryManager.getWaterStock() << endl;
        saveFile << inventoryManager.getColaStock() << endl;
        saveFile << inventoryManager.getBreadStock() << endl;
        saveFile << inventoryManager.getFishStock() << endl;
        saveFile << inventoryManager.getHamStock() << endl;

        saveFile.close();

        diaObj.writeDialouge("Data Saved! REMEMBER THE NAME: " + fileName, true, true);

        return true;
    }
    else
    {
        return false;
    }
}

int convertStringtoInt(string toConvert)
{
    //Assume valid
    return stoi(toConvert);
}

bool loadGame(Dialouge& diaObj, GameStats* gameStats, PlayerStats* playerStats, InventoryManager& inventoryManager)
{
    diaObj.writeDialouge("Enter save file name:", false, true);
    string fileName;
    diaObj.askUserChoice(fileName);

    ifstream dataFile;
    dataFile.open(fileName + ".txt");
    if (dataFile.is_open() && dataFile.good())
    {
        //Start reading
        string tempstr;

        //Gamestats
        getline(dataFile, tempstr);
        gameStats->setDay(convertStringtoInt(tempstr)); //Day
        //Player Stats
        getline(dataFile, tempstr);
        playerStats->setExp(convertStringtoInt(tempstr)); //Exp
        getline(dataFile, tempstr);
        playerStats->setGold(convertStringtoInt(tempstr)); //Gold
        getline(dataFile, tempstr);
        playerStats->setRep(convertStringtoInt(tempstr)); //Rep
        getline(dataFile, tempstr);
        playerStats->setProf(convertStringtoInt(tempstr)); //Prof
        //Stock
        getline(dataFile, tempstr);
        inventoryManager.setWaterStock(convertStringtoInt(tempstr)); //Water
        getline(dataFile, tempstr);
        inventoryManager.setColaStock(convertStringtoInt(tempstr)); //Cola
        getline(dataFile, tempstr);
        inventoryManager.setBreadStock(convertStringtoInt(tempstr)); //Bread
        getline(dataFile, tempstr);
        inventoryManager.setFishStock(convertStringtoInt(tempstr)); //Fish
        getline(dataFile, tempstr);
        inventoryManager.setHamStock(convertStringtoInt(tempstr)); //Ham

        dataFile.close();

        diaObj.writeDialouge("Data Loaded!", true, true);

        return true;
    }
    else
    {
        return false;
    }


}

void setBaseStats(GameStats* gameStats, PlayerStats* playerStats, InventoryManager& inventoryManager)
{
    //Sets the current stats to base
    //Game
    baseStats.baseDay = gameStats->getDay();
    baseStats.baseEarnings = gameStats->getEarnings();
    //Player
    baseStats.baseExp = playerStats->getExp();
    baseStats.baseGold = playerStats->getGold();
    baseStats.baseRep = playerStats->getRep();
    baseStats.baseProf = playerStats->getProf();
    //Stock
    baseStats.baseWater = inventoryManager.getWaterStock();
    baseStats.baseCola = inventoryManager.getColaStock();
    baseStats.baseBread = inventoryManager.getBreadStock();
    baseStats.baseFish = inventoryManager.getFishStock();
    baseStats.baseHam = inventoryManager.getHamStock();
}

int main()
{
    srand(time(0));
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
    InventoryManager inventoryManager;
    GameStats* gameStats = new GameStats;
    PlayerStats* playerStats = new PlayerStats;
    TimeClass timeClass;
    string diaChoiceMain;

    if (loadgame)
    {
        //Load objects respectively
        if (!loadGame(diaObj, gameStats, playerStats, inventoryManager))
        {
            diaObj.writeDialouge("File operation failed!", true, true);
            return 1;
        }
    }
    //Load game objects
    int gameResult = -1;

    //Start the game!
    //Intro sequence
    if (gameStats->getDay() == 0)
    {
        
        //New game
        
        diaObj.writeDialouge("Blahblah intro sequence", false, true);
    }
    else
    {
        //loaded game intro sequence
        diaObj.writeDialouge("Blahblah loaded intro sequence", false, true);
    }

    //Store base stats here to be used when retrying
    setBaseStats(gameStats, playerStats, inventoryManager);

    bool loopLocker = true;

    gameStats->setQuota(generateQuota(gameStats->getDay()));
    //Gameplay Elements
    vector<OrderItem*> currentOrder;
    vector<OrderItem*> currentPrep;
    
    //Stocking phase
    enterStockingPhase(diaObj, gameStats, playerStats, inventoryManager);
    
    //Gameplay loop starts!
    diaObj.writeDialouge("You finish final preparations, all you need to do now is flip the open sign...", true, true);
    diaObj.writeDialouge("Let's do this!", false, true);

    //Start main game time in a different thread
    thread t1(&TimeClass::startTime, &timeClass, gameStats);
    

    //Gameplay loop 
    while (loopLocker) //Only continue if time isnt 21
    {
        
        //Main game! 
        while (loopLocker)
        {
           
            printStatus(diaObj, gameStats, playerStats, timeClass);
            Customer* currCustomer = nullptr;
            
            selectRandomCustomer(currCustomer, playerStats->getRep(), gameStats);
             
            diaObj.writeDialouge("The Tavern door swings open...", true, true);

            diaObj.writeDialouge("CUSTOMER: " + currCustomer->getName(), false, true);
            diaObj.writeDialouge(currCustomer->getDEnter(), false, true);

            if (playerStats->getRep() > currCustomer->getMinRep())
            {
                diaObj.writeDialouge("Take their order? | Yes, No", false, true);
                do
                {
                    diaObj.askUserChoice(diaChoiceMain);
                    if (diaChoiceMain == "No" || diaChoiceMain == "Yes")
                    {
                        break;
                    }
                } while (true);
            }
            else
            {
                //Rep too low dialogue
                diaObj.writeDialouge(currCustomer->getDrepTooLow(), false, true);
                diaObj.writeDialouge("Reputation is too low to serve this customer!", true, true);
                continue;
            }
            //Check for decline to move to next customer
            if (diaChoiceMain == "No")
            { 
                //Declined message
                diaObj.writeDialouge(currCustomer->getDdeclined(), false, true);
                //Lower players reputation
                diaObj.writeDialouge("You lost reputation: -1", true, false);
                playerStats->setRep(playerStats->getRep() - 1);

                continue; 
            }

            //Order was taken start a customer time in a different thread
            CustomerTimer localCustTimer;
            thread t2(&CustomerTimer::startTime, &localCustTimer);

           
            //Creates a order
            createOrder(currCustomer, playerStats->getExp(), currentOrder, gameStats);
            //Print time
            diaObj.writeDialouge("Current Time: " + getTime(timeClass), false, false);

            //Customer starts order text
            diaObj.writeDialouge(currCustomer->getDstartOrder(), true, true);

            //Print out order to player
            printOrder(diaObj,currentOrder);

            //start loop preparing order items, end with grading
            int orderGrade;
            orderGrade = askSelectOrder(diaObj, gameStats, playerStats, currentPrep, timeClass, currentOrder, inventoryManager);

            //Order submitted
            //Tips
            int tips = 0;
            int baseOrderGrade = 70;

            //Happy Hour
            if (timeClass.Hour == 17)
            {
                diaObj.writeDialouge("Happy Hour is active!! Tips are greatly increased and customers are less rowdy!", true, true);
                tips += 10;
                baseOrderGrade -= 20;
                gameStats->changeHappyHour(true);
            }
            else
            {
                gameStats->changeHappyHour(false);
            }

            //End timer
            localCustTimer.timeActive = false;
            int waitTime = localCustTimer.elapsed;
            t2.detach();

            //Submit Dialouge
            diaObj.writeDialouge(currCustomer->getDsubmitOrder(), true, true);


            //Grade order 
            //Score above 70 is passing 
            int localEarnings = 0;

            if (orderGrade >= baseOrderGrade + currCustomer->getRowdiness())
            {
                //Passed!!!
                //Check wait time 
                //Only allow tips when high grade
                if (waitTime <= currCustomer->getPatience())
                {
                    //Order submited in time
                    tips += 5;
                }
                else
                {
                    //Order submited took too long
                    diaObj.writeDialouge(currCustomer->getDWaitToLong(), true, true);
                }

                
                diaObj.writeDialouge(currCustomer->getDOrderGood(), true, true);

                //tips
                tips += orderGrade * 0.05;
                diaObj.writeDialouge("You've been tipped: " + to_string(tips), false, false);
                //Add local earnings to tips, can only earn tips if sent out with a good grade
                localEarnings += tips;

                //Rep
                diaObj.writeDialouge("You gained Reputation: 2", false, false);
                playerStats->setRep(playerStats->getRep() + 2);

                //Exp
                diaObj.writeDialouge("You gained Exp: 5", false, false);
                playerStats->setExp(playerStats->getExp() + 5);

                //Prof
                diaObj.writeDialouge("You gained Proficency: 1", true, false);
                playerStats->setProf(playerStats->getProf() + 1);
            }
            else
            {
                //Horrible food gread
                diaObj.writeDialouge(currCustomer->getDOrderBad(), true, true);

                //Rep
                diaObj.writeDialouge("You lost Reputation: -1", false, false);
                playerStats->setRep(playerStats->getRep() - 1);

                //Exp
                diaObj.writeDialouge("You gained Exp: 2", true, false);
                playerStats->setExp(playerStats->getExp() + 2);
            }

            //Give player the earnings + markup
            for (int i = 0; i < currentOrder.size(); i++)
            {

                localEarnings += currentOrder[i]->getCost() + (currentOrder[i]->getCost()*0.8);
                

            }

            if (orderGrade <= 0) { localEarnings = 0; }

            //Gold Earnings
            diaObj.writeDialouge("You earned Gold: " + to_string(localEarnings) + " | Tips: " + to_string(tips), true, true);
            gameStats->addEarnings(localEarnings);
            playerStats->setGold(playerStats->getGold() + localEarnings);

            //Reset order to allow next customer!
            currentOrder.clear();

            //Quota check
            if (gameStats->getEarnings() >= gameStats->getQuota())
            {
                gameResult = 1;
            }
            else
            {
                gameResult = 2;
            }

            if (timeClass.reachedEnd == true)
            {

                //Day ended!!
                diaObj.writeDialouge("The day has come to an end!", true, true);
                diaObj.writeDialouge("You close up shop and count your earnings, glancing at the quota requirement...", true, true);
                endTime(timeClass, t1);
                if (gameResult == 1)
                {
                    //Passed quota
                    //Reset rep if zero
                    if (playerStats->getRep() <= 0) { playerStats->setRep(10); }

                    gameStats->setDay(gameStats->getDay() + 1);
                    gameStats->setEarnings(0);
                    gameStats->setQuota(generateQuota(gameStats->getDay()));
                    diaObj.writeDialouge("The quota has been reached!", true, true);
                    diaObj.writeDialouge("You head home and rest, getting ready to do it all over again tomorrow...", true, true);
                    diaObj.writeDialouge("Options: Save Game | Continue | Exit", false, true);
                    do
                    {
                        diaObj.askUserChoice(diaChoiceMain);
                        if (diaChoiceMain == "Continue"  || diaChoiceMain == "Exit")
                        {
                            break;
                        }
                        else if (diaChoiceMain == "Save Game")
                        {

                            if (!saveGame(diaObj, gameStats, playerStats, inventoryManager))
                            {
                                diaObj.writeDialouge("File operation failed!", true, true);
                            }
                            //Save success, loop
                        }

                    } while (true);

                    //Back in main game 
                    if (diaChoiceMain == "Continue")
                    {
                        

                        //Same as retry, but things are increased, me when redundant code
                        setBaseStats(gameStats, playerStats, inventoryManager);

                        //Stocking phase
                        enterStockingPhase(diaObj, gameStats, playerStats, inventoryManager);

                        gameResult = -1;

                        timeClass.restartTime = true;
                        continue;
                        //Same as retry, me when redundant code
                    }
                    else if (diaChoiceMain == "Exit")
                    {
                        diaObj.writeDialouge("See you next time!", true, true);
                        return 1;
                    }
                }
                else if (gameResult == 2)
                {
                    //failed
                    diaObj.writeDialouge("The Qutoa has not been reached... You take your losses and begin to packup...", true, true);
                    diaObj.writeDialouge("Or is this really the end?", true, true);
                    diaObj.writeDialouge("What will it be? : Retry - Exit", true, true);
                    do
                    {
                        diaObj.askUserChoice(diaChoiceMain);
                        if (diaChoiceMain == "Retry" || diaChoiceMain == "Exit")
                        {
                            break;
                        }
                    } while (true);

                    if (diaChoiceMain == "Exit")
                    {
                        //MainMenu
                        diaObj.writeDialouge("See you next time!", true, true);
                        return 1;
                    }
                    else
                    {
                        //Retry
                        //Assign base stats and restart timer, set gameresult to -1, continue

                        gameStats->setDay(baseStats.baseDay);
                        gameStats->setEarnings(baseStats.baseEarnings);

                        playerStats->setExp(baseStats.baseExp);
                        playerStats->setGold(baseStats.baseGold);
                        playerStats->setProf(baseStats.baseProf);
                        playerStats->setRep(baseStats.baseRep);

                        inventoryManager.setWaterStock(baseStats.baseWater);
                        inventoryManager.setColaStock(baseStats.baseCola);
                        inventoryManager.setBreadStock(baseStats.baseBread);
                        inventoryManager.setFishStock(baseStats.baseFish);
                        inventoryManager.setHamStock(baseStats.baseHam);

                        //Stocking phase
                        enterStockingPhase(diaObj, gameStats, playerStats, inventoryManager);
                        
                        gameResult = -1;

                        timeClass.restartTime = true;
                        continue;
                    }
                }
            }

        }
        
    }

    delete playerStats;
    delete gameStats;
    endTime(timeClass, t1);
    return 0;
} 

