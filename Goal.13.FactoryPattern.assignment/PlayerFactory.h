#ifndef PLAYERFACTORY_H
#define PLAYERFACTORY_H

#include"ObjectFactory.h"
#include"Player.h"

class PlayerFactory : public ObjectFactory {
public:
	std::unique_ptr<Object> create() { return std::make_unique<Player>(); }
};


#endif