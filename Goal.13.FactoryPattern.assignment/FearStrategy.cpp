#include <algorithm>
#include "FearStrategy.h"
#include "Player.h"
#include "Monster.h"

FearStrategy::FearStrategy(Player* owner)
	: iStrategy(owner, 'e', "F(e)ar")
{

}
void FearStrategy::execute(std::vector <std::unique_ptr<Object>>& objects)
{
	std::for_each(objects.begin() + 1, objects.end(), [](std::unique_ptr<Object>& monster)
		{
			((Monster*)monster.get())->scare();
		});
}
