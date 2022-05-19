#pragma once

#define BORDER_WIDTH 1
#define SPECIESNUMBER 10
#define DIRECTIONS 9
#define COORDINATIONSPOSSIBILITY 16

class Coordinates {
	int x, y;
public:
	Coordinates();
	Coordinates(int x, int y);
	int GetX() const;
	int GetY() const;

	bool operator ==(const Coordinates& cords);
	bool operator !=(const Coordinates& cords);
	void operator =(const Coordinates& cords);
	Coordinates move(int dx, int dy);
};
