#include "stdafx.h"
#include "DataManager.h"



DataManager* DataManager::instance;
DataManager::DataManager()
{

}

void DataManager::Init(Device device)
{
	Texture tex;
	D3DXCreateTextureFromFile(device, "Tile/basictile.bmp", &tex);
	textures.insert(ST("basictile.bmp", tex));
	D3DXCreateTextureFromFile(device, "Tile/rocktile.bmp", &tex);
	textures.insert(ST("rocktile.bmp", tex));
	D3DXCreateTextureFromFile(device, "Tile/housebody.bmp", &tex);
	textures.insert(ST("housebody.bmp", tex));
	D3DXCreateTextureFromFile(device, "Tile/houseroof.bmp", &tex);
	textures.insert(ST("houseroof.bmp", tex));
	D3DXCreateTextureFromFile(device, "mons/slime.png", &tex);
	textures.insert(ST("slime.png", tex));
	D3DXCreateTextureFromFile(device, "Zealot/Zealot_Diffuse.bmp", &tex);
	textures.insert(ST("Zealot_Diffuse.bmp", tex));
	D3DXCreateTextureFromFile(device, "mons/Damaged.png", &tex);
	textures.insert(ST("Damaged", tex));
	D3DXCreateTextureFromFile(device, "mons/skeletone.bmp", &tex);
	textures.insert(ST("skeletone.bmp", tex));
	D3DXCreateTextureFromFile(device, "mons/swordbody.bmp", &tex);
	textures.insert(ST("swordbody.bmp", tex));
	D3DXCreateTextureFromFile(device, "mons/swordhandle.bmp", &tex);
	textures.insert(ST("swordhandle.bmp", tex));
	D3DXCreateTextureFromFile(device, "mons/slimeMissile.bmp", &tex);
	textures.insert(ST("slimeMissile.bmp", tex));
	D3DXCreateTextureFromFile(device, "mons/coin.bmp", &tex);
	textures.insert(ST("coin.bmp", tex));
	D3DXCreateTextureFromFile(device, "mons/coin5.bmp", &tex);
	textures.insert(ST("coin5.bmp", tex));

	D3DXCreateTextureFromFile(device, "ui/gageframe.png", &tex);
	textures.insert(ST("gageframe", tex));
	D3DXCreateTextureFromFile(device, "ui/hpgage.png", &tex);
	textures.insert(ST("hpgage", tex));
	D3DXCreateTextureFromFile(device, "ui/hppotion.png", &tex);
	textures.insert(ST("hppotion", tex));
	D3DXCreateTextureFromFile(device, "ui/manapotion.png", &tex);
	textures.insert(ST("mppotion", tex));
	D3DXCreateTextureFromFile(device, "ui/mana.png", &tex);
	textures.insert(ST("mana", tex));
	D3DXCreateTextureFromFile(device, "mons/green.png", &tex);
	textures.insert(ST("green", tex));

	D3DXCreateTextureFromFile(device, "mons/slime2.png", &tex);
	textures.insert(ST("slime2.png", tex));
	D3DXCreateTextureFromFile(device, "mons/slime3.png", &tex);
	textures.insert(ST("slime3.png", tex));

	Model* model = new NormalModel(device, "Tile/basictile.x");
	models.insert(SM("basictile", model));
	model = new NormalModel(device, "Tile/rocktile.x");
	models.insert(SM("rocktile", model));
	model = new NormalModel(device, "Tile/housetile.x");
	models.insert(SM("housetile", model));
	model = new NormalModel(device, "mons/SlimeMissile.x");
	models.insert(SM("slimemissile", model));
	model = new NormalModel(device, "mons/coin.x");
	models.insert(SM("coin", model));

	KindData* kind = new KindData(device, "mons/movingslime.x", "mons/attackingslime.x", 5, 1, 0);
	kinds.insert(SK("slime", kind));
	kind = new KindData(device, "mons/movingslime3.x", "mons/attackingslime3.x", 10, 3, 1);
	kinds.insert(SK("bigslime", kind));
	kind = new KindData(device, "mons/movingskeletone.x", "mons/attackingskeletone.x", 10, 3, 1);
	kinds.insert(SK("skeletone", kind));
	kind = new KindData(device, "mons/movingslime2.x", "mons/attackingslime2.x", 50, 2, 2);
	kinds.insert(SK("player", kind));

	SkinnedModelQueue* queue = new SkinnedModelQueue(device, "mons/movingslime.x", 30);
	queues.insert(SQ("mons/movingslime.x", queue)); 
	queue = new SkinnedModelQueue(device, "mons/attackingslime.x", 30);
	queues.insert(SQ("mons/attackingslime.x", queue));

	queue = new SkinnedModelQueue(device, "mons/attackingslime2.x", 30);
	queues.insert(SQ("mons/attackingslime2.x", queue));
	queue = new SkinnedModelQueue(device, "mons/movingslime2.x", 30);
	queues.insert(SQ("mons/movingslime2.x", queue));

	queue = new SkinnedModelQueue(device, "mons/attackingslime3.x", 30);
	queues.insert(SQ("mons/attackingslime3.x", queue));
	queue = new SkinnedModelQueue(device, "mons/movingslime3.x", 30);
	queues.insert(SQ("mons/movingslime3.x", queue));
}

DataManager::~DataManager()
{

}

SkinnedModel* DataManager::GetQueueModel(String Name)
{
	return queues[Name]->DeQueue();
}

Model* DataManager::getModel(String Name)
{
	return models[Name];
}
Texture DataManager::getTexture(String Name)
{
	return textures[Name];
}
KindData* DataManager::getKindData(String Name)
{
	return kinds[Name];
}