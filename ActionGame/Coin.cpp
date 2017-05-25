#include "stdafx.h"
#include "Coin.h"
#include "DataManager.h"

Coin::Coin(int price, int x, int y) : Movable(0, x, y)
{
	this->price = price;
	model = DataManager::GetInstance()->getModel("coin");
}


Coin::~Coin()
{
}

void Coin::Draw(Device device)
{
	device->SetTransform(D3DTS_WORLD, &matWorld);

	if (price == 1)
		model->Draw(device);
	else
		model->Draw(device, DataManager::GetInstance()->getTexture("coin5.bmp"));
}