#pragma once
#include "Organism.h"
#define PROBABILITY 5
#define SOSNOWSKYHOGWEEED_PROBABILITY 2	//Procent rozprzestrzeniania si� barszczu sosnowskiego
#define DEADLYNIGHTSHADES_PROBABILITY 2	//Procent rozprzestrzeniania si� wilczych jag�d
class Plant : public Organism {
	virtual void collision(Organism* adjacentOrganism);
	virtual void action() override;
protected: 
	virtual Coordinates findField(Coordinates coordinates);
	virtual void spreading();
};
