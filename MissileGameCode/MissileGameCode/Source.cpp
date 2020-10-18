/// <summary>
/// Author: Caroline Percy
/// Date: 12 Oct 2020 - 18 Oct 2020
/// Objective: Create a console missile game, where the player fires a missile which explodes when it hits the target,
/// or deactivates if it misses
/// Bugs: None
/// </summary>

#include <iostream>
#include "WarHead.h"
#include "Target.h"

// Functions
int selectWarHead();
Coordinates acquireTarget();
bool armMissile();
bool launchCode(WarHead& t_missile, Target& t_target);
bool collisionCheck(WarHead& t_missile, Target& t_target);
bool destroyTarget(WarHead & t_missile, Target& t_target);
void deactivateMissile(WarHead& t_missile);
void letUserRead();
void errorMessage();


/// <summary>
/// The start of the code
/// </summary>
/// <returns>returns 0 if the code exited correctly</returns>
int main()
{
	WarHead missile; // rocket shot at target. User controls this
	Target target; // What the user is aiming at. Has 100 health
	bool windowOpen{ true }; // Checks whether the console window is to be closed

	while (windowOpen) // while the game runs
	{
		missile.setWarhead(selectWarHead());
		missile.target = acquireTarget();
		missile.armed = armMissile();

		windowOpen = launchCode(missile, target);
	}
	
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
		errorMessage();
		std::cin >> inputtedNum;
	}

	return inputtedNum; // once valid answer added, return the answer to main
}

/// <summary>
/// Gets the coordinates the missile should aim for
/// </summary>
Coordinates acquireTarget()
{
	// temporary coordinates to store values user inputs
	Coordinates missileDestination;
	missileDestination.setPosition(-1,-1);

	std::cout << "***********************" << std::endl;
	std::cout << "Please enter the X value of where the missile should aim for." << std::endl;

	std::cin >> missileDestination.x; // takes the value from user

	while (missileDestination.x <= 0) // If user puts in an invalid answer, display error
	{
		errorMessage();
		std::cin >> missileDestination.x;
	}

	std::cout << "Now please enter the Y value." << std::endl;

	std::cin >> missileDestination.y; // takes the value from user

	while (missileDestination.y <= 0)// If user puts in an invalid answer, display error
	{
		errorMessage();
		std::cin >> missileDestination.y;
	}

	// Then shows user what they inputted so they know for sure the destination
	std::cout << "The missile's target is at (" << missileDestination.x << "," << missileDestination.y << ")." << std::endl;

	letUserRead();

	return missileDestination;
}

/// <summary>
/// Asks user whether they want this missile to launch.
/// </summary>
/// <returns>Whether the user allows the missile to be armed</returns>
bool armMissile()
{
	bool armed{false};
	char input{' '};

	std::cout << "***********************" << std::endl;
	std::cout << "Select if the missile will be armed or disarmed. (a|d)" << std::endl;
	// Asks user if they want the missile to be armed

	std::cin >> input; // takes the value from user


	while (input != 'd' && input != 'D' && input != 'A' && input != 'a')// invalid answer gives error
	{
		errorMessage();
		std::cin >> input;
	}

	if (input == 'd' || input == 'D') // if user passed letter D, missile is disarmed
	{
		std::cout << "The missile has been disarmed." << std::endl;
		armed = false;
	}

	else // if user passes letter A, missile is armed
	{
		std::cout << "the missile has been armed." << std::endl;
		armed = true;
	}

	letUserRead();

	return armed;
}

/// <summary>
/// if the missile is armed, this function launches the rocket. It connects to functions that control the missile in mid-air.
/// </summary>
/// <param name="t_missile">The missile object</param>
/// <param name="t_target">the target object</param>
/// <returns>Whether the window is still open after the missile launch.</returns>
bool launchCode(WarHead& t_missile, Target& t_target)
{
	bool windowOpen{ true };
	std::cout << "***********************" << std::endl;

	if (t_missile.armed) // If missile is armed, it is launched
	{
		std::cout << "The missile has been launched." << std::endl;

		letUserRead();

		// Does the calculations on where the missile and target are, returning a bool that says whether the target was hit
		bool missileTargetCollide = collisionCheck(t_missile, t_target); 

		if (missileTargetCollide) // if target was hit, damage target
		{
			windowOpen = destroyTarget(t_missile, t_target);
		}

		else // if it wasnt hit, deactivate missile
		{
			deactivateMissile(t_missile);
		}
	}

	else // if missile was not armed, display text saying so to user
	{
		std::cout << "Missile was disarmed, so it does not launch." << std::endl;
		letUserRead();
	}

	system("CLS"); // clear screen to make text look nice
	return windowOpen;
}

/// <summary>
/// Moves the missile in the air, and checks if it collides with the target, or reaches the coordinates the user set for it to go to
/// </summary>
/// <param name="t_missile">the missile object</param>
/// <param name="t_target">the target object</param>
/// <returns>Whether the missile collided with the target</returns>
bool collisionCheck(WarHead& t_missile, Target& t_target)
{
	bool collisionOccur;
	bool onTrack{true};	

	while (onTrack) // while the missile is in the air
	{
		
		// check if the missile collided with the target
		if (t_missile.position.x == t_target.position.x && t_missile.position.y == t_target.position.y)
		{
			// if it does, damage target
			collisionOccur = true;
			onTrack = false;
		}

		// check if it went past the coordinates the player told it to go to
		else if (t_missile.position.x > t_missile.target.x || t_missile.position.y > t_missile.target.y)
		{
			// if it does, it deactivates
			collisionOccur = false;
			onTrack = false;
		}

		// moves the warhead by its speed
		t_missile.moveWarhead();
	}

	return collisionOccur;
}

/// <summary>
/// Does damage to the target, depending on the damage of the warhead of the missile.
/// will tell the user how much health the target has left, and will let the program close if the target has been destroyed
/// </summary>
/// <param name="t_missile">The missile object</param>
/// <param name="t_target">The target object</param>
/// <returns>Whether the window is to close (window is to close once target is destroyed)</returns>
bool destroyTarget(WarHead& t_missile, Target& t_target)
{
	// Removes the health from the target and resets the missile
	t_target.health -= t_missile.damage;
	t_missile.position.setPosition(0,0);

	bool windowOpen{true};
	
	// tells the user the missile collided with target
	std::cout << "Hit!";

	letUserRead();

	// if the target is not destroyed, tells user how much health it has left
	if (t_target.health > 0)
	{
		std::cout << "The target has "<< t_target.health << " health left." << std::endl;
	}

	else // if health is 0 or below, target is destroyed
	{
		std::cout << "The target was destoryed!" << std::endl;
		windowOpen = false;
	}

	letUserRead();

	return windowOpen;
}

/// <summary>
/// Returns the missile to its original position, and tells the user this has happened
/// </summary>
/// <param name="t_missile">The missile object</param>
void deactivateMissile(WarHead& t_missile)
{	
	// resets the missile and tells the user why it not damage the target
	t_missile.position.setPosition(0, 0);
	std::cout << "The missile did not hit the target, and deactivated itself." << std::endl;
	letUserRead();
}

/// <summary>
/// Pauses the program to allow the user to read the text displayed to them in a neat and nice manner
/// </summary>
void letUserRead()
{
	std::cin.clear();
	std::cin.ignore(10000, '\n');
	std::cin.get();
}

/// <summary>
/// Used to display a warning to the user, as they did not input a value asked from them
/// </summary>
void errorMessage()
{
	std::cout << "Please enter a valid command." << std::endl;
	std::cin.clear();
	std::cin.ignore(10000, '\n');
}
