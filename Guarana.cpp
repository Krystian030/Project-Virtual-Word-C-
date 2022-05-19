#include "Guarana.h"
#define GUARANA_INCREASE 3

Guarana::Guarana(Organisms* organisms, Coordinates coordinates){
	features.strength = 0;
	features.initiative = 0;
	features.age = 0;
	features.sign = '@';
	features.name = "Guarana";
	world = organisms;
	this->coordinates = coordinates;
}

/*Kolzija Guarany, organizm po zjedzeniu jej zwieksza swoja sile o 3*/
void Guarana::collision(Organism* adjacentOrganism){
	string report = adjacentOrganism->getName() + " zjadl/a " + this->getName() + " sila " + adjacentOrganism->getName() +
	" wynosila  " + to_string(adjacentOrganism->getStrength());
	adjacentOrganism->increaseStrength(GUARANA_INCREASE);
	report += " i wzrosla do " + to_string(adjacentOrganism->getStrength());
	world->addTokillOrganism(coordinates);
	adjacentOrganism->takeMove(coordinates);

	world->addReport(report);
}

