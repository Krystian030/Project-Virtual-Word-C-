#pragma once
#define REPORT_NUMBER 20
#include <list>
#include <iostream>
#include "Organism.h"

class Organism;

struct Board {
	bool isEmpty;
	Organism* organism;
};

using namespace std;
class Organisms {
	list<Organism*> listOrganisms;
	Board** organismsBoard;
	Board* organismsToKill;
	string reports[REPORT_NUMBER];
	int reportsNumbers;
	int organismPopulity;
	int worldHeight, worldWidth;
	int deathsNumbers;
public:
	Organisms();
	int getOrganismPopulity() const;
	void setOrganismPopulity(int number);
	list<Organism*>* getList();
	string* getReports();
	void addReport(string report);
	void setReportsNumbers(int reportsNumbers);
	int getReportsNumbers();
	void createOrganismsBoard(int x,int y);
	Board** getOrganismsBoard();
	void createOrganisms();
	Organism* createOrganism(int speciesNumber, Coordinates coordinates);
	Organism* getOrganism(Coordinates coordinates);
	void addOrganism(Organism* organism);
	void addTokillOrganism(Coordinates coordinates);
	void killOrganism(Coordinates coordinates);
	list<Organism*>::iterator getIterator(Coordinates coordinates);
	Coordinates findCoordinates(Coordinates firstParent, Coordinates secondParent);
	void update();
	void addOrganismToBoard(Organism* organism);
	Coordinates  drawCoordinates();
	void removeField(Coordinates oldCoordinates);
	int getWidth() const;
	int getHeight() const;
	void setWidth(int width);
	void setHeight(int height);
	Organism* createOrganismType(string type, Coordinates coordinates);
};
