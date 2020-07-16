#ifndef LIBRARY_H
#define LIBRARY_H

#include<string>
#include<map>
#include<memory>

#include"PlayerFactory.h"
#include"MonsterFactory.h"
#include"ObjectFactory.h"
class Library {

public:
	//virtual std::unique_ptr<Object> create() = 0;
	//std::unique_ptr<Object> create() { return std::make_unique<Child1>(); }
	Library() {
		inventory["Player"] = std::make_unique<PlayerFactory>();
		inventory["Enemy"] = std::make_unique<MonsterFactory>();
	}
	std::map<std::string, std::unique_ptr<ObjectFactory>> inventory;
};

#endif