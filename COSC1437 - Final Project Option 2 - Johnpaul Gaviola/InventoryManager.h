#pragma once
#include <string>

//All order items

#include "Water.h"
#include "Bread.h"
#include "Fish.h"

class InventoryManager {

public:
	InventoryManager() 
	{
		water = 0;
		bread = 0;
		fish = 0;
	}
	InventoryManager(int inWater, int inBread, int inFish)
	: water(inWater), bread(inBread), fish(inFish) {}

	int getWaterStock() { return water; }
	int getBreadStock() { return bread; }
	int getFishStock() { return fish; }

	void addWaterStock(int temp) { water += temp; }
	void addBreadStock(int temp) { bread += temp; }
	void addFishStock(int temp) { fish += temp; }

	void setWaterStock(int temp) { water = temp; }
	void setBreadStock(int temp) { bread = temp; }
	void setFishStock(int temp) { fish = temp; }

	int getWaterPrice() { Water temp; return temp.getCost(); }
	int getBreadPrice() { Bread temp; return temp.getCost(); }
	int getFishPrice() { Fish temp; return temp.getCost(); }

	int getFishExp() { Fish temp; return temp.getExpNeeded(); }

private:
	int water;
	int bread;
	int fish;
};