#include <random>
#include <iostream>
#include <algorithm>
#include "Player.h"
#include "Monster.h"
#include "iStrategy.h"
#include "AttackStrategy.h"
#include "HealStrategy.h"
#include "FireballStrategy.h"
#include "FuryStrategy.h"
#include "FearStrategy.h"

Player::Player() :Object(Object::Type::player, 0, 1, 0)
{
	levelUp();
}

Player::Player(const Player& src) noexcept :
	Object(src.name, src.strength, src.health, src.level),
	SP{src.SP}
{
	for (const auto& currItem : src.inventory)
	{
		inventory[currItem.first] = 
			std::make_unique<Item>
			(currItem.second->getClassification(), currItem.second->getBonusValue());
	}
}

Player::Player(Player&& src) noexcept :
	Object(src.name, src.strength, src.health, src.level),
	inventory{ std::move(src.inventory) },
	SP{ src.SP }
{
}

Player& Player::operator=(const Player& src) noexcept
{
	inventory.clear();
	for (const auto& currItem : src.inventory)
	{
		inventory[currItem.first] =
			std::make_unique<Item>
			(currItem.second->getClassification(), currItem.second->getBonusValue());
	}
	name = src.name;
	strength = src.strength;
	health = src.health;
	level = src.level;
	SP = src.SP;
	return *this;
}

Player& Player::operator=(Player&& src) noexcept
{
	inventory.clear();
	name = src.name;
	strength = src.strength;
	health = src.health; 
	level = src.level;
	inventory = std::move(src.inventory);
	SP = src.SP;
	return *this;

}

void Player::levelUp()
{
	system("CLS");
	level++;
	switch (level)
	{
	case 1:
		abilities.push_back(std::make_unique<AttackStrategy>(this));
		break;
	case 2:
		abilities.push_back(std::make_unique<HealStrategy>(this));
		break;
	case 3:
		abilities.push_back(std::make_unique<FuryStrategy>(this));
		break;
	case 4:
		abilities.push_back(std::make_unique<FireballStrategy>(this));
		break;
	case 5:
		abilities.push_back(std::make_unique<FearStrategy>(this));
		break;

	default:
		break;
	}
	std::normal_distribution<double> randomHealth(20.0 + level * 5.0, 5.0);
	health += std::max(1, (int)randomHealth(engine));

	std::normal_distribution<double> randomStrength(3.0 + level, 1.0);
	strength += std::max(1, (int)randomStrength(engine));
	SP += std::max(1, (int)randomStrength(engine));

	//grab new item.
	std::uniform_int_distribution<int> randomItem(0, (int)Item::Type::numTypes - 1);
	std::normal_distribution<double> randomBonus((double)level, (double)level / 2);
	std::unique_ptr<Item> found{ std::make_unique<Item>((Item::Type)randomItem(engine), std::max(1, (int)randomBonus(engine))) };

	std::cout << "You found a " << *found << "!!!!" << std::endl;
	if (
		auto haveOne{ inventory.find(found->getClassification()) };
		haveOne == inventory.end()
		|| *haveOne->second < *found
		)
	{
		std::cout << "You keep the shiny new toy!" << std::endl;
		inventory[found->getClassification()] = std::move(found);
	}
	else
	{
		std::cout << "You toss aside the ugly old thing!" << std::endl;
	}
}

void Player::update(std::vector<std::unique_ptr<Object>>& objects)
{
	displayBattle(objects);
	std::cout << "What do you do?  ";
	for (const auto& ability : abilities)
	{
		std::cout << ability->getActionName() << ", ";
	}
	char command{ 'x' };
	std::cin >> command;
	
	auto activeAbility{ std::find_if(abilities.begin(), abilities.end(),
	[command](std::unique_ptr<iStrategy>& ability)
		{
			return ability->getCommand() == command;
	}) };

	if (activeAbility != abilities.end())
	{
		(*activeAbility)->execute(objects);
	}
	else std::cout << "Not valid input" << std::endl;
	if (health > 0 && objects.size() == 2 && objects.back()->isDead())
	{
		levelUp();
	}
}

void Player::displayBattle(const std::vector<std::unique_ptr<Object>>& objects)
{
	std::cout << *this << std::endl;
	std::cout << inventory;
	std::cout << std::endl << "  Monsters: " << std::endl;
	{
		int i{ 1 };
		std::for_each(objects.begin() + 1, objects.end(), [&](const std::unique_ptr<Object>& object)
			{
				std::cout << "   " << i << ". " << *object << std::endl;

				i++;
			});
	}
}

int Player::getLevel() const
{
	return level;
}

int Player::getSP() const
{
	return SP;
}

void Player::cast(int cost)
{
	SP -= cost;
}

int Player::attack() const
{
	if (auto sword{ inventory.find(Item::Type::sword) }; sword != inventory.end())
	{
		return damageDone(sword->second->getBonusValue());
	}
	else
	{
		return damageDone(0);
	}
}

const std::map<Item::Type, std::unique_ptr<Item>>& Player::getInventory() const
{
	return inventory;
}

void Player::defend(int damage)
{
	int AC{ 0 };
	if (auto armor{ inventory.find(Item::Type::armor) }; armor != inventory.end())
	{
		AC += *armor->second;
	}
	if (auto shield{ inventory.find(Item::Type::shield) }; shield != inventory.end())
	{
		AC += *shield->second;
	}
	damageTaken(damage, AC);
}

void Player::print(std::ostream& o) const
{
	o << "L:" << getLevel() << " ";
	Object::print(o);
	o << " h:" << getHealth() << ", SP:" << getSP();
}

std::ostream& operator<< (std::ostream& o, const std::map<Item::Type, std::unique_ptr<Item>>& src)
{
	for(const auto & item: src)
		{
			o << "  " << *item.second << std::endl;
		};
	return o;
}


