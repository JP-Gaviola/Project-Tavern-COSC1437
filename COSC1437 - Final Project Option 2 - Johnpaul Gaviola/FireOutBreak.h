#pragma once
#include "EventClass.h"
#include <string>
#include "PlayerStats.h"
#include "GameStats.h"
#include "DialougeClass.h"
#include "InventoryManager.h"
using namespace std;

class FireOutbreak : public EventClass {
protected:
	string eventText = "A fire broke out and damaged your inventory!";
public:
	void eventMain(Dialouge& diaObj, GameStats* gameStats, PlayerStats* playerStats, InventoryManager& inventoryManager)
	{
		//Negative event
		diaObj.writeDialouge(eventText, true, true);

		string diaChoice;

		inventoryManager.addBreadStock(-5);
		diaObj.writeDialouge("The fire was quickly put out by helpful customers, but the damage was already done... (-5 Bread)", true, true);
	}
};