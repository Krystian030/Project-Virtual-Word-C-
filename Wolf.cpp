#include "Wolf.h"

Wolf::Wolf(Organisms* organisms, Coordinates coordinates){
	features.strength = 9;
	features.initiative = 5;
	features.age = 0;
	features.sign = 'W';
	features.name = "Wilk";
	world = organisms;
	this->coordinates = coordinates;
}