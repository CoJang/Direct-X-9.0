#pragma once

#include "d3d9.h"
#include "d3dx9.h"
#include "dxerr.h"  

#include "windows.h"
#include "mmsystem.h"
#include "Device.h"
 
#ifndef LPTEXTURE
typedef LPDIRECT3DTEXTURE9	LPTEXTURE;
#endif

#ifndef LPDIVICE
typedef LPDIRECT3DDEVICE9	LPDEVICE;
#endif

#ifndef NO_   
#define YES_  1
#define NO_   0
#define NOMSGBOX_  NO_
#endif


//에러 출력.
int B3Error(BOOL bMsgBox, char* msg, ...);


//////////////////////////////////////////////////////////////////////////////
//
// 메쉬 파일 로드/랜더링 클래스.
// 
class B3Mesh  
{
public:
	LPD3DXMESH		m_pMesh;			//메쉬 인터페이스 포인터.
	//ID3DXMesh*	m_pMesh;			//메쉬 인터페이스 포인터.(상동)
 	D3DMATERIAL9*	m_pMtrls;			//재질 포인터들.
	DWORD			m_MtrlCnt;			//재질 개수.

	LPTEXTURE*		m_ppTextures;		//텍스쳐 이중 포인터들.

	LPDEVICE		m_pDev; 

	B3Mesh();
	~B3Mesh();

	BOOL Load(LPDEVICE pDev, LPCTSTR filename);
	void Release();

    char		g_pMeshName[MAX_PATH];
    CHAR*		g_pMeshPath;
	//B3Mesh(LPDEVICE pDev, LPCTSTR filename);

    D3DXMATRIX      mTM, mPROP;   // 저장용 행렬.
    D3DXMATRIX      mScale, mRot, mRRot, mTrans;

    D3DXVECTOR3     vPos, vRot, vDir;

    FLOAT           speed;
    FLOAT           Radius, Degree; // 비행기 회전반경 및 수평각도
	D3DMATERIAL9	Material;
};

bool	LoadInitData(char* pPath, char* pMeshName);

INT     PlaneInit(D3DXVECTOR3 vpos);
void    PlaneUpdate(float dTime);
BOOL    PlaneDraw(float dTime);

INT		DwarfInit(D3DXVECTOR3 vpos);
void	DwarfUpdate(float dTime);
BOOL	DwarfDraw(float dTime);


extern B3Mesh* Plane;
extern B3Mesh* Dwarf;
 
/****************** end of file "B3Mesh.h" *******************************/