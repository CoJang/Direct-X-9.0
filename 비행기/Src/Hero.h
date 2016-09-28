//
// Hero.h
//
//
// 2007.01.25. Kihong Kim / mad_dog@hanmail.net
//
#pragma warning(disable:4996)
#pragma once
 


struct HERO_BOT
{
	D3DXVECTOR3 vPos;
	D3DXVECTOR3 vRot;

	D3DXVECTOR3 vNormal;

	D3DXMATRIX mTM;
	D3DXMATRIX mScale, mRot, mTrans;

	D3DMATERIAL9 WMBOT_MTL;

	CHAR*	   g_TextureName;
	LPDIRECT3DTEXTURE9 pTex;
};
//
//  ���ΰ� ����ü.
//
struct HERO
{

	int  Hp;							// ü��.
	int  Lv;							// ����.
	int  Exp;							// ����ġ.
	char Name[256];

	D3DXVECTOR3 vDir;					// ���⺤��.��		
	D3DXVECTOR3 vRot;					// ���⺤�� �����.��
	float		fVelo;					// �ӵ�.��

	D3DXVECTOR3 vPos;					// ����(��) ��ǥ.
	D3DXVECTOR3 vOrgPos;				// ���¿�. ������ǥ.

	D3DXVECTOR3 vCenterL;				//�浹�˻�� �߽� ��ǥ.(Local)��
	D3DXVECTOR3 vCenterW;				//�浹�˻�� �߽� ��ǥ.(World)��
	float		fRadius;				//�浹�� �ݰ�.��

	D3DXMATRIX mTM, temp_mTM, R_mTM;    // ���� ���� ��ȯ ���.
	D3DXMATRIX mScale, mRot, mTrans;
	D3DXMATRIX mLRot, mRRot;			// ��ȸ��, ��ȸ�� ���. 

	CHAR*	   g_TextureName;
	LPDIRECT3DTEXTURE9 pTex;

	HERO_BOT bot;
};




// ���ΰ� ���� ���� �Լ�.
//
INT HeroInit(char* name, D3DXVECTOR3 vPos);
void HeroMove(float dTime);
void HeroDraw(float dTime);
void HeroRelease();
void HeroBSphereDraw(float dTime);

void HeroBottomDraw(float dTime);
static BOOL isHeroSelect;


extern HERO* g_pHero;

/****************** end of file "Hero.h" ************************/