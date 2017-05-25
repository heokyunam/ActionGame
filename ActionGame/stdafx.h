// stdafx.h : ���� ��������� ���� ��������� �ʴ�
// ǥ�� �ý��� ���� ���� �� ������Ʈ ���� ���� ������
// ��� �ִ� ���� �����Դϴ�.
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // ���� ������ �ʴ� ������ Windows ������� �����մϴ�.
// Windows ��� ����:
#include <windows.h>

// C ��Ÿ�� ��� �����Դϴ�.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>


// TODO: ���α׷��� �ʿ��� �߰� ����� ���⿡�� �����մϴ�.
#include <d3d9.h>
#include <d3dx9.h>
#include <assert.h>
#include <vector>
#include <map>

typedef LPDIRECT3DDEVICE9 Device;
typedef D3DXVECTOR3 Vector3;
typedef D3DXVECTOR2 Vector2;
typedef D3DXMATRIX Matrix;
typedef LPD3DXMESH Mesh;
typedef LPD3DXSKININFO SkinInfo;
typedef LPD3DXSPRITE Sprite;
typedef D3DMATERIAL9 Material;
typedef LPDIRECT3DTEXTURE9 Texture;
typedef D3DXFRAME Frame;
typedef LPD3DXANIMATIONCONTROLLER Animation;
typedef LPD3DXANIMATIONSET AniSet;
typedef D3DXQUATERNION Quaternion;
typedef std::string String;

#define WINDOWWIDTH 800
#define WINDOWHEIGHT 600
#define SVector std::vector
#define Map std::map

#define SYNTHESIZE(type, name, func)\
	protected:type name;\
	public:void Set##func(type name) { this->name = name;  }\
	type Get##func() { return name;  }

#define SAFE_RELEASE(p) {if(p) p->Release(); p = 0; }
#define SAFE_DELETE(p) {if(p) delete p; p = 0; }
#define SAFE_DELETE_ARRAY(p) {if(p) delete[] p; p = 0; }
#define NUMVEC(n) &Vector3(n,n,n)
#define CONVERT(x, a) ((x)a)

#define SVectorDraw(name)\
	for (int i = 0; i < name.size(); i++)\
		name[i]->Draw(device);

#define SVectorUpdate(vectype, type, name)\
for (vectype::iterator i = name.begin(); i != name.end();)\
{	if ((*i)->Update()){ i++; }\
	else { type t = (*i); i = name.erase(i); delete t; }}