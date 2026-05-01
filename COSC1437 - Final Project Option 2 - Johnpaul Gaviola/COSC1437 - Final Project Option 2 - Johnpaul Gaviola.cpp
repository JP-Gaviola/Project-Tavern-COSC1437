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
    int baseQuota = (day * 10) + 50;
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
    diaObj.writeDialouge("Today's Earnings: " + to_string(gameStats->getEarnings()), false, false);
    diaObj.writeDialouge("Current Time: " + getTime(timeClass), false, false);
    diaObj.writeDialouge("Happy Hour: " + to_string(gameStats->checkHappyHour()), false, false);
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
        optionList += ") - Bread(S:" + to_string(inventoryManager.getBreadStock());
        optionList += ") - Fish(S:" + to_string(inventoryManager.getFishStock());
        optionList += ") -  Submit Order - Remove Item - View Order";

        diaObj.writeDialouge(optionList, false, false);

        diaObj.askUserChoice(diaChoiceLocal);
        if (diaChoiceLocal == "Water")
        {
            //Stock check 
            if (inventoryManager.getWaterStock() <= 0) { diaObj.writeDialouge("Not enough stock!", true, true); continue; }
            Water* tempWater = new Water;
            tempWater->prepareItem();
            prepOrder.push_back(tempWater);
            inventoryManager.addWaterStock(-1);
        }
        else if (diaChoiceLocal == "Bread")
        {
            if (inventoryManager.getBreadStock() <= 0) { diaObj.writeDialouge("Not enough stock!", true, true); continue; }
            Bread* tempBread = new Bread;
            tempBread->prepareItem();
            prepOrder.push_back(tempBread);
            inventoryManager.addBreadStock(-1);
        }
        else if (diaChoiceLocal == "Fish")
        {
            if (inventoryManager.getFishStock() <= 0) { diaObj.writeDialouge("Not enough stock!", true, true); continue; }
            Fish* tempFish = new Fish;
            
            tempFish->prepareItem();
            prepOrder.push_back(tempFish);
            inventoryManager.addFishStock(-1);
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
       diaObj.writeDialouge("Water : Price 2 ", false, false);
       diaObj.writeDialouge("Bread : Price 5 ", false, false);
       diaObj.writeDialouge("Fish : Price 10 : Exp 20 ", false, false);
       diaObj.writeDialouge("//////////////Store Inventory/////////////////", false, false);
       diaObj.writeDialouge("Water : " + to_string(inventoryManager.getWaterStock()), false, false);
       diaObj.writeDialouge("Bread : " + to_string(inventoryManager.getBreadStock()), false, false);
       diaObj.writeDialouge("Fish : " + to_string(inventoryManager.getFishStock()), false, false);
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
    InventoryManager inventoryManager;
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
    
    //Stocking phase
    enterStockingPhase(diaObj, gameStats, playerStats, inventoryManager);
    
    //Gameplay loop starts!
    diaObj.writeDialouge("You finish final preparations, all you need to do now is flip the open sign...", true, true);
    diaObj.writeDialouge("Let's do this!", false, true);

    //Start main game time in a different thread
    thread t1(&TimeClass::startTime, &timeClass);
    

    //Gameplay loop 
    while (gameResult == -1) //Only continue if time isnt 21
    {
        
        //Main game! 
        while (timeClass.reachedEnd == false)
        {
           
            printStatus(diaObj, gameStats, playerStats, timeClass);
            Customer* currCustomer = nullptr;
            
            selectRandomCustomer(currCustomer, playerStats->getRep());
             
            diaObj.writeDialouge("The Tavern door swings open...", true, true);

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
                        //Declined message
                        diaObj.writeDialouge(currCustomer->getDdeclined(), false, true);
                        //Lower players reputation
                        diaObj.writeDialouge("You lost reputation: -1", true, false);
                        playerStats->setRep(playerStats->getRep() - 1);
                        break;
                    }
                } while (diaChoiceMain != "Yes");
            }
            else
            {
                //Rep too low dialogue
                diaObj.writeDialouge(currCustomer->getDrepTooLow(), false, true);
                diaObj.writeDialouge("Reputation is too low to serve this customer!", true, true);
                continue;
            }
            //Check for decline to move to next customer
            if (diaChoiceMain == "No") { continue; }

            //Order was taken start a customer time in a different thread
            CustomerTimer localCustTimer;
            thread t2(&CustomerTimer::startTime, &localCustTimer);

           
            //Creates a order
            createOrder(currCustomer, playerStats->getExp(), currentOrder);
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
            //End timer
            localCustTimer.timeActive = false;
            int waitTime = localCustTimer.elapsed;
            t2.detach();

            //Submit Dialouge
            diaObj.writeDialouge(currCustomer->getDsubmitOrder(), true, true);

            
         

            
            //Grade order 
            //Score above 70 is passing 
            int localEarnings = 0;

            if (orderGrade >= 70)
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
                //Failed...
                diaObj.writeDialouge(currCustomer->getDOrderBad(), true, true);

                //Rep
                diaObj.writeDialouge("You lost Reputation: -1", false, false);
                playerStats->setRep(playerStats->getRep() - 1);

                //Exp
                diaObj.writeDialouge("You gained Exp: 2", true, false);
                playerStats->setExp(playerStats->getExp() + 2);
            }

            //Give player the earnings
            for (int i = 0; i < currentOrder.size(); i++)
            {
                localEarnings += currentOrder[i]->getCost();
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

    delete playerStats;
    delete gameStats;
    endTime(timeClass, t1);
    return 0;
} 

