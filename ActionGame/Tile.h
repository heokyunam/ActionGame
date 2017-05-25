#pragma once
#include "GameObject.h"
#include "Camera.h"
#include "Movable.h"
#include "Enemy.h"

#define TILESIZE 0.5f

class Tile : public GameObject
{
private:
	NormalModel* model;
public:
	Tile(String tile, float x, float y, float z);
	~Tile();
	void ChangeTile(String str);
	void Draw(Device device);
	Mesh getMesh();
};

class TileMap
{
private:
	Tile*** tiles;
	SVector<Enemy*>* enemies;
	SVector<String>* data;
	int height, width;
public:
	TileMap(SVector<Enemy*>* enemies);
	~TileMap();
	void Draw(Device device);
	void Update();
	void Encode(SVector<String>* map);
	Tile* getTile(int x, int z) { return tiles[x][z]; }
	Tile* Picking(Vector3* dir, Vector3* eye);
	void DeleteTile();
	int getHeight() { return height; }
	int getWidth() { return width; }
	bool isMovableTile(int targetX, int targetY);
	SVector<Enemy*>* getEnemies() { return enemies; }
};