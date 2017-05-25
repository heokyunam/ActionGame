#pragma once
#define MESHDATAMESH pMeshData->pMesh 

struct BoneMesh : public D3DXMESHCONTAINER
{
	SVector<Material> materials;
	SVector<Texture> textures;

	Mesh origin;
	Matrix* pMatCurrent;
	Matrix* pMatOffset;
	Matrix** ppMat;
};

struct Bone : public D3DXFRAME
{
	Matrix matWorld;
	void Draw(Device device, Texture tex = 0);
	void Update(Matrix* parent);
};


class Allocator : public ID3DXAllocateHierarchy
{
	SYNTHESIZE(Device, device, Device);
	SYNTHESIZE(String, folder, Folder);
public:
	Allocator();
	~Allocator();
	STDMETHOD(CreateFrame)(THIS_ LPCSTR Name,
		LPD3DXFRAME *ppNewFrame);

	STDMETHOD(CreateMeshContainer)(THIS_
		LPCSTR Name,
		CONST D3DXMESHDATA *pMeshData,
		CONST D3DXMATERIAL *pMaterials,
		CONST D3DXEFFECTINSTANCE *pEffectInstances,
		DWORD NumMaterials,
		CONST DWORD *pAdjacency,
		LPD3DXSKININFO pSkinInfo,
		LPD3DXMESHCONTAINER *ppNewMeshContainer);

	
	STDMETHOD(DestroyFrame)(THIS_ LPD3DXFRAME pFrameToFree);

	
	STDMETHOD(DestroyMeshContainer)(THIS_ LPD3DXMESHCONTAINER pMeshContainerToFree);
};

