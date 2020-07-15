#ifndef ISTRATEGY_H
#define ISTRATEGY_H
#include <string>
#include <vector>
#include <memory>
class Object;
class Player;
class iStrategy
{
public:
	iStrategy() = delete;
	iStrategy(Player* player, const char commandToActivate, const std::string& actionName);
	virtual void execute(std::vector <std::unique_ptr<Object>>& objects) = 0;
	std::string getActionName() const;
	char getCommand()const;
protected:
	const char commandToActivate{ ' ' };
	const std::string actionName;
	Player* owner{ nullptr };
	

};

#endif // !ISTRATEGY_H