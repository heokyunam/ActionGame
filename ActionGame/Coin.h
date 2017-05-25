#pragma once
#include "Movable.h"
class Coin : public Movable
{
private:
	int price;
public:
	Coin(int price, int x, int y);
	~Coin();
	void Draw(Device device);
	int getPrice() { return price; }
};

