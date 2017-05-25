#include "stdafx.h"
#include "Movable.h"
#include "DataManager.h"
#include "Tile.h"


Movable::Movable(KindData* data, int x, int y) : GameObject()
{
	ReSize(0.01f);
	this->x = this->targetX = x;
	this->z = this->targetZ = y;
	Move(TILEDIST * this->x, 0.5f, TILEDIST * this->z);
	walkCount = 0;
	dmgCount = DMGMAXCOUNT;
	damaged = DataManager::GetInstance()->getTexture("Damaged");
	if (data)
	{
		this->hp = data->hp;
		model = data->makeModel(data->modelNormal);
	}
}


Movable::~Movable()
{
}

void Movable::Draw(Device device)
{
	device->SetTransform(D3DTS_WORLD, &matWorld);

	if (dmgCount < DMGMAXCOUNT)
		model->Draw(device, damaged);
	else
		model->Draw(device);
}

int Movable::isCollide(int x, int y)
{
	if (this->targetX == x && this->targetZ == y)
	{
		return COLLIDE_NOW;
	}
	if (this->x == x && this->z == y)
	{
		return COLLIDE_PAST;
	}
	return 0;
}

void Movable::SetTarget(TileMap* map, int addX, int addY)
{
	if (walkCount == 0 && map->isMovableTile(targetX + addX, targetZ + addY))
	{
		this->targetX += addX;
		this->targetZ += addY;
		walkCount = 0;
	}
}

void Movable::Turn(int dir)
{
	this->dir = dir;
	switch (dir)
	{
	case DIR_LEFT:
		Rotate(0, D3DX_PI, 0);
		break;
	case DIR_UP:
		Rotate(0, -D3DX_PI / 2, 0);
		break;
	case DIR_RIGHT:
		Rotate(0, 2 * D3DX_PI, 0);
		break;
	case DIR_DOWN:
		Rotate(0, D3DX_PI / 2, 0);
		break;
	}
}

bool Movable::Update()
{
	if (dmgCount < DMGMAXCOUNT)
		dmgCount++;
	model->Update(0.02f);
	if (x != targetX)
	{
		int dir = targetX - x;
		if (walkCount < WALKMAXCOUNT)
		{
			this->mloc.x += dir * TILEDIST / WALKMAXCOUNT;
			walkCount++;
		}
		else if (walkCount == WALKMAXCOUNT)
		{
			this->mloc.x = TILEDIST * targetX;
			walkCount = 0;
			x = targetX;
		}
	}
	else if (z != targetZ)
	{
		int dir = targetZ - z;
		if (walkCount < WALKMAXCOUNT)
		{
			this->mloc.z += dir * TILEDIST / WALKMAXCOUNT;
			walkCount++;
		}
		else if (walkCount == WALKMAXCOUNT)
		{
			this->mloc.z = TILEDIST * targetZ;
			walkCount = 0;
			z = targetZ;
		}
	}
	UpdateMatWorld();
	return isAlive();
}
void Movable::Damage(int value) 
{
	hp -= value;
	dmgCount = 0;
}
Attackable::Attackable(KindData* data, int x, int y) : Movable(data, x, y)
{
	this->attack = data->makeModel(data->modelAttack);
	attackCount = ATTACKMAXCOUNT;
	this->damage = data->damage;
	this->defDmg = data->defDmg;
}

void Attackable::Attack(TileMap* map)
{
	if (attackCount >= ATTACKMAXCOUNT && walkCount == 0)
	{
		attackCount = 0;
		SVector<Enemy*>* enemies = map->getEnemies();
		Vector2 vec = TargetVector();
		for (int i = 0; i < enemies->size(); i++)
		{
			Enemy* e = enemies[0][i];
			if (e->getTileX() == (int)vec.x && e->getTileY() == (int)vec.y)
			{
				enemy = e;
				break;
			}
		}
	}
}

Vector2 Attackable::TargetVector()
{
	Vector2 vec(x, z);
	switch (dir)
	{
	case DIR_LEFT:
		vec += Vector2(0, 1);
		break;
	case DIR_UP:
		vec += Vector2(1, 0);
		break;
	case DIR_RIGHT:
		vec += Vector2(0, -1);
		break;
	case DIR_DOWN:
		vec += Vector2(-1, 0);
		break;
	}
	return vec;
}

void Attackable::Draw(Device device)
{
	if (attackCount < ATTACKMAXCOUNT)
	{
		device->SetTransform(D3DTS_WORLD, &matWorld);
		if (dmgCount < DMGMAXCOUNT)
			attack->Draw(device, damaged);
		else
			attack->Draw(device);
	}
	else
	{
		Movable::Draw(device);
	}
}

bool Attackable::Update()
{
	if (attackCount < ATTACKMAXCOUNT)
	{
		attack->Update(0.02f);
		attackCount++;
	}
	else if (attackCount == ATTACKMAXCOUNT)
	{
		walkCount = 0;
		attackCount++;
		if (enemy)
		{
			Vector2 vec = TargetVector();
			int code = enemy->isCollide(vec.x, vec.y);
			if (code == COLLIDE_NOW)
			{
				enemy->Damage(damage);
				enemy = 0;
			}
		}
	}
	else
	{
		Movable::Update();
	}
	return isAlive();
}