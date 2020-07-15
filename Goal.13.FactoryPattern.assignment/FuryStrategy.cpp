#include "FuryStrategy.h"
#include "Player.h"
#include "Monster.h"
FuryStrategy::FuryStrategy(Player* owner)
	: iStrategy(owner, 'u', "F(u)ry")
{

}

void FuryStrategy::execute(std::vector <std::unique_ptr<Object>>& objects)
{
	if (owner->getStrength() > 0)
	{
		owner->weaken();
		//TODO:: for_each
		objects[1]->defend(2*owner->attack());
		if (objects.size() > 2)
		{
			objects[2]->defend(2 * owner->attack());
		}
	}
}
