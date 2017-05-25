#pragma once
#include "Movable.h"
#include "Player.h"
#define LENGTH(x, y) (sqrt((x) * (x) + (y) * (y)))
#define ENEMYRANGE 4
#define ENEMYACTIONTERM 100
#define MISSILEMAXCOUNT 10

class Coin;
class TileMap;
class Missile;
class Enemy : public Attackable
{
private:
	SVector<Enemy*>* enemies;
	SVector<Missile*> missiles;
	SVector<Coin*>* coins;
	int actionTerm;
	int range, remoteRange;
public:
	Enemy(String kind, SVector<Coin*>* coins, SVector<Enemy*>* enemies, int x, int y);
	~Enemy();
	bool Update();
	void AIFollow(TileMap* map, Player* player);
	bool AttackCheck(Player* p);
	void Draw(Device device);
};

class Missile : public GameObject
{
private:
	Model* model;
	Player* player;
	int followCount;
	int damage;
public:
	Missile(Player* p, Enemy* e, int damage);
	~Missile() {}
	bool Update();
	void Draw(Device device);
};