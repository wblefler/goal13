#ifndef HEALSTRATEGY_H
#define HEALSTRATEGY_H


#include "iStrategy.h"
class HealStrategy :
	public iStrategy
{
public:
	HealStrategy() = delete;
	HealStrategy(Player* owner);
	void execute(std::vector <std::unique_ptr<Object>>& objects) override;
};

#endif // !HEALSTRATEGY_H