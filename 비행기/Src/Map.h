//
// Map.h
//
//
// 2007.01.25. Kihong Kim / mad_dog@hanmail.net
//
#pragma warning(disable:4996)
#pragma once

 

//
//  멥 / 지형 구조체.
//
struct MAP
{ 	  
 	char Name[256];

	D3DXVECTOR2 vSize;			//가로, 세로 사이즈 (미터) 
	D3DXVECTOR3 vPos;			// 월드 좌표.

	D3DXMATRIX mTM;				// 최종 월드 변환 행렬.
	D3DXMATRIX mScale, mRot, mTrans;

	CHAR* g_TextureName[2];
	LPDIRECT3DTEXTURE9 pTex[2];
};



// 멥 관련 전역 함수.
//
INT MapInit(char* name, D3DXVECTOR3 vPos, D3DXVECTOR2 vSize);
void MapUpdate(float dTime);
void MapDraw(float dTime);
void MapRelease();
void DrawBackGround(float dTime);

extern MAP* g_pMap;


/****************** end of file "Map.h" ************************/