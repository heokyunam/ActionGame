#pragma once
#include <comdef.h>
#include "Camera.h"
class Scene
{
protected:
	Device device;
	HWND* hWnd;
	int mouseX, mouseY;
	Camera* camera;
public:
	Scene() {}
	~Scene() {}
	void Setup(Device device, HWND* hWnd) 
	{
		this->device = device;
		this->hWnd = hWnd;
		camera = new Camera();
		camera->Init(device);
	}
	virtual void Init() {}
	virtual void Draw() {}
	virtual void Draw2D(Sprite sprite) {}
	virtual int Update() { return 0; } //0이 아닌 경우 수명을 다함
	virtual void Destroy() {}
	virtual void WndProc(UINT msg, WPARAM w, LPARAM l)
	{
		if (msg == WM_MOUSEMOVE)
		{
			mouseX = LOWORD(l);
			mouseY = HIWORD(l);
		}
	}
};
class Framework
{
private:
	Device device;
	Sprite sprite;
	HWND hWnd;
	Scene* scene;
public:
	Framework();
	~Framework();
	void InitDevice(HWND hWnd);
	void Init();
	void Update();
	void WndProc(UINT msg, WPARAM w, LPARAM l)
	{
		if (scene) scene->WndProc(msg, w, l);
	}
};