#include "stdafx.h"
#include "Stage.h"
#include "DataManager.h"
#include "Tile.h"


Stage::Stage()
{
}


Stage::~Stage()
{
}

void Stage::Init()
{
	//행이 x 열이 y
	mapdata.push_back("BRBBBBBBBB");
	mapdata.push_back("BBBBBB00BB");
	mapdata.push_back("BBBBBB00BB");
	mapdata.push_back("BBBBBH00BB");
	mapdata.push_back("BBBBBBBBRB");
	mapdata.push_back("BBBBBBBBBB");
	mapdata.push_back("BBRBBBBBRB");
	mapdata.push_back("BBBBBBBBBB");
	mapdata.push_back("00000000BB");
	mapdata.push_back("00000000BB");
	mapdata.push_back("00000000BB");
	mapdata.push_back("BBBBBBBBBB");
	mapdata.push_back("BBBBBBBBBB");
	mapdata.push_back("BBBBBBBBBB");
	mapdata.push_back("BBBBBBBBBB");
	mapdata.push_back("BBBBBBBBBB");
	mapdata.push_back("BBBBBBBBBB");
	time = 2 * 100 * 60;
	enemies.push_back(new Enemy("slime", &coins, &enemies, 2, 1));
	enemies.push_back(new Enemy("slime", &coins, &enemies, 3, 2));
	enemies.push_back(new Enemy("slime", &coins, &enemies, 5, 8));
	enemies.push_back(new Enemy("slime", &coins, &enemies, 8, 8));
	enemies.push_back(new Enemy("bigslime", &coins, &enemies, 11, 2));
	enemies.push_back(new Enemy("bigslime", &coins, &enemies, 11, 8));
	enemies.push_back(new Enemy("bigslime", &coins, &enemies, 13, 2));

	font = new GFont();
	font->Load(device, "굴림체");
	player = new Player(0, 0);
	map = new TileMap(&enemies);
	map->Encode(&mapdata);
}

void Stage::Draw()
{
	map->Draw(device);
	player->Draw(device);
	SVectorDraw(enemies);
	SVectorDraw(coins);
}

void Stage::Draw2D(Sprite sprite)
{
	if (enemies.size() == 0)
	{
		font->Draw(sprite, "WIN!!", WINDOWWIDTH / 2 - 20, WINDOWHEIGHT / 2 - 80);
	}
	int sec = time / 100;
	char text[50];
	sprintf_s(text, "%d : %d", sec / 60, sec % 60);
	font->Draw(sprite, text, 0, 0);

	player->Draw2D(sprite, font);
}

int Stage::Update()
{
	if (enemies.size() == 0) return 0;
	time--;
	player->Update();
	camera->Follow(device, player->getLoc());
	for (SVector<Enemy*>::iterator i = enemies.begin(); i != enemies.end();)
	{	
		(*i)->AIFollow(map, player);
		if ((*i)->Update())
		{ 
			i++; 
		}
		else 
		{ 
			Enemy* t = (*i); 
			i = enemies.erase(i); 
			delete t;
		}
	}
	for (SVector<Coin*>::iterator i = coins.begin(); i != coins.end();)
	{
		Coin* c = (*i);
		if (c->isCollide(player->getTileX(), player->getTileY()))
		{
			player->AddCoin(c->getPrice());
			i = coins.erase(i);
			delete c;
		}
		else
		{
			i++;
		}
	}
	return 0;
}

void Stage::Destroy()
{
	delete map;
}

void Stage::WndProc(UINT msg, WPARAM w, LPARAM l)
{
	if (msg == WM_LBUTTONDOWN)
	{
		Vector3 dir, eye;
		camera->RayInfo(mouseX, mouseY, &dir, &eye);
		Tile* tile = map->Picking(&dir, &eye);
		if(tile) tile->ChangeTile("rocktile");
	}
	
	if (msg == WM_MOUSEWHEEL)
	{
		((short)HIWORD(w) < 0) ? camera->Zoom(device, 0.1f) : camera->Zoom(device, -0.1f);
	}

	if (msg == WM_KEYDOWN)
	{
		player->Action(map, w);
		if (w == 'G')
		{
		}
	}
}
