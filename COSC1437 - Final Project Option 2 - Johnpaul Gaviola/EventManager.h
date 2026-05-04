#pragma once
#include <iomanip>

#include "TavernFight.h"
#include "WaterDonator.h"
#include "FireOutBreak.h"

using namespace std;



class EventManager
{
public:
	void pickOneRandomEvent(Dialouge& diaObj, GameStats* gameStats, PlayerStats* playerStats, InventoryManager& inventoryManager)
	{
		TavernFight tavernFight;
		WaterDonator waterDonator;
		FireOutbreak fireOutbreak;

		int randomNum = rand() % 7 + 1; //1 to 7 //1-3 are blank evnets
		//randomNum = 6; debug

		switch (randomNum)
		{
		case 1:
			//Nothing
			break;
		case 2:
			//Nothing
			break;
		case 3:
			//Nothing
			break;
		case 4:
			tavernFight.eventMain(diaObj, gameStats, playerStats, inventoryManager);
			break;
		case 5:
			waterDonator.eventMain(diaObj, gameStats, playerStats, inventoryManager);
			break;
		case 6:
			fireOutbreak.eventMain(diaObj, gameStats, playerStats, inventoryManager);
			break;
		}
	}

};