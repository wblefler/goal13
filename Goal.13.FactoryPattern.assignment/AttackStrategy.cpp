#include <iostream>
#include "AttackStrategy.h"
#include "Object.h"
#include "Monster.h"
#include "Player.h"

AttackStrategy::AttackStrategy(Player* owner)
	: iStrategy(owner, 'a', "(a)ttack")
{
}

void AttackStrategy::execute(std::vector <std::unique_ptr<Object>>& objects)
{
	std::cout << "Which Monster: ";
	unsigned int monsterNum{ 0 };
	std::cin >> monsterNum;
	if (monsterNum > 0 && monsterNum <= objects.size())
	{
		objects[monsterNum]->defend(owner->attack());
	}	
}
