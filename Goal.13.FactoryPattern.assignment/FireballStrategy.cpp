#include <iostream>
#include "FireballStrategy.h"
#include "Player.h"
#include "Monster.h"

FireballStrategy::FireballStrategy(Player* owner)
	: iStrategy(owner, 'f', "(f)ireball")
{

}
void FireballStrategy::execute(std::vector <std::unique_ptr<Object>>& objects)
{
	if (owner->getSP() >= 5)
	{
		owner->cast(5);
		//TODO:: For_Each
		objects[1]->defend(owner->attack());
		if (objects.size() > 2)
		{
			objects[2]->defend(owner->attack());
		}
		if (objects.size() > 3)
		{
			objects[3]->defend(owner->attack());
		}
	}
	else
	{
		std::cout << "Not enough SP!!!" << std::endl;
	}
}
