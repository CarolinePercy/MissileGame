#pragma once
#include "Coordinates.h"
#include <iostream>
class WarHead
{
public:
	void setWarhead(int t_warhead);
	void setPosition(Coordinates t_coord);
	Coordinates getPosition();
private:
	int damage{0};
	Coordinates position;
};

