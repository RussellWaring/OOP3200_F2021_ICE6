#include <iomanip>
#include <iostream>
#include <map>
#include <fstream> // for ofstream
#include <cstdlib> // for exit functions

#include <vector>

#include "GameObject.h"
#include "Vector3D.h"


void PrintGameObjects(const std::map<std::string, GameObject*>& game_objects) // from the updated repo
{
	std::cout << "-------------------------------------\n";
	std::cout << "Output map of Game Objects\n";
	std::cout << "-------------------------------------\n\n";

	for (const auto& game_object : game_objects)
	{
		std::cout << "Key   : " << game_object.first << std::endl;
		std::cout << "-----------------------------" << std::endl;
		std::cout << game_object.second->ToString();
		std::cout << "-----------------------------" << std::endl;
	}
}

int main()
{
	std::map<std::string, GameObject*> gameObjects; // a map of type GameObject, with a friendly name. A key-value pair. Key is string, value is GameObject* (pointers)

	auto* ship = new GameObject("Ship", 0, 3.0f, 4.0f);
	auto* enemy = new GameObject("Enemy", 1, 10.0f, 20.0f);


	//gameObjects["ship"] = ship; // Add to map. Creating an association between key ("ship") and the value (ship) - a reference to the ship itself, the object
	//make the key the name of the object already declared:
	gameObjects[ship->GetName()] = ship;
	gameObjects[enemy->GetName()] = enemy;

	// Want to be able to loop. Range based for loop
	// "for every game_object in gameObjects....loop"
	for (const auto& game_object : gameObjects)
	{
		std::cout << "Key   : " << game_object.first << std::endl;
		std::cout << "Value : " << std::endl;
		std::cout << "---------------------------------" << std::endl;
		std::cout << game_object.second->ToString() << std::endl; // want to convert the object itself. No overloaded operator / friend class.
	}

	// find the distance between the two objects:
	// auto distance = Vector2D<float>::Distance(ship->GetPosition(), enemy->GetPosition()); --------------------------------------------- distance between objects
	auto distance = Vector2D<float>::Distance(gameObjects["Ship"]->GetPosition(), gameObjects["Enemy"]->GetPosition()); // - accessing obj stored in map

	std::cout << "Distance between " << gameObjects["Ship"]->GetName() << " and " << gameObjects["Enemy"]->GetName() << " is " << std::to_string(distance) << std::endl;

	std::ofstream outfile("GameObject.txt", std::ios::out);
	outfile << gameObjects["Ship"]->ToFile() << std::endl;
	//outfile << gameObjects["Enemy"]->GetID() << " " << gameObjects["Enemy"]->GetName() << " " << gameObjects["Enemy"]->GetPosition() << std::endl;
	outfile << gameObjects["Enemy"]->ToFile() << std::endl;
	outfile.close(); // close the outfile!

	std::cout << "-------------------------------------\n";
	std::cout << "END OF OUTPUT \n";
	std::cout << "-------------------------------------\n\n";

	std::cout << "-------------------------------------\n";
	std::cout << "START OF INPUT \n";
	std::cout << "-------------------------------------\n\n"; // banners

	std::ifstream infile;
	std::string fileName = "GameObject.txt";

	infile.open(fileName.c_str()); // c_str?

	//while(!infile.eof()) - loop not closing
	while(infile.is_open())
	{
		int id;
		float x, y;
		std::string name;

		while (!infile.fail())
		{
			infile >> id >> name;
			infile.ignore(1, ' ');
			infile.ignore(1, '(');
			infile >> x;
			infile.ignore(1, ',');
			infile.ignore(1, ' ');
			infile >> y;
			infile.ignore(1, ')');
			// Read it all in, create GameObject. If going into map, has to be type pointer
			auto* temp_object = new GameObject(name, id, x, y);

			gameObjects[name + " 1"] = temp_object;
		}
		infile.close();
	}

	PrintGameObjects(gameObjects);

	std::cout << "-------------------------------------\n";
	std::cout << "END OF INPUT \n";
	std::cout << "-------------------------------------\n\n";

}

