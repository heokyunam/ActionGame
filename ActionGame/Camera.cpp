#include "stdafx.h"
#include "Camera.h"


Camera::Camera()
{
	zoom = 1;
}


Camera::~Camera()
{
}

void Camera::Init(Device device)
{
	D3DVIEWPORT9 vp;
	vp.X = 0;
	vp.Y = 0;
	vp.Width = WINDOWWIDTH;
	vp.Height = WINDOWHEIGHT;
	vp.MinZ = 0;
	vp.MaxZ = 1;

	Look(device, &Vector3(-3, 3.5f, -3), &Vector3(0, 0.5f, 0), &Vector3(0, 1, 0));

	D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI / 4, 4.f / 3.f, 0.001f, 1000.0f);
	device->SetTransform(D3DTS_PROJECTION, &matProj);
}

void Camera::Look(Device device, Vector3* eye, Vector3* at, Vector3* up)
{
	meye = *eye + Vector3(zoom, zoom, zoom);
	mat = *at;
	mup = *up;
	D3DXMatrixLookAtLH(&matView, &meye, &mat, &mup);
	device->SetTransform(D3DTS_VIEW, &matView);
}

void Camera::Follow(Device device, Vector3* loc)
{
	Look(device, &Vector3(loc->x - 3, 3.5f, loc->z - 3)
		, &Vector3(loc->x, 0.5f, loc->z) , &mup);
}

void Camera::RayInfo(int mouseX, int mouseY, Vector3* dir, Vector3* eye)
{
	Matrix inView;
	D3DXMatrixInverse(&inView, 0, &matView); 
	float pointX = -((2.0f * (float)mouseX / (float)WINDOWWIDTH) - 1.0f);
	float pointY = ((2.0f * (float)mouseY / (float)WINDOWHEIGHT) - 1.0f);

	pointX = pointX / matProj._11;
	pointY = pointY / matProj._22;

	dir->x = (pointX * inView._11) + (pointY * inView._21) + inView._31;
	dir->y = (pointX * inView._12) + (pointY * inView._22) + inView._32;
	dir->z = (pointX * inView._13) + (pointY * inView._23) + inView._33;

	*eye = meye;
}

Ray* Camera::Intersect(Matrix* world, int mouseX, int mouseY)
{
	Matrix inView, inWorld;
	Ray* ray = new Ray();
	Vector3 dir;

	D3DXMatrixInverse(&inView, 0, &matView);
	D3DXMatrixInverse(&inWorld, 0, world);

	float pointX = ((2.0f * mouseX / WINDOWWIDTH) - 1.0f);
	float pointY = ((2.0f * mouseY / WINDOWHEIGHT) - 1.0f);

	pointX = pointX / matProj._11;
	pointY = pointY / matProj._22;

	dir.x = (pointX * inView._11) + (pointY * inView._21) + inView._31;
	dir.y = (pointX * inView._12) + (pointY * inView._22) + inView._32;
	dir.z = (pointX * inView._13) + (pointY * inView._23) + inView._33;

	D3DXVec3TransformCoord(&ray->origin, &meye, &inWorld);
	D3DXVec3TransformNormal(&ray->dir, &dir, &inWorld);
	D3DXVec3Normalize(&ray->dir, &ray->dir);

	return ray;
}
bool Camera::Collision(Mesh mesh, Ray* ray)
{
	BOOL bHit;
	float pDist;//dist는 실제보다 너무 길게 나간다
	D3DXIntersect(mesh, &ray->origin, &ray->dir, &bHit, 0, 0, 0, &pDist, 0, 0);
	return bHit;
}

Vector3 Camera::Collision(GameObject* obj, Mesh mesh, Ray* ray)
{
	Vector3* vec = obj->getPoints();
	float u, v;
	D3DXIntersect(mesh, &ray->origin, &ray->dir, 0,
		0, &u, &v, 0, 0, 0);
	Vector3 value = vec[0] + u * (vec[1] - vec[0]) + v * (vec[2] - vec[1]);
	delete[] vec;
	return value;
}

void Camera::Zoom(Device device, float zoom)
{
	this->zoom = zoom;
	Look(device, &meye, &mat, &mup);
}