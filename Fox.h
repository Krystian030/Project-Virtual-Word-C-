#pragma once
#include "Animal.h"

class Fox : public Animal {
	virtual void action();
public:
	Fox(Organisms* organisms, Coordinates coordinates);
};
