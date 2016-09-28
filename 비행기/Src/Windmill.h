//
// Windmill.h
//
//
// 2007.01.25. Kihong Kim / mad_dog@hanmail.net
// 
#pragma once
 

// 풍차의 날개.
struct WINDMILL_WING
{
	D3DXVECTOR3 vPos;		// 날개의 '몸체' 로부터의 '상대 좌표'

	D3DXVECTOR3 vCenterL;		//충돌검사용 중심 좌표.(Local)★
	D3DXVECTOR3 vCenterW;		//충돌검사용 중심 좌표.(World)★
	float		fRadius;		//충돌구 반경.★
	BOOL		IsHeroFire;

	D3DXVECTOR3 vNormal;

	D3DXMATRIX mTM;
	D3DXMATRIX mScale, mRot, mTrans;
	D3DXMATRIX Sinverse, Rinverse;

	CHAR*	   g_TextureName[2];
	LPDIRECT3DTEXTURE9 pTex[2];

    HRESULT InitIB();                    // 인덱스 버퍼 정의
    LPDIRECT3DINDEXBUFFER9 INDEX_BUFFER; //인덱스 버퍼
};

// 풍차의 바닥(빛샘).
struct WINDMILL_BOT
{
	D3DXVECTOR3 vPos;
	D3DXVECTOR3 vRot;

	D3DXVECTOR3 vNormal;

	D3DXMATRIX mTM;
	D3DXMATRIX mScale, mRot, mTrans;

	D3DMATERIAL9 WMBOT_MTL;

	CHAR*	   g_TextureName;
	LPDIRECT3DTEXTURE9 pTex;

    HRESULT InitIB();                    // 인덱스 버퍼 정의
    LPDIRECT3DINDEXBUFFER9 INDEX_BUFFER; //인덱스 버퍼
};


//
//  풍차 구조체.
//
struct WINDMILL
{ 	
	WINDMILL_WING Wing[3];		//풍차 날개.
	WINDMILL_BOT Bottom;		// 풍차 바닥 (빛샘)

	D3DXVECTOR3 vPos;			// 월드(멥) 좌표.(이동)
	D3DXVECTOR3 vRot;			// 월드 회전.
	
	D3DXVECTOR3 vNormal;

	D3DXMATRIX mTM;				// 최종 월드 변환 행렬.
	D3DXMATRIX mScale, mRot, mTrans;
	D3DXMATRIX Sinverse, Rinverse;

	BOOL bShowInnerLight;		// 실내등 끄고 키는 불

    HRESULT InitIB();                    // 인덱스 버퍼 정의
    LPDIRECT3DINDEXBUFFER9 INDEX_BUFFER; // 인덱스 버퍼
};

// 풍차 관련 전역 함수.
//

INT WindmillInit(D3DXVECTOR3 vPos);
void WindmillUpdate(float dTime);
void WindmillDraw(float dTime);
void WindmillRelease();

INT TripleWindmillInit(D3DXVECTOR3 vPos);
void TripleWindmillUpdate(float dTime);
void TripleWindmillDraw(float dTime);
void TripleWindmillRelease();

INT TripleWindmillInit2(D3DXVECTOR3 vPos);
void TripleWindmillUpdate2(float dTime);
void TripleWindmillDraw2(float dTime);
void TripleWindmillRelease2();

void WingBSphereDraw(float dTime);
void WindMillBottomDraw(float dTime);
void WindMillBottomDraw1(float dTime);
void WindMillBottomDraw2(float dTime);

enum : unsigned char
{
	hf_NONE,
	hf_RELOAD,
	hf_FIRE
}
static heroFireState;

extern WINDMILL* g_pWindmill;
extern WINDMILL* g_pTripleWindmill;
extern WINDMILL* g_pTripleWindmill2;

extern WINDMILL_WING* g_pWindMillWing;
/****************** end of file "Windmill.h" ************************/