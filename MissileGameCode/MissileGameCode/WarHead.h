#pragma once
#include "Coordinates.h"
#include <iostream>	
struct WarHead
{
	int damage{0};
	Coordinates position;
	Coordinates target;
	Coordinates speed;
	bool armed{false};

	WarHead();
	void setWarhead(int t_warhead);
	void moveWarhead();
};

