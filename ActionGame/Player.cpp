#include "stdafx.h"
#include "Player.h"
#include "Tile.h"
#include "DataManager.h"

Player* Player::self;
Player::Player(int x, int y) : Attackable(DataManager::GetInstance()->getKindData("player"), x, y)
{
	self = this;
	mana = 10;
	coin = 0;
	hppotion = mppotion = 2;
	max_hp = DataManager::GetInstance()->getKindData("player")->hp;
}


Player::~Player()
{
}

void Player::Action(TileMap* map, WPARAM w)
{
	switch (w)
	{
	case DIR_LEFT:
		SetTarget(map, 0, 1);
		Turn(w);
		break;
	case DIR_UP:
		SetTarget(map, 1, 0);
		Turn(w);
		break;
	case DIR_RIGHT:
		SetTarget(map, 0, -1);
		Turn(w);
		break;
	case DIR_DOWN:
		SetTarget(map, -1, 0);
		Turn(w);
		break;
	case KEY_SPACE:
		Attack(map);
		break;
	case KEY_ONE:
		if (hppotion > 0)
		{
			hp += 20;
			hp = min(hp, max_hp);
			hppotion--;
		}
		break;
	case 'S':
		Skill(map);
		break;
	case KEY_ONE + 1:
		if (mppotion > 0)
		{
			mana += 1;
			mppotion--;
		}
		break;
	}
}

void Player::Skill(TileMap* map)
{
	if (attackCount >= ATTACKMAXCOUNT && walkCount == 0 && mana > 0)
	{
		attackCount = 0;
		SVector<Enemy*>* enemies = map->getEnemies();
		Vector2 vec = TargetVector();
		for (int i = 0; i < enemies->size(); i++)
		{
			Enemy* e = enemies[0][i];
			if (e->getTileX() <= (int)vec.x + 1 && e->getTileY() <= (int)vec.y + 1
				&& e->getTileX() >= (int) vec.x - 1 && e->getTileX() >= (int)vec.y - 1)
			{
				e->Damage(2);
			}
		}
		mana--;
	}
}

void Player::Draw2D(Sprite sprite, GFont* font)
{
	char text[50];
	int rate = - hp * 200 / max_hp;
	Texture tex = DataManager::GetInstance()->getTexture("hpgage");
	sprite->Draw(tex, 0, 0, &Vector3(0, WINDOWHEIGHT / 2 + 185 + rate, 0), 0xffffffff);
	tex = DataManager::GetInstance()->getTexture("gageframe");
	sprite->Draw(tex, 0, 0, &Vector3(0, WINDOWHEIGHT / 2 - 15, 0), 0xffffffff);
	tex = DataManager::GetInstance()->getTexture("mana");
	for (int i = 0; i < mana; i++)
	{
		sprite->Draw(tex, 0, 0, &Vector3(140 + i * 35, WINDOWHEIGHT / 2 + 50, 0), 0xffffffff);
	}
	sprintf_s(text, "COIN : %d", coin);
	font->Draw(sprite, text, 0, 25);
	tex = DataManager::GetInstance()->getTexture("hppotion");
	sprite->Draw(tex, 0, 0, &Vector3(140, WINDOWHEIGHT / 2 + 100, 0), 0xffffffff);
	tex = DataManager::GetInstance()->getTexture("mppotion");
	sprite->Draw(tex, 0, 0, &Vector3(290, WINDOWHEIGHT / 2 + 100, 0), 0xffffffff);

	sprintf_s(text, "x%d", hppotion);
	font->Draw(sprite, text, 240, WINDOWHEIGHT / 2 + 100);
	sprintf_s(text, "x%d", mppotion);
	font->Draw(sprite, text, 390, WINDOWHEIGHT / 2 + 100);
}