#pragma once
#include "Coordinates.h"

struct Target
{
	Target();
	Coordinates position;
	int health{100};
};

