#include "Grass.h"

Grass::Grass(Organisms* organisms, Coordinates coordinates){
	features.strength = 0;
	features.initiative = 0;
	features.age = 0;
	features.sign = ',';
	features.name = "Trawa";
	world = organisms;
	this->coordinates = coordinates;
}
