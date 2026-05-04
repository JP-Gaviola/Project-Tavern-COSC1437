#pragma once
#include <thread>
#include <chrono>
#include "EventClass.h"
#include <string>
#include "PlayerStats.h"
#include "GameStats.h"
#include "DialougeClass.h"
#include "InventoryManager.h"
using namespace std;



class WaterDonator : public EventClass {
protected:
	string eventText = "A man carrying around a cart of water walks in and drops off water in your pantry for free, citing it's a gift from his god...";
public:
	bool guitarActive = false;
	void eventMain(Dialouge& diaObj, GameStats* gameStats, PlayerStats* playerStats, InventoryManager& inventoryManager)
	{
		inventoryManager.addWaterStock(5);
		diaObj.writeDialouge("Gained 5 water!", true, true);
	}
		
};