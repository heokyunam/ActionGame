#pragma once
#include "Allocator.h"
class Model
{
public:
	Model() {}
	~Model() {}
	virtual void Draw(Device device, Texture tex = 0) {}
	virtual void Load(Device device, char* filename) {}
	virtual void Update(float speed) {}
};

class SkinnedModel : public Model
{
private:
	Bone* root;
	Animation ani;
public:
	SkinnedModel(Device device = 0, char* filename = 0);
	~SkinnedModel();
	void Draw(Device device, Texture tex = 0);
	void Load(Device device, char* filename);
	void Update(float speed = 0.01f);

	void LoadBone(Frame* bone);
	void UpdateBone(Frame* bone);
	void SetIndex(int index);
};

class NormalModel : public Model
{
private:
	Mesh mesh;
	SVector<Material> materials;
	SVector<Texture> textures;
public:
	NormalModel(Device device, char* filename);
	~NormalModel();
	void Draw(Device device, Texture tex = 0);
	void Load(Device device, char* filename);
	Mesh getMesh() { return mesh; }
};