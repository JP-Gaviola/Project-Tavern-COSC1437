#pragma once
#include <string>

//All order items

#include "Water.h"
#include "Bread.h"
#include "Fish.h"
#include "Cola.h"
#include "Ham.h"

class InventoryManager {

public:
	InventoryManager() 
	{
		water = 0;
		cola = 0;
		bread = 0;
		fish = 0;
		ham = 0;
	}

	int getWaterStock() { return water; }
	int getColaStock() { return cola; }
	int getBreadStock() { return bread; }
	int getFishStock() { return fish; }
	int getHamStock() { return ham; }


	void addWaterStock(int temp) { water += temp; }
	void addColaStock(int temp) { cola += temp; }
	void addBreadStock(int temp) { bread += temp; }
	void addFishStock(int temp) { fish += temp; }
	void addHamStock(int temp) { ham += temp; }

	void setWaterStock(int temp) { water = temp; }
	void setColaStock(int temp) { cola = temp; }
	void setBreadStock(int temp) { bread = temp; }
	void setFishStock(int temp) { fish = temp; }
	void setHamStock(int temp) { ham = temp; }

	int getWaterPrice() { Water temp; return temp.getCost(); }
	int getColaPrice() { Cola temp; return temp.getCost(); }
	int getBreadPrice() { Bread temp; return temp.getCost(); }
	int getFishPrice() { Fish temp; return temp.getCost(); }
	int getHamPrice() { Ham temp; return temp.getCost(); }

	int getFishExp() { Fish temp; return temp.getExpNeeded(); }
	int getHamExp() { Ham temp; return temp.getExpNeeded(); }

private:
	int water;
	int cola;
	int bread;
	int fish;
	int ham;
};