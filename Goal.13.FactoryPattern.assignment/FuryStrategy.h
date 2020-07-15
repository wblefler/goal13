#ifndef FURYSTRATEGY_H
#define FURYSTRATEGY_H


#include "iStrategy.h"
class FuryStrategy :
	public iStrategy
{
public:
	FuryStrategy() = delete;
	FuryStrategy(Player* owner);
	void execute(std::vector <std::unique_ptr<Object>>& objects) override;
};

#endif // !FURYSTRATEGY_H