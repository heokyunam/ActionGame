#include "stdafx.h"
#include "Enemy.h"
#include "DataManager.h"
#include "Coin.h"

Enemy::Enemy(String kind, SVector<Coin*>* coins, SVector<Enemy*>* enemies, int x, int y) : Attackable(DataManager::GetInstance()->getKindData(kind), x, y)
{
	actionTerm = 0;
	this->coins = coins;
	this->enemies = enemies;
	if (memcmp(kind.c_str(), "slime", 3) == 0)
	{
		range = 3;
		remoteRange = 0;
	}
	else if (memcmp(kind.c_str(), "bigslime", 3) == 0)
	{
		range = 3;
		remoteRange = 5;
	}
}


Enemy::~Enemy()
{
}

void Enemy::Draw(Device device)
{
	Attackable::Draw(device);

	SVectorDraw(missiles);
}
bool Enemy::Update()
{
	if (actionTerm < ENEMYACTIONTERM) actionTerm++;
	SVectorUpdate(SVector<Missile*>, Missile*, missiles);
	if (!isAlive())
	{
		coins->push_back(new Coin(5, getTileX(), getTileY()));
		if (remoteRange > 0)
		{
			enemies->push_back(new Enemy("slime", coins, enemies, getTileX(), getTileY()));
			enemies->push_back(new Enemy("slime", coins, enemies, getTileX(), getTileY()));
			enemies->push_back(new Enemy("slime", coins, enemies, getTileX(), getTileY()));
			enemies->push_back(new Enemy("slime", coins, enemies, getTileX(), getTileY()));
		}
	}
	return Attackable::Update();
}

bool Enemy::AttackCheck(Player* p)
{
	if (actionTerm >= ENEMYACTIONTERM)
	{
		Vector2 vec = TargetVector();
		if (vec.x == p->getTileX() && vec.y == p->getTileY())
		{
			attackCount = 0;
			enemy = p;
			actionTerm = 0;
			return true;
		}
	}
	return false;
}

void Enemy::AIFollow(TileMap* map, Player* p)
{
	if (actionTerm >= ENEMYACTIONTERM)
	{
		if (walkCount == 0)
		{
			int difX = p->getTileX() - this->getTileX();
			int difY = p->getTileY() - this->getTileY();
			float length = LENGTH(difX, difY);
			if (length < range)
			{
				if (difX > 0)
				{
					Turn(DIR_UP);
					if (!AttackCheck(p))	SetTarget(map, 1, 0);
				}
				else if (difY > 0)
				{
					Turn(DIR_LEFT);
					if (!AttackCheck(p)) SetTarget(map, 0, 1);
				}
				else if (difX < 0)
				{
					Turn(DIR_DOWN);
					if (!AttackCheck(p)) SetTarget(map, -1, 0);
				}
				else if (difY < 0)
				{
					Turn(DIR_RIGHT);
					if (!AttackCheck(p)) SetTarget(map, 0, -1);
				}
			}
			else if (length < remoteRange)
			{
				missiles.push_back(new Missile(p, this, damage));
				if (difX < 0) Turn(DIR_DOWN);
				else Turn(DIR_UP);
			}
		}
		actionTerm = 0;
	}
}

Missile::Missile(Player* p, Enemy* e, int damage)
{
	player = p;
	model = DataManager::GetInstance()->getModel("slimemissile");
	this->Move(e->getLoc());
	this->damage = damage;
	ReSize(0.01f);
}

bool Missile::Update()
{
	float difX = player->getX() - this->getX();
	float difZ = player->getZ() - this->getZ();
	Move(difX / (MISSILEMAXCOUNT - this->followCount), 0, difZ / (MISSILEMAXCOUNT - this->followCount), true);
	this->followCount++;
	if (followCount < MISSILEMAXCOUNT == false) player->Damage(damage);
	return followCount < MISSILEMAXCOUNT;
}

void Missile::Draw(Device device)
{
	device->SetTransform(D3DTS_WORLD, &matWorld);

	model->Draw(device);
}