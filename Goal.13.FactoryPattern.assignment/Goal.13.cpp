#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <algorithm>
#include <fstream>
#include <map>
#include <memory>

#include "Item.h"
#include "Object.h"
#include "Player.h"
#include "Monster.h"
#include "Library.h"

void createObjects(std::vector<std::unique_ptr<Object>>& objects, Library & library);

void bringOutYourDead(std::vector<std::unique_ptr<Object>> & objects);


int main()
{
	Library library;
	std::vector<std::unique_ptr<Object>> objects;
	objects.push_back(library.inventory.find("Player")->second->create(objects) );
	while (objects.size()>0 && objects.front()->getName() == Object::Type::player)
	{
		createObjects(objects, library);

		std::cout << objects.size()-1 << " monster(s) approaches!!" << std::endl;
		system("pause");
		system("cls");

		while (objects.size() >1)
		{

			for (auto& object : objects)
			{
				object->update(objects);
			}

			bringOutYourDead(objects);

			system("PAUSE");
			system("CLS");
		}
	}

	if ((objects.size() ==1 && objects.back()->getName() != Object::Type::player) || objects.size() == 0)
	{
		std::cout << "You Have Died" << std::endl;
	}
	if (objects.size()==0)
	{
		std::cout << "BUT" << std::endl;
	}
	if ((objects.size() == 1 && objects.back()->getName() == Object::Type::player) || objects.size() == 0)
	{
		std::cout << "You have killed the monsters!!!" << std::endl;
	}
	system("PAUSE");

}

void createObjects(std::vector<std::unique_ptr<Object>>& objects, Library& library)
{
	if (objects.size() == 0)
	{
		objects.push_back(library.inventory.find("Player")->second->create(objects));
	}
	std::normal_distribution<double> randomNumMonsters((double)objects.front()->getLevel(), objects.front()->getLevel() / 2.0);
	objects.resize(std::max(1, (int)randomNumMonsters(Object::engine))+1);
	std::generate(objects.begin()+1, objects.end(), [&]()
		{
			return library.inventory.find("Monster")->second->create(objects);
		});
}

void bringOutYourDead(std::vector<std::unique_ptr<Object>>& objects)
{
	objects.erase(
		std::remove_if(objects.begin(), objects.end(),
			[](std::unique_ptr<Object>& object)
			{
				if (object->isDead())
				{
					return true;
				}
				return false;
			}),
		objects.end());

}
