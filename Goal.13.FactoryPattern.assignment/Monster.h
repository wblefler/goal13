#ifndef MONSTER_H
#define MONSTER_H
#include "Object.h"

class Player;
class Monster :
	public Object
{
public:
	void update(std::vector<std::unique_ptr<Object>>& objects) override;
	Monster() {};
	Monster(const std::unique_ptr<Object>& player);
	int attack() const override;
	void defend(int damage) override;
	void print(std::ostream& o) const override;
	void scare();
private:
	bool afraid{ false };
	int AC{ 0 };

};

#endif // !MONSTER_H