#include "stdafx.h"
#include "Allocator.h"
#include "DataManager.h"


void Bone::Draw(Device device, Texture tex)
{
	BoneMesh* bm = (BoneMesh*) this->pMeshContainer;
	if (bm)
	{
		for (int i = 0; i < bm->NumMaterials; i++)
		{
			device->SetMaterial(&bm->materials[i]);
			if (tex)
				device->SetTexture(0, tex);
			else
				device->SetTexture(0, bm->textures[i]);
			bm->MeshData.pMesh->DrawSubset(i);
		}
	}
	if (this->pFrameFirstChild)
		CONVERT(Bone*, this->pFrameFirstChild)->Draw(device, tex);
	if (this->pFrameSibling)
		CONVERT(Bone*, this->pFrameSibling)->Draw(device, tex);

}

void Bone::Update(Matrix* parent)
{
	this->matWorld = this->TransformationMatrix;

	if (parent)
		this->matWorld *= *parent;
	if (this->pFrameFirstChild)
		CONVERT(Bone*, pFrameFirstChild)->Update(&matWorld);
	if (this->pFrameSibling)
		CONVERT(Bone*, pFrameSibling)->Update(parent);

}

Allocator::Allocator()
{
}


Allocator::~Allocator()
{
}

STDMETHODIMP Allocator::CreateFrame(THIS_ LPCSTR Name,
	LPD3DXFRAME *ppNewFrame)
{
	Bone* bone = new Bone();
	ZeroMemory(bone, sizeof(Bone));

	if (Name)
	{
		int length = strlen(Name) + 1;
		bone->Name = new char[length];
		memcpy(bone->Name, Name, length);
	}

	D3DXMatrixIdentity(&bone->matWorld);

	*ppNewFrame = bone;

	return S_OK;
}

STDMETHODIMP Allocator::CreateMeshContainer(THIS_
	LPCSTR Name,
	CONST D3DXMESHDATA *pMeshData,
	CONST D3DXMATERIAL *pMaterials,
	CONST D3DXEFFECTINSTANCE *pEffectInstances,
	DWORD NumMaterials,
	CONST DWORD *pAdjacency,
	LPD3DXSKININFO pSkinInfo,
	LPD3DXMESHCONTAINER *ppNewMeshContainer)
{
	BoneMesh* bm = new BoneMesh();
	ZeroMemory(bm, sizeof(BoneMesh));

	assert(pMeshData->Type == D3DXMESHTYPE_MESH);
	bm->MeshData.Type = pMeshData->Type;
	MESHDATAMESH->AddRef();
	bm->MeshData.pMesh = MESHDATAMESH;
	bm->NumMaterials = NumMaterials;

	DataManager* r = DataManager::GetInstance();
	for (int i = 0; i < NumMaterials; i++)
	{
		bm->materials.push_back(pMaterials[i].MatD3D);
		Texture tex = r->getTexture(pMaterials[i].pTextureFilename);
		bm->textures.push_back(tex);
	}

	if (pAdjacency)
	{
		int length = MESHDATAMESH->GetNumVertices();
		bm->pAdjacency = new DWORD[length];
		memcpy(bm->pAdjacency, pAdjacency, length * sizeof(DWORD));
	}

	if (pSkinInfo)
	{
		pSkinInfo->AddRef();
		bm->pSkinInfo = pSkinInfo;
	}

	MESHDATAMESH->CloneMeshFVF(D3DXMESH_MANAGED,
		MESHDATAMESH->GetFVF(),
		device, &bm->origin);

	if (pSkinInfo)
	{
		int length = pSkinInfo->GetNumBones();
		bm->pMatCurrent = new Matrix[length];
		bm->pMatOffset = new Matrix[length];
		bm->ppMat = new Matrix*[length];

		for (int i = 0; i < length; i++)
			bm->pMatOffset[i] = *pSkinInfo->GetBoneOffsetMatrix(i);
	}

	*ppNewMeshContainer = bm;

	return S_OK;
}


STDMETHODIMP Allocator::DestroyFrame(THIS_ LPD3DXFRAME pFrame)
{
	Bone* bone = (Bone*)pFrame;
	SAFE_DELETE_ARRAY(bone->Name);
	return S_OK;
}


STDMETHODIMP Allocator::DestroyMeshContainer(THIS_ LPD3DXMESHCONTAINER pContainer)
{
	BoneMesh* bm = (BoneMesh*)pContainer;
	SAFE_RELEASE(bm->MeshData.pMesh);

	SAFE_DELETE_ARRAY(bm->pAdjacency);
	SAFE_RELEASE(bm->origin);

	SAFE_DELETE_ARRAY(bm->pMatCurrent);
	SAFE_DELETE_ARRAY(bm->pMatOffset);
	SAFE_DELETE_ARRAY(bm->ppMat);

	return S_OK;
}