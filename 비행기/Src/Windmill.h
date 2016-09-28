//
// Windmill.h
//
//
// 2007.01.25. Kihong Kim / mad_dog@hanmail.net
// 
#pragma once
 

// ǳ���� ����.
struct WINDMILL_WING
{
	D3DXVECTOR3 vPos;		// ������ '��ü' �κ����� '��� ��ǥ'

	D3DXVECTOR3 vCenterL;		//�浹�˻�� �߽� ��ǥ.(Local)��
	D3DXVECTOR3 vCenterW;		//�浹�˻�� �߽� ��ǥ.(World)��
	float		fRadius;		//�浹�� �ݰ�.��
	BOOL		IsHeroFire;

	D3DXVECTOR3 vNormal;

	D3DXMATRIX mTM;
	D3DXMATRIX mScale, mRot, mTrans;
	D3DXMATRIX Sinverse, Rinverse;

	CHAR*	   g_TextureName[2];
	LPDIRECT3DTEXTURE9 pTex[2];

    HRESULT InitIB();                    // �ε��� ���� ����
    LPDIRECT3DINDEXBUFFER9 INDEX_BUFFER; //�ε��� ����
};

// ǳ���� �ٴ�(����).
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

    HRESULT InitIB();                    // �ε��� ���� ����
    LPDIRECT3DINDEXBUFFER9 INDEX_BUFFER; //�ε��� ����
};


//
//  ǳ�� ����ü.
//
struct WINDMILL
{ 	
	WINDMILL_WING Wing[3];		//ǳ�� ����.
	WINDMILL_BOT Bottom;		// ǳ�� �ٴ� (����)

	D3DXVECTOR3 vPos;			// ����(��) ��ǥ.(�̵�)
	D3DXVECTOR3 vRot;			// ���� ȸ��.
	
	D3DXVECTOR3 vNormal;

	D3DXMATRIX mTM;				// ���� ���� ��ȯ ���.
	D3DXMATRIX mScale, mRot, mTrans;
	D3DXMATRIX Sinverse, Rinverse;

	BOOL bShowInnerLight;		// �ǳ��� ���� Ű�� ��

    HRESULT InitIB();                    // �ε��� ���� ����
    LPDIRECT3DINDEXBUFFER9 INDEX_BUFFER; // �ε��� ����
};

// ǳ�� ���� ���� �Լ�.
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