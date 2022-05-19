#pragma once
#include "Antelope.h"
#include "Fox.h"
#include "Human.h"
#include "Sheep.h"
#include "Turtle.h"
#include "Wolf.h"
#include "Dandelion.h"
#include "DeadlyNightshades.h"
#include "Grass.h"
#include "SosnowskyHogweed.h"
#include "World.h"


class Initializer {
	World* world;
public:
	Initializer(World* world);
	void initializer();
};
