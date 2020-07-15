#include <iostream>
#include "HealStrategy.h"
#include "Player.h"
HealStrategy::HealStrategy(Player* owner)
	: iStrategy(owner, 'h', "(h)eal")
{

}

void HealStrategy::execute(std::vector <std::unique_ptr<Object>>& objects)
{
	if (owner->getSP() >= 2)
	{
		std::normal_distribution<double> randomHeal(owner->getStrength(), 3.0);
		int  amountHealed{ std::max(1, (int)randomHeal(Object::engine)) };

		owner->cast(2);
		std::cout << *owner << " is healed by " << amountHealed << "hp!" << std::endl;
		owner->heal(amountHealed);
	}
	else
	{
		std::cout << "Not enough SP!!!" << std::endl;
	}
}
