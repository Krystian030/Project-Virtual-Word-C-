#pragma once
#include "Organisms.h"

class World {
	Organisms organisms;
	int turnNumber;
	int width, height;
public:
	World();
	World(int width, int height);
	void setTurnNumber(int turnNumber);
	void setOrganisms(Organisms* organisms);
	int getWidth() const;
	int getHeight() const;
	void setWidth(int width);
	void setHeight(int height);
	void takeTurn(int btn);
	void drawWorld();
	Organisms* getOrganisms();
	void saveWorld();
	void initiateWorld(Organisms* organisms);
};
