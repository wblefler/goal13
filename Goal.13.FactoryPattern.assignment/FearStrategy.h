#ifndef FEARSTRATEGY_H
#define FEARSTRATEGY_H


#include "iStrategy.h"
class FearStrategy :
	public iStrategy
{
public:
	FearStrategy() = delete;
	FearStrategy(Player* owner);
	void execute(std::vector <std::unique_ptr<Object>>& objects) override;
};

#endif // !FEARSTRATEGY_H