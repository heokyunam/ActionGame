#pragma once
#include "Model.h"
class GameObject
{
protected:
	Matrix matWorld;
	Matrix matRot;
	Vector3 mloc;
	Vector3 mrot;
	float size;
public:
	GameObject();
	~GameObject();

	void Move(Vector3* loc, bool isRelative = false);
	void Move(float x, float y, float z, bool isRelative = false);

	void Rotate(Vector3* rot, bool isRelative = false);
	void Rotate(float x, float y, float z, bool isRelative = false);

	void ReSize(float size);

	void UpdateMatWorld();

	Matrix* getMatWorld() { return &matWorld; }
	Vector3* getLoc() { return &mloc; }
	Vector3* getRot() { return &mrot; }

	Vector3* getPoints();
	float getX() { return mloc.x; }
	float getY() { return mloc.y; }
	float getZ() { return mloc.z; }
};

