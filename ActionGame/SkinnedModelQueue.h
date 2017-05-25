#pragma once
#include "Model.h"
class SkinnedModelQueue
{
private:
	SVector<SkinnedModel*> models;
	int index;
public:
	SkinnedModelQueue(Device device, char* xfile, int length);
	~SkinnedModelQueue();
	void Load(Device device, char* xfile, int length);
	SkinnedModel* DeQueue();
};

