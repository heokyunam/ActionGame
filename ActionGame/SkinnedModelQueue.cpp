#include "stdafx.h"
#include "SkinnedModelQueue.h"


SkinnedModelQueue::SkinnedModelQueue(Device device, char* xfile, int length)
{
	Load(device, xfile, length);
	index = 0;
}


SkinnedModelQueue::~SkinnedModelQueue()
{
}

void SkinnedModelQueue::Load(Device device, char* xfile, int length)
{
	for (int i = 0; i < length; i++){
		SkinnedModel* sm = new SkinnedModel();
		sm->Load(device, xfile);
		models.push_back(sm);
	}
}
SkinnedModel* SkinnedModelQueue::DeQueue()
{
	SkinnedModel* model = models[index];
	index++;
	if (index >= models.size()) index = 0;
	return model;
}