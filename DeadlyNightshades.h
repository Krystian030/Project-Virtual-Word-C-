#pragma once
#include "Plant.h"

class DeadlyNightshades : public Plant {
	virtual void action() override;
	virtual void collision(Organism* adjacentOrganism);
public:
	DeadlyNightshades(Organisms* organisms, Coordinates coordinates);
};
