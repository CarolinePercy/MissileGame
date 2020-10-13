/// <summary>
/// Author: Caroline Percy
/// Date: 12 Oct 2020 - 
/// Objective: Create a console missile game, where the player fires a missile which explodes when it hits the target, or deactivates if it misses
/// Bugs: None
/// </summary>

#include <iostream>
#include "WarHead.h"

int selectWarHead();
void acquireTarget();
void launchCode();
void armMissile();
void collisionCheck();
void destroyTarget(int t_warhead);
void deactivateMissile();

int main()
{
	WarHead missile;
	missile.setWarhead(selectWarHead());



	return 0;
}

/// <summary>
/// Asks the user to select a warhead type using numbers, sending it back to main once a valid option has been picked
/// </summary>
/// <returns>the value for the warhead's type (effects damage)</returns>
int selectWarHead()
{
	int inputtedNum{-1};

	// Asks user to select a warhead
	std::cout << "***********************" << std::endl;
	std::cout << "Please select a War Head, using the number." << std::endl;
	std::cout << "1) Explosive" << std::endl;
	std::cout << "2) Nuclear" << std::endl;
	std::cout << "3) Atomic" << std::endl;

	std::cin >> inputtedNum; // takes the value from user

	while ( inputtedNum <= 0 || inputtedNum > 3) // if user entered an invalid answer, display error
	{
		std::cout << "Please enter a valid number." << std::endl;
		std::cin.clear();
		std::cin.ignore(10000, '\n');
		std::cin >> inputtedNum;
	}

	return inputtedNum; // once valid answer added, return the answer to main
}
