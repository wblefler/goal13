#include "iStrategy.h"
#include "Object.h"
#include "Player.h"

iStrategy::iStrategy(Player* player, const char commandToActivate, const std::string& actionName)
	: owner(player), commandToActivate(commandToActivate), actionName(actionName)
{
}

std::string iStrategy::getActionName() const
{
	return actionName;
}

char iStrategy::getCommand() const
{
	return commandToActivate;
}
