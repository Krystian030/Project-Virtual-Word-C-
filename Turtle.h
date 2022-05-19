#pragma once
#include "Animal.h"

class Turtle : public Animal {
	virtual void action();
	virtual void defensive(Organism* enemy);
public:
	Turtle(Organisms* organisms, Coordinates coordinates);
};
