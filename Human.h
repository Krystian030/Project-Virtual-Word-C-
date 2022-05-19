#pragma once
#include "Animal.h"

class Human : public Animal {
	bool boostIsActive;
	bool boostIsAvaliable;
	bool isAlive;
	int turnsToBoost;
	int boostTurns;
public:
	Human(Organisms* organisms, Coordinates coordinates);
	virtual void action(int btn);
	void boostActivating();
	void boostLoading();
	void boostManagement(Coordinates coordinates);
	int getTurnsToBoost() const;
	int getBoostTurns() const;
	void setTurnsToBoost(int turnsToBoost);
	void setBoostTurns(int boostTurns);
	void setBoostIsActive(bool option);
	void setBoostIsAvaliable(bool option);
};
	
