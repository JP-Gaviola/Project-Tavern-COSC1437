#pragma once
#include <string>

//All order items

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
	
private:
	int water;
	int bread;
	int fish;
};