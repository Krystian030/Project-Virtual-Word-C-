#include "Initializer.h"
#include <iostream>
#include <Windows.h>
#include <cmath>
#define LOAD_GAME 1
#define NEW_GAME 2
using namespace std;
Initializer::Initializer(World* world){
	this->world = world;
}

/*Metoda inicjalizujaca swiat*/
void Initializer::initializer(){
	Organisms* organisms = world->getOrganisms();
	Organism* human;

	cout << "=========================" << endl;
	cout << "Witaj w symulatorze zycia" << endl;
	cout << "=========================" << endl;
	int option;
	bool rightOption = false;
	cout << "Wybierz opcje:\n1 - wczytac zapisany plik\n2 - nowa gra\n";
	cin >> option;
	while (!rightOption) {
		if (option == LOAD_GAME) {
			world->initiateWorld(organisms);
			rightOption = true;
		}
		else if (option == NEW_GAME) {
			int w, h;
			double p;
			cout << "Podaj wymiary swiata" << endl;
			cout << "Szerokosc: ";
			cin >> w; world->setWidth(w);  organisms->setWidth(w);
			cout << "Wysokosc: ";
			cin >> h; world->setHeight(h); organisms->setHeight(h);
			cout << "Podaj w procentach poczatkowe zapelnienie swiata wzgledem planszy: ";
			cin >> p;
			p = (p / 100) * (h * w);
			organisms->setOrganismPopulity((int)p);
			organisms->createOrganismsBoard(w, h);
			//Tworzenie cz³owieka
			human = new Human(organisms, organisms->drawCoordinates());
			organisms->addOrganism(human);
			organisms->createOrganisms();
			rightOption = true;
		}
		else {
			cout << "Wybrano nieprawidlowa opcje. Podaj ponownie opcje\n";
			rightOption = false;
			cin >> option;
		}
	}
	system("cls");
	world->drawWorld();
}
