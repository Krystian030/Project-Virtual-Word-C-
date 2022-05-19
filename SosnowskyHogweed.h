#pragma once
#include "Plant.h"

class SosnowskyHogweed : public Plant {
	virtual void action() override;
	virtual void collision(Organism* adjacentOrganism);
public:
	SosnowskyHogweed(Organisms* organisms, Coordinates coordinates);
};
