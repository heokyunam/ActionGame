#pragma once
#include "Framework.h"
#include "GameObject.h"
#include "Tile.h"
#include "Movable.h"
#include "Enemy.h"
#include "Player.h"
#include "Coin.h"
#include "GFont.h"

class Stage : public Scene
{
private:
	SVector<String> mapdata;
	SVector<Enemy*> enemies;
	SVector<Coin*> coins;
	TileMap* map;
	Player* player;
	GFont* font;
	bool isLoading;
	UINT time;
public:
	Stage();
	~Stage();

	void Init();
	void Draw();
	void Draw2D(Sprite sprite);
	int Update();
	void Destroy();
	void WndProc(UINT msg, WPARAM w, LPARAM l);
};

