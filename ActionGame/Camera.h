#pragma once
#include "GameObject.h"
struct Ray
{
	Vector3 origin, dir;
};
class Camera
{
private:
	Matrix matProj;
	Matrix matView;
	Vector3 meye;
	Vector3 mat;
	Vector3 mup;
	float zoom;
public:
	Camera();
	~Camera();
	void Init(Device device);
	void Look(Device device, Vector3* eye, Vector3* at, Vector3* up);
	void RayInfo(int mouseX, int mouseY, Vector3* dir, Vector3* eye);
	Ray* Intersect(Matrix* world, int mouseX, int mouseY);
	bool Collision(Mesh mesh, Ray* ray);
	Vector3 Collision(GameObject* obj, Mesh loc, Ray* ray);
	void Zoom(Device device, float zoom);
	void Follow(Device device, Vector3* loc);
};

