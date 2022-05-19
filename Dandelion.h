#pragma once
#pragma once
#include "Plant.h"

class Dandelion : public Plant {
	virtual void action() override;
public:
	Dandelion(Organisms* organisms, Coordinates coordinates);
};
