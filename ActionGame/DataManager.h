#pragma once
#include "Model.h"
#include "SkinnedModelQueue.h"
#define SM(x,y) std::pair<String, Model*>(x,y)
#define ST(x,y) std::pair<String, Texture>(x,y)
#define SK(x,y) std::pair<String, KindData*>(x,y)
#define SQ(x,y) std::pair<String, SkinnedModelQueue*>(x,y)

struct KindData;
class DataManager
{
private:
	Map<String, Model*> models;
	Map<String, Texture> textures;
	static DataManager* instance;
	Map<String, KindData*> kinds;
	Map<String, SkinnedModelQueue*> queues;
public:
	DataManager();
	~DataManager();
	Model* getModel(String Name);
	Texture getTexture(String Name);
	KindData* getKindData(String Name);
	SkinnedModel* GetQueueModel(String Name);
	void Init(Device device);
public:
	static void InitInstance(Device device) { instance = new DataManager(); instance->Init(device); }
	static DataManager* GetInstance() { return instance; }
};
class KindData
{
public:
	Device device;
	String modelNormal;
	String modelAttack;
	int hp;
	int damage;
	int defDmg;
	int speed;
	KindData(Device device, String normal, String attack, int hp, int damage, 
		int defDmg, int speed = 2)
	{
		this->device = device;
		this->modelNormal = normal;
		this->modelAttack = attack;
		this->hp = hp;
		this->damage = damage;
		this->defDmg = defDmg;
		this->speed = speed;
	}
	SkinnedModel* makeModel(String s)
	{
		return DataManager::GetInstance()->GetQueueModel(s);
	}
};