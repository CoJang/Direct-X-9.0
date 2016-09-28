#pragma warning(disable:4996)
#pragma once
 
struct BOX
{
	D3DXVECTOR3			vDir;					// 방향벡터.★		
	D3DXVECTOR3			vPos;					// 월드(멥) 좌표.

	D3DXMATRIX			mTM, temp_mTM, R_mTM;    // 최종 월드 변환 행렬.
	D3DXMATRIX			mScale, mRot, mTrans;

	CHAR*				g_TextureName;
	LPDIRECT3DTEXTURE9  pTex;
	D3DMATERIAL9		Material;
};


INT BoxInit(D3DXVECTOR3 vPos);
void BoxUpdate(float dTime);
void BoxDraw(float dTime);
void BoxRelease();


extern BOX* g_pBox;

/****************** end of file "Hero.h" ************************/