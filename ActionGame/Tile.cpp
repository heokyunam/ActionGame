#include "stdafx.h"
#include "Tile.h"
#include "DataManager.h"


Tile::Tile(String tile, float x, float y, float z) : GameObject()
{
	model = (NormalModel*) DataManager::GetInstance()->getModel(tile);
	ReSize(0.01f);
	Move(x * TILESIZE, y, z * TILESIZE);
	Rotate(0, D3DX_PI, 0);
}


Tile::~Tile()
{
}

Mesh Tile::getMesh()
{
	return ((NormalModel*)model)->getMesh();
}

void Tile::Draw(Device device)
{
	device->SetTransform(D3DTS_WORLD, &matWorld);

	model->Draw(device);
}

void Tile::ChangeTile(String str)
{
	model = (NormalModel*) DataManager::GetInstance()->getModel(str);
}

TileMap::TileMap(SVector<Enemy*>* enemies)
{
	this->enemies = enemies;
	width = height = 0;
	tiles = 0;
}

TileMap::~TileMap()
{
	DeleteTile();
}

void TileMap::Draw(Device device)
{
	if (tiles)
	{
		for (int i = 0; i < width; i++)
		{
			for (int j = 0; j < height; j++)
			{
				if (tiles[i][j]) 
					tiles[i][j]->Draw(device);
			}
		}
	}	
}

void TileMap::Update()
{

}

Tile* TileMap::Picking(Vector3* dir, Vector3* eye)
{
	return 0;
}

void TileMap::DeleteTile()
{
	if (tiles)
	{
		for (int i = 0; i < width; i++)
		{
			if (tiles[i])
			{
				for (int j = 0; j < height; j++)
				{
					if (tiles[i][j]) delete tiles[i][j];
				}
				delete[] tiles[i];
			}

		}
		delete[] tiles;
	}	
}

void TileMap::Encode(SVector<String>* map)
{
	this->data = map;
	width = map->size();
	tiles = new Tile**[map->size()];
	DataManager* dm = DataManager::GetInstance();
	for (int i = 0; i < map->size(); i++)
	{
		String line = (*map)[i];
		if(i == 0) height = line.size();
		tiles[i] = new Tile*[line.size()];
		for (int j = 0; j < line.size(); j++)
		{
			switch (line[j])
			{
			case 'B'://basic
				tiles[i][j] = new Tile("basictile", i, 0, j);
				break;
			case 'R'://rock
				tiles[i][j] = new Tile("rocktile", i, 0, j);
				break;
			case 'H'://house
				tiles[i][j] = new Tile("housetile", i, 0, j);
				break;
			default:
				tiles[i][j] = 0;
				break;
			}
		}
	}
}


bool TileMap::isMovableTile(int targetX, int targetY)
{
	if (targetX < 0 || targetX >= width || targetY < 0 || targetY >= height) return false;
	for (int i = 0; i < enemies->size(); i++)
	{
		Enemy* e = (*enemies)[i];
		if (e->isCollide(targetX, targetY) > 0) {
			return false;
		}
	}

	switch ((*data)[targetX][targetY])
	{
	case 'B':
	case 'H':
	case '1':
		return true;
	default:
		return false;
	}
}