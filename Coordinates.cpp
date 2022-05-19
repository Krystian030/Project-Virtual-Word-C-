#include "Coordinates.h"
	
	Coordinates::Coordinates(){}

	Coordinates::Coordinates(int x, int y) {
		this->x = x;
		this->y = y;
	}

	int Coordinates::GetX() const {
		return this->x;
	}

	int Coordinates::GetY() const {
		return this->y;
	}

	bool Coordinates::operator==(const Coordinates& coordinates) {
		if (this->x == coordinates.x && this->y == coordinates.y) return true;
		else return false;
	}

	/*Operator ró¿noœci klasy Coordinates*/
	bool Coordinates::operator!=(const Coordinates& coordinates) {
		if (this->x != coordinates.x || this->y != coordinates.y) return true;
		else return false;
	}

	/*Operator przypisania klasy Coordinates*/
	void Coordinates::operator=(const Coordinates& coordinates) {
		this->x = coordinates.x;
		this->y = coordinates.y;
	}
	
	/*Zmienia koordynaty o podany wektor dx i dy*/
	Coordinates Coordinates::move(int dx, int dy){
		Coordinates* tmp = new Coordinates(x + dx, y + dy);
		Coordinates newCoordinates = *tmp;
		delete tmp;
		return newCoordinates;
	}