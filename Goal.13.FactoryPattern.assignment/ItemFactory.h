#ifndef ITEM_FACTORY_H
#define ITEM_FACTORY_H
#include "ObectFactory.h"
#include "Item.h"
class ItemFactory :public ObjectFactory
{
public:
	std::unique_ptr<Object> create()
	{
		return std::make_unique<Item>();
	}

};
#endif // !ITEM_FACTORY_H