#pragma warning(disable:4996)
#pragma once
 
struct BOX
{
	D3DXVECTOR3			vDir;					// ���⺤��.��		
	D3DXVECTOR3			vPos;					// ����(��) ��ǥ.

	D3DXMATRIX			mTM, temp_mTM, R_mTM;    // ���� ���� ��ȯ ���.
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