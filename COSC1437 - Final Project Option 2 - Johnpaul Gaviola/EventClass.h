#pragma once
#include <string>
#include "PlayerStats.h"
#include "GameStats.h"
#include "DialougeClass.h"
#include "InventoryManager.h"
using namespace std;

class EventClass {
protected:
	string eventText;
public:
	virtual void eventMain(Dialouge& diaObj, GameStats* gameStats, PlayerStats* playerStats, InventoryManager& inventoryManager) = 0;
};