#pragma once
#include "GameObject.h"
#define WALKMAXCOUNT 30
#define DMGMAXCOUNT 20
#define ATTACKMAXCOUNT 33
#define TILEDIST 0.5f
#define DIR_LEFT 37
#define DIR_UP 38
#define DIR_RIGHT 39
#define DIR_DOWN 40
#define COLLIDE_PAST 1
#define COLLIDE_NOW 2

class Tile;
class TileMap;
class KindData;
class Movable : public GameObject
{
protected:
	Model* model;
	int targetX, targetZ;
	int x, z;
	int walkCount, dmgCount;
	int dir;
	Texture damaged;
	Tile* targetTile;
	int hp;
public:
	Movable(KindData* data, int x, int y);
	~Movable();
	void Draw(Device device);
	void SetTarget(TileMap* map, int addX, int addY);
	virtual bool Update();
	void Turn(int dir);
	int getTileX() { return x; }
	int getTileY() { return z; }
	int getDir() { return dir; }
	virtual void Damage(int value);
	bool isAlive() { return hp > 0;  }
	int isCollide(int x,int y);
};

class Attackable : public Movable
{
protected:
	Model* attack;
	Movable* enemy;
	int attackCount;
	int damage;
	int defDmg;
public:
	Attackable(KindData* data, int x, int y);
	void Attack(TileMap* map);
	bool Update();
	void Draw(Device device);
	Vector2 TargetVector();
};