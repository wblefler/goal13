#ifndef MONSTERFACTORY_H
#define MONSTERFACTORY_H

#include"ObjectFactory.h"
#include"Monster.h"

class MonsterFactory : public ObjectFactory {
public:
	std::unique_ptr<Object> create() { return std::make_unique<Monster>(); }
};


#endif