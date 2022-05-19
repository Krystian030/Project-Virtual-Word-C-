#include "Sheep.h"

Sheep::Sheep(Organisms* organisms, Coordinates coordinates){
	features.strength = 4;
	features.initiative = 4;
	features.age = 0;
	features.sign = 'S';
	features.name = "Owca";
	world = organisms;
	this->coordinates = coordinates;
}
