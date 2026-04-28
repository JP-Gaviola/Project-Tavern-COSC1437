#include "PlayerStats.h"
#include <string>
using namespace std;

//Constructors
PlayerStats::PlayerStats()
{
	Exp = 0;
	Gold = 0;
	Reputation = 0;
	Proficiency = 0;
}

PlayerStats::PlayerStats(int inE, int inG, int inR, int inP)
{
	Exp = inE;
	Gold = inG;
	Reputation = inR;
	Proficiency = inP;
}

//Setter

void PlayerStats::setExp(int in) { Exp = in; }
void PlayerStats::setGold(int in) { Gold = in; }
void PlayerStats::setRep(int in) { Reputation = in; }
void PlayerStats::setProf(int in) { Proficiency = in; }


//Getter
int PlayerStats::getExp() { return Exp; }
int PlayerStats::getGold() { return Gold; }
int PlayerStats::getRep() { return Reputation; }
int PlayerStats::getProf() { return Proficiency; }