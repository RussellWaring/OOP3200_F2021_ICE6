#include <iomanip>
#include <iostream>
#include <map>
#include <fstream> // for ofstream
#include <cstdlib> // for exit functions

#include <vector>

#include "GameObject.h"
#include "Vector3D.h"


void BuildGameObjects(std::vector<GameObject*>& game_objects, const int num = 2)
{
	for (auto count = 0; count < num; ++count)
	{
		int id;
		std::cout << "Enter the gameObject's ID: ";
		std::cin >> id;
		Vector2D<float> point;
		std::cout << "Enter the gameObject's Position (x, y): ";
		std::cin >> point;
		std::cout << "\n--------------------------------------------------------------" << std::endl;
		std::cout << "You Entered " << id << " for the gameObject's ID " << std::endl;
		std::cout << "You Entered " << point << " for the gameObject's Position" << std::endl;
		std::cout << "--------------------------------------------------------------\n" << std::endl;
		auto* gameObject = new GameObject(id, point);
		game_objects.push_back(gameObject);
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

	std::ifstream infile("GameObject.txt", std::ios::in);

	//while(!infile.eof()) - loop not closing
	while(infile >> new GameObject())
	{
		int id;
		float x, y = 0;
		std::string name;
		Vector2D<float> position;

		infile >> id >> name;
		infile.ignore();
		infile >> x;
		infile.ignore();
		infile >> y;
		infile.ignore();
		// Read it all in, create GameObject. If going into map, has to be type pointer
		auto* temp_object = new GameObject(name, id, x, y);

		gameObjects[name + " 2"] = temp_object;

		std::cout << "Read Operation" << std::endl;
	}
	infile.close(); // close the infile!

	for (const auto& game_object : gameObjects)
	{
		std::cout << "Key   : " << game_object.first << std::endl;
		std::cout << "Value : " << std::endl;
		std::cout << "---------------------------------" << std::endl;
		std::cout << game_object.second->ToString() << std::endl; // want to convert the object itself. No overloaded operator / friend class.
	}



	//std::vector<GameObject*> gameObjects;

	//int num_of_GO;
	//std::cout << "How Many Game Objects do you need?: ";
	//std::cin >> num_of_GO;
	//std::cout << "\n--------------------------------------------------------------" << std::endl;

	//BuildGameObjects(gameObjects, num_of_GO);
	//
	//
	//int index1;
	//std::cout << "What is the First Object index?: ";
	//std::cin >> index1;
	//std::cout << "\n--------------------------------------------------------------" << std::endl;
	//int index2;
	//std::cout << "What is the Second Object index?: ";
	//std::cin >> index2;
	//std::cout << "\n--------------------------------------------------------------" << std::endl;
	//
	//CompareGameObjects(gameObjects[index1], gameObjects[index2]);
	//CompareGameObjects(gameObjects[index1], gameObjects[index2]);
}

