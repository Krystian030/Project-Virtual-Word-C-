#pragma once
#include "Animal.h"

class Antelope : public Animal {
	virtual void action();
	virtual void defensive(Organism* enemy);
public:
	Antelope(Organisms* organisms, Coordinates coordinates);
};
