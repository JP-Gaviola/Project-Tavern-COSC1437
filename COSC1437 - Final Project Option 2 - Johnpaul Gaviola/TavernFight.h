#pragma once
#include "EventClass.h"
#include <string>
#include "PlayerStats.h"
#include "GameStats.h"
#include "DialougeClass.h"
#include "InventoryManager.h"
using namespace std;

class TavernFight : public EventClass {
protected:
	string eventText = "A fight within the tavern breaks out! The furniture is damaged severely, pay 10 gold to repair? (-5 Reputation if ignored) - Yes - No";
public:
	void eventMain(Dialouge& diaObj, GameStats* gameStats, PlayerStats* playerStats, InventoryManager& inventoryManager)
	{
		//Negative event
		diaObj.writeDialouge(eventText, false, true);

		string diaChoice;
		
		do
		{
			diaObj.askUserChoice(diaChoice);
			if (diaChoice != "Yes" || diaChoice != "No")
			{
				break;
			}
		} while (true);

		if (diaChoice == "Yes")
		{
			playerStats->setGold(playerStats->getGold() - 10);
			diaObj.writeDialouge("You pay 10 gold and the finest carpenters enter and quickly fix up the shop.. (-10 Gold)", true, true);
		}
		else
		{
			playerStats->setRep(playerStats->getRep() - 5);
			diaObj.writeDialouge("You refuse to do anything about the damage and some customers are discouraged by your tavern now... (-5  Rep)", true, true);
		}
	}
};