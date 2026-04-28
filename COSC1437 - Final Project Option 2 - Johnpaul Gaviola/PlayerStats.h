#pragma once
#include <string>
using namespace std;

class PlayerStats {

public:
	PlayerStats();
	PlayerStats(int, int, int, int); 

	void setExp(int); //to add get then set
	void setGold(int);
	void setRep(int);
	void setProf(int);

	int getExp();
	int getGold();
	int getRep();
	int getProf();

private:
	int Exp;
	int Gold;
	int Reputation;
	int Proficiency;
};
