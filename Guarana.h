#pragma once
#include "Plant.h"

class Guarana : public Plant {
	virtual void collision(Organism* adjacentOrganism);
public:
	Guarana(Organisms* organisms, Coordinates coordinates);
};

