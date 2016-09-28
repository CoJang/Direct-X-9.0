//
// Map.h
//
//
// 2007.01.25. Kihong Kim / mad_dog@hanmail.net
//
#pragma warning(disable:4996)
#pragma once

 

//
//  �� / ���� ����ü.
//
struct MAP
{ 	  
 	char Name[256];

	D3DXVECTOR2 vSize;			//����, ���� ������ (����) 
	D3DXVECTOR3 vPos;			// ���� ��ǥ.

	D3DXMATRIX mTM;				// ���� ���� ��ȯ ���.
	D3DXMATRIX mScale, mRot, mTrans;

	CHAR* g_TextureName[2];
	LPDIRECT3DTEXTURE9 pTex[2];
};



// �� ���� ���� �Լ�.
//
INT MapInit(char* name, D3DXVECTOR3 vPos, D3DXVECTOR2 vSize);
void MapUpdate(float dTime);
void MapDraw(float dTime);
void MapRelease();
void DrawBackGround(float dTime);

extern MAP* g_pMap;


/****************** end of file "Map.h" ************************/