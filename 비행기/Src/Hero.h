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
//  주인공 구조체.
//
struct HERO
{

	int  Hp;							// 체력.
	int  Lv;							// 레벨.
	int  Exp;							// 경험치.
	char Name[256];

	D3DXVECTOR3 vDir;					// 방향벡터.★		
	D3DXVECTOR3 vRot;					// 방향벡터 저장소.★
	float		fVelo;					// 속도.★

	D3DXVECTOR3 vPos;					// 월드(멥) 좌표.
	D3DXVECTOR3 vOrgPos;				// 리셋용. 원본좌표.

	D3DXVECTOR3 vCenterL;				//충돌검사용 중심 좌표.(Local)★
	D3DXVECTOR3 vCenterW;				//충돌검사용 중심 좌표.(World)★
	float		fRadius;				//충돌구 반경.★

	D3DXMATRIX mTM, temp_mTM, R_mTM;    // 최종 월드 변환 행렬.
	D3DXMATRIX mScale, mRot, mTrans;
	D3DXMATRIX mLRot, mRRot;			// 좌회전, 우회전 행렬. 

	CHAR*	   g_TextureName;
	LPDIRECT3DTEXTURE9 pTex;

	HERO_BOT bot;
};




// 주인공 관련 전역 함수.
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