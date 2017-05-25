#pragma once
#include "Movable.h"
#include "GFont.h"
#define KEY_SPACE 32
#define KEY_ONE 49

class TileMap;
class Player : public Attackable
{
private:
	int mana, coin;
	int max_hp;
	int hppotion, mppotion;
public:
	static Player* self;
	Player(int x, int y);
	~Player();
	void Action(TileMap* map, WPARAM w);
	void AddCoin(int price) { coin += price; }
	int getCoin() { return coin; }
	void Draw2D(Sprite sprite, GFont* font);
	int getHp() { return hp;  }
	void Skill(TileMap* map);
};

