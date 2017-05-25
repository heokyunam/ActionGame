#include "stdafx.h"
#include "GameObject.h"
#include "DataManager.h"

GameObject::GameObject()
{
	Move(0, 0, 0);
	Rotate(0, D3DX_PI, 0);
	ReSize(0.01f);
}


GameObject::~GameObject()
{
}

void GameObject::Move(Vector3* loc, bool isRelative)
{
	if (isRelative)
	{
		mloc += *loc;
	}
	else
		mloc = *loc;
	UpdateMatWorld();
}

void GameObject::Move(float x, float y, float z, bool isRelative)
{
	Move(&Vector3(x, y, z), isRelative);
}

void GameObject::Rotate(Vector3* rot, bool isRelative)
{
	if (isRelative)
		mrot += *rot;
	else
		mrot = *rot;
	UpdateMatWorld();
}

void GameObject::Rotate(float x, float y, float z, bool isRelative)
{
	Rotate(&Vector3(x, y, z), isRelative);
}


void GameObject::ReSize(float size)
{
	this->size = size;
	UpdateMatWorld();
}


void GameObject::UpdateMatWorld()
{
	Quaternion q;
	Matrix temp;
	D3DXMatrixRotationX(&matRot, mrot.x);
	D3DXMatrixRotationY(&temp, mrot.y);
	matRot *= temp;
	D3DXMatrixRotationZ(&temp, mrot.z);
	matRot *= temp;
	D3DXQuaternionRotationMatrix(&q, &matRot);

	D3DXMatrixTransformation(&matWorld, NUMVEC(0), 0,
		NUMVEC(size), NUMVEC(0), &q, &mloc);
}
Vector3* GameObject::getPoints()
{
	Vector3* vec = new Vector3[3];
	vec[0] = mloc + Vector3(1, 0, 0);
	vec[1] = mloc + Vector3(0, 0, 1);
	vec[2] = mloc + Vector3(1, 0, 1);
	D3DXVec3TransformCoord(&vec[0], &vec[0], &matRot);
	D3DXVec3TransformCoord(&vec[1], &vec[1], &matRot);
	D3DXVec3TransformCoord(&vec[2], &vec[2], &matRot);

	return vec;
}