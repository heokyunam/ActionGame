#include "stdafx.h"
#include "Model.h"
#include "DataManager.h"

SkinnedModel::SkinnedModel(Device device, char* filename)
{
	if (filename && device) Load(device, filename);
}

SkinnedModel::~SkinnedModel()
{
	Allocator ac;
	D3DXFrameDestroy(root, &ac);

	SAFE_RELEASE(ani);
}

void SkinnedModel::Draw(Device device, Texture tex)
{
	if (root)
		root->Draw(device, tex);
}

void SkinnedModel::Load(Device device, char* filename)
{
	Allocator ac;
	ac.SetDevice(device);
	D3DXLoadMeshHierarchyFromXA(filename, D3DXMESH_MANAGED, device, &ac, 0, (Frame**)&root, &ani);

	LoadBone(root);
}

void SkinnedModel::Update(float speed)
{
	ani->AdvanceTime(speed, 0);
	if (root)
		root->Update(0);
	UpdateBone(root);
}

void SkinnedModel::LoadBone(Frame* bone)
{
	BoneMesh* bm = (BoneMesh*)bone->pMeshContainer;
	if (bm)
	{
		SkinInfo info = bm->pSkinInfo;
		if (info)
		{
			int length = info->GetNumBones();
			for (int i = 0; i < length; i++)
			{
				LPCSTR Name = info->GetBoneName(i);
				Bone* find = (Bone*)D3DXFrameFind(root, Name);
				bm->ppMat[i] = &find->matWorld;
			}
		}		
	}
	if (bone->pFrameFirstChild)
		LoadBone(bone->pFrameFirstChild);
	if (bone->pFrameSibling)
		LoadBone(bone->pFrameSibling);

}

void SkinnedModel::UpdateBone(Frame* frame)
{
	BoneMesh* bm = (BoneMesh*)frame->pMeshContainer;
	if (bm)
	{
		SkinInfo info = bm->pSkinInfo;
		if (info)
		{
			int length = info->GetNumBones();
			for (int i = 0; i < length; i++)
			{
				bm->pMatCurrent[i] = bm->pMatOffset[i] * (*bm->ppMat[i]);
			}
			BYTE* src = 0, *dest = 0;
			bm->origin->LockVertexBuffer(D3DLOCK_READONLY, (void**)&src);
			bm->MeshData.pMesh->LockVertexBuffer(0, (void**)&dest);

			info->UpdateSkinnedMesh(bm->pMatCurrent, 0, src, dest);

			bm->origin->UnlockVertexBuffer();
			bm->MeshData.pMesh->UnlockVertexBuffer();
		}
	}

	if (frame->pFrameFirstChild)
		UpdateBone(frame->pFrameFirstChild);
	if (frame->pFrameSibling)
		UpdateBone(frame->pFrameSibling);
}

void SkinnedModel::SetIndex(int index)
{
	if (ani)
	{
		AniSet set;
		ani->GetAnimationSet(index, &set);
		ani->SetTrackAnimationSet(0, set);
		SAFE_RELEASE(set);
	}
}

NormalModel::NormalModel(Device device, char* filename)
{
	if (device && filename) Load(device, filename);
}

NormalModel::~NormalModel()
{
	SAFE_RELEASE(mesh);
}

void NormalModel::Draw(Device device, Texture tex)
{
	for (int i = 0; i < materials.size(); i++)
	{
		if (tex)
			device->SetTexture(0, tex);
		else
			device->SetTexture(0, textures[i]);

		device->SetMaterial(&materials[i]);

		mesh->DrawSubset(i);
	}
}

void NormalModel::Load(Device device, char* filename)
{
	LPD3DXBUFFER mtlBuffer;
	DWORD length;
	D3DXLoadMeshFromXA(filename, D3DXMESH_SYSTEMMEM, 
		device, 0, &mtlBuffer, 0, &length, &mesh);
	D3DXMATERIAL* mat = (D3DXMATERIAL*)mtlBuffer->GetBufferPointer();

	DataManager* dm = DataManager::GetInstance();

	for (int i = 0; i < length; i++)
	{
		materials.push_back(mat[i].MatD3D);
		textures.push_back(dm->getTexture(mat[i].pTextureFilename));
	}
}