#include "Dandelion.h"
#define TRY 3
 
Dandelion::Dandelion(Organisms* organisms, Coordinates coordinates) {
	features.strength =  0;
	features.initiative = 0;
	features.age = 0;
	features.sign = '*';
	features.name = "Mlecz";
	world = organisms;
	this->coordinates = coordinates;
}

/*Metoda odpowiedzialna za rozprzestrzenianie siê mlecza, podejmuje on 3 proby rozprzestrzeniania*/
void Dandelion::action() {
	int probability;
	for (int i = 0; i < TRY; ++i) {
		probability = 100 / PROBABILITY;
		if (!(rand() % probability)) spreading();
	}
}