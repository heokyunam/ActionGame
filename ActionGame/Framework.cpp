#include "stdafx.h"
#include "Framework.h"
#include "Stage.h"
#include "DataManager.h"


Framework::Framework()
{
}


Framework::~Framework()
{
}

void Framework::InitDevice(HWND hWnd)
{
	LPDIRECT3D9 d = Direct3DCreate9(D3D_SDK_VERSION);
	D3DPRESENT_PARAMETERS pp;
	ZeroMemory(&pp, sizeof(D3DPRESENT_PARAMETERS));
	pp.AutoDepthStencilFormat = D3DFMT_D24S8;
	pp.BackBufferCount = 1;
	pp.BackBufferFormat = D3DFMT_A8R8G8B8;
	pp.EnableAutoDepthStencil = true;
	pp.PresentationInterval = D3DPRESENT_INTERVAL_ONE;
	pp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	pp.Windowed = true;
	pp.hDeviceWindow = hWnd;

	HRESULT h = d->CreateDevice(0, D3DDEVTYPE_HAL, 0, D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&pp, &device);
	_com_error erro(h);
	const TCHAR* msg = erro.ErrorMessage();

	D3DXCreateSprite(device, &sprite);
	this->hWnd = hWnd;

	scene = new Stage();
	scene->Setup(device, &hWnd);

	DataManager::InitInstance(device);
}
void Framework::Init() 
{
	if (scene) scene->Init();
}
void Framework::Update()
{
	if (scene) {
		if (scene->Update() > 0)
		{
			//장면 전환
		}
		device->Clear(1, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0xffa0ffff, 1, 0);
		device->BeginScene();

		scene->Draw();

		device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
		device->SetRenderState(D3DRS_ZENABLE, true);
		device->SetRenderState(D3DRS_ZWRITEENABLE, true);
		device->SetRenderState(D3DRS_LIGHTING, false);

		sprite->Begin(D3DXSPRITE_ALPHABLEND);
		scene->Draw2D(sprite);
		sprite->End();

		device->EndScene();

		device->Present(0, 0, 0, 0);
	}
}