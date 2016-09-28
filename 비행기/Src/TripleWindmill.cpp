//
// Windmill.cpp
//
//
// 2007.01.25. Kihong Kim / mad_dog@hanmail.net
//

#include "windows.h"
#include "assert.h"
#include "Device.h"
#include "Render.h"

#include "Vertex.h"
#include "Normal.h"

#include "Map.h"
#include "Windmill.h"
#include "Hero.h"
#include "Season.h"



////////////////////////////////////////////////////////////////////////////
//
WINDMILL* g_pTripleWindmill = NULL;
D3DMATERIAL9 g_TriWindMTL;
D3DMATERIAL9 g_TriWindWingMTL;

// ǳ�� ��ü : �Ƕ�̵� ����.
VERTEX g_MeshTriWindmill_Body[] = {
	// 4������ ��ü..
	{ D3DXVECTOR3(0, 3, 0), D3DXVECTOR3(0, 0, -1), D3DXVECTOR2(0.242f, 0.0f) },
	{ D3DXVECTOR3(1, 0, -1), D3DXVECTOR3(0, 0, -1), D3DXVECTOR2(0.498f, 1.0f) },
	{ D3DXVECTOR3(-1, 0, -1), D3DXVECTOR3(0, 0, -1), D3DXVECTOR2(0.0f, 1.0f) },

	{ D3DXVECTOR3(-1, 0, 1), D3DXVECTOR3(0, 0, 1), D3DXVECTOR2(0.0f, 1.0f) },
	{ D3DXVECTOR3(1, 0, 1), D3DXVECTOR3(0, 0, 1), D3DXVECTOR2(0.498f, 1.0f) },
	{ D3DXVECTOR3(0, 3, 0), D3DXVECTOR3(0, 0, 1), D3DXVECTOR2(0.242f, 0.0f) },

	{ D3DXVECTOR3(-1, 0, -1), D3DXVECTOR3(-1, 0, 0), D3DXVECTOR2(0.498f, 1.0f) },
	{ D3DXVECTOR3(-1, 0, 1), D3DXVECTOR3(-1, 0, 0), D3DXVECTOR2(0.0f, 1.0f) },
	{ D3DXVECTOR3(0, 3, 0), D3DXVECTOR3(-1, 0, 0), D3DXVECTOR2(0.242f, 0.0f) },

    { D3DXVECTOR3(0, 3, 0), D3DXVECTOR3(1, 0, 0), D3DXVECTOR2(0.242f, 0.0f) },
    { D3DXVECTOR3(1, 0, 1), D3DXVECTOR3(1, 0, 0), D3DXVECTOR2(0.0f, 1.0f) },
    { D3DXVECTOR3(1, 0, -1), D3DXVECTOR3(1, 0, 0), D3DXVECTOR2(0.498f, 1.0f) },

	//'�ظ�' �� �ʿ� ����..
};



//ǳ�� ����.
VERTEX g_MeshTriWindmill_Wing[] = {
	{ D3DXVECTOR3(-2, -0.5, 0), D3DXVECTOR3(0, 0, -1), D3DXVECTOR2(0.710f, 0.978f), D3DXVECTOR2(0.669f, 1) }, //1
	{ D3DXVECTOR3(-2, 0.3, 0), D3DXVECTOR3(0, 0, -1), D3DXVECTOR2(0.574f, 0.978f), D3DXVECTOR2(0.853f, 1) },  //2
	{ D3DXVECTOR3(0, -0.5, 0), D3DXVECTOR3(0, 0, -1), D3DXVECTOR2(0.710f, 0.472f), D3DXVECTOR2(0.853f, 0.546f) },  //3

	{ D3DXVECTOR3(0, -0.5, 0), D3DXVECTOR3(0, 0, -1), D3DXVECTOR2(0.710f, 0.472f), D3DXVECTOR2(0.853f, 0.546f) },  //4
	{ D3DXVECTOR3(0, 0.3, 0), D3DXVECTOR3(0, 0, -1), D3DXVECTOR2(0.574f, 0.472f), D3DXVECTOR2(0.676f, 0.546f) },   //5
	{ D3DXVECTOR3(-2, 0.3, 0), D3DXVECTOR3(0, 0, -1), D3DXVECTOR2(0.574f, 0.978f), D3DXVECTOR2(0.669f, 1) },  //6

	{ D3DXVECTOR3(2, -0.3, 0), D3DXVECTOR3(0, 0, -1), D3DXVECTOR2(0.574f, 0.978f), D3DXVECTOR2(0.669f, 1) },
	{ D3DXVECTOR3(2, 0.5, 0), D3DXVECTOR3(0, 0, -1), D3DXVECTOR2(0.710f, 0.978f), D3DXVECTOR2(0.669f, 1) },
	{ D3DXVECTOR3(0, -0.3, 0), D3DXVECTOR3(0, 0, -1), D3DXVECTOR2(0.574f, 0.472f), D3DXVECTOR2(0.676f, 0.546f) },

	{ D3DXVECTOR3(0, -0.3, 0), D3DXVECTOR3(0, 0, -1), D3DXVECTOR2(0.574f, 0.472f), D3DXVECTOR2(0.676f, 0.546f) },
	{ D3DXVECTOR3(0, 0.5, 0), D3DXVECTOR3(0, 0, -1), D3DXVECTOR2(0.710f, 0.472f), D3DXVECTOR2(0.853f, 0.546f) },
	{ D3DXVECTOR3(2, 0.5, 0), D3DXVECTOR3(0, 0, -1), D3DXVECTOR2(0.710f, 0.978f), D3DXVECTOR2(0.669f, 1) },

	{ D3DXVECTOR3(-0.3, -2, 0), D3DXVECTOR3(0, 0, -1), D3DXVECTOR2(0.574f, 0.978f), D3DXVECTOR2(0.669f, 1) },
	{ D3DXVECTOR3(0.5, -2, 0), D3DXVECTOR3(0, 0, -1), D3DXVECTOR2(0.710f, 0.978f), D3DXVECTOR2(0.669f, 1) },
	{ D3DXVECTOR3(-0.3, 0, 0), D3DXVECTOR3(0, 0, -1), D3DXVECTOR2(0.574f, 0.472f), D3DXVECTOR2(0.676f, 0.546f) },

	{ D3DXVECTOR3(-0.3, 0, 0), D3DXVECTOR3(0, 0, -1), D3DXVECTOR2(0.574f, 0.472f), D3DXVECTOR2(0.676f, 0.546f) },
	{ D3DXVECTOR3(0.5, 0, 0), D3DXVECTOR3(0, 0, -1), D3DXVECTOR2(0.710f, 0.472f), D3DXVECTOR2(0.853f, 0.546f) },
	{ D3DXVECTOR3(0.5, -2, 0), D3DXVECTOR3(0, 0, -1), D3DXVECTOR2(0.710f, 0.978f), D3DXVECTOR2(0.669f, 1) },

	{ D3DXVECTOR3(-0.5, 2, 0), D3DXVECTOR3(0, 0, -1), D3DXVECTOR2(0.710f, 0.978f), D3DXVECTOR2(0.669f, 1) },
	{ D3DXVECTOR3(0.3, 2, 0), D3DXVECTOR3(0, 0, -1), D3DXVECTOR2(0.574f, 0.978f), D3DXVECTOR2(0.669f, 1) },
	{ D3DXVECTOR3(-0.5, 0, 0), D3DXVECTOR3(0, 0, -1), D3DXVECTOR2(0.710f, 0.472f), D3DXVECTOR2(0.853f, 0.546f) },

	{ D3DXVECTOR3(-0.5, 0, 0), D3DXVECTOR3(0, 0, -1), D3DXVECTOR2(0.710f, 0.472f), D3DXVECTOR2(0.853f, 0.546f) },
	{ D3DXVECTOR3(0.3, 0, 0), D3DXVECTOR3(0, 0, -1), D3DXVECTOR2(0.574f, 0.472f), D3DXVECTOR2(0.676f, 0.546f) },
	{ D3DXVECTOR3(0.3, 2, 0), D3DXVECTOR3(0, 0, -1), D3DXVECTOR2(0.574f, 0.978f), D3DXVECTOR2(0.669f, 1) },
};

VERTEX g_MeshTriWindMillBottom[] = {

	//�ٴ�.  ( Face#1)
	{ D3DXVECTOR3(1.0, -1.0, 1.0), D3DXVECTOR3(0.0, 0.0, 0.0), D3DXVECTOR2(0.0, 0.0) },
	{ D3DXVECTOR3(-1.0, -1.0, 1.0), D3DXVECTOR3(0.0, 0.0, 0.0), D3DXVECTOR2(1.0, 0.0) },
	{ D3DXVECTOR3(-1.0, -1.0, -1.0), D3DXVECTOR3(0.0, 0.0, 0.0), D3DXVECTOR2(1.0, 1.0) },
	//		 ( Face#2)
	{ D3DXVECTOR3(1.0, -1.0, 1.0), D3DXVECTOR3(0.0, 0.0, 0.0), D3DXVECTOR2(0.0, 0.0) },
	{ D3DXVECTOR3(-1.0, -1.0, -1.0), D3DXVECTOR3(0.0, 0.0, 0.0), D3DXVECTOR2(1.0, 1.0) },
	{ D3DXVECTOR3(1.0, -1.0, -1.0), D3DXVECTOR3(0.0, 0.0, 0.0), D3DXVECTOR2(0.0, 1.0) },

};

LPDIRECT3DVERTEXBUFFER9	g_pVBTriWindmill_Body = NULL;					//���� ���ۿ� ������.(��ü)
LPDIRECT3DVERTEXBUFFER9	g_pVBTriWindmill_Wing[3] = { NULL, NULL, NULL };//���� ���ۿ� ������.(����)
LPDIRECT3DVERTEXBUFFER9	g_pVBTriWindmill_Bottom = NULL;					//���� ���ۿ� ������.(�ٴ�)


////////////////////////////////////////////////////////////////////////////
//
int TripleWindmillInit(D3DXVECTOR3 vPos)
{

    int i;

	for (i = 0; i < _countof(g_MeshTriWindmill_Body); ++i)
		D3DXVec3Normalize(&g_MeshTriWindmill_Body[i].vNormal, &g_MeshTriWindmill_Body[i].vNormal);

	for (i = 0; i < _countof(g_MeshTriWindmill_Wing); ++i)
		D3DXVec3Normalize(&g_MeshTriWindmill_Wing[i].vNormal, &g_MeshTriWindmill_Wing[i].vNormal);


	g_pTripleWindmill = new WINDMILL;
	g_pTripleWindmill->bShowInnerLight = FALSE;
	assert(g_pTripleWindmill != NULL);

    g_pTripleWindmill->INDEX_BUFFER = NULL;
    g_pTripleWindmill->Wing[0].INDEX_BUFFER = NULL;
    g_pTripleWindmill->Wing[1].INDEX_BUFFER = NULL;
    g_pTripleWindmill->Wing[2].INDEX_BUFFER = NULL;
    g_pTripleWindmill->Bottom.INDEX_BUFFER = NULL;

	// [ ǳ�� �ٵ� ��ĺ��� �ʱ�ȭ �� Y�� 2�� ������ ]
	g_pTripleWindmill->vPos = vPos;								//ǳ�� ���� ��ġ
	g_pTripleWindmill->vRot = D3DXVECTOR3(0, 0, 0);				//ǳ�� ȸ�� ����.
	D3DXMatrixIdentity(&g_pTripleWindmill->mTM);					
	D3DXMatrixIdentity(&g_pTripleWindmill->mRot);
	D3DXMatrixIdentity(&g_pTripleWindmill->mScale);
	D3DXMatrixIdentity(&g_pTripleWindmill->mTrans);
	g_pTripleWindmill->mScale[5] *= 2.0f;							


	g_pTripleWindmill->Wing[0].vPos = D3DXVECTOR3(0, 2, -1.0f);
	g_pTripleWindmill->Wing[1].vPos = D3DXVECTOR3(1, 4, 0.0f);
	g_pTripleWindmill->Wing[2].vPos = D3DXVECTOR3(-0.5f, 6, 0.5f);

	for (i = 0; i < 3; i++)
	{
		D3DXMatrixIdentity(&g_pTripleWindmill->Wing[i].mTM);				
		D3DXMatrixIdentity(&g_pTripleWindmill->Wing[i].mRot);
		D3DXMatrixIdentity(&g_pTripleWindmill->Wing[i].mScale);
		D3DXMatrixIdentity(&g_pTripleWindmill->Wing[i].mTrans);
	}

	D3DXMatrixScaling(&g_pTripleWindmill->Wing[0].mScale, 1.5f, 1.5f, 1.5f);
	D3DXMatrixScaling(&g_pTripleWindmill->Wing[2].mScale, 0.8f, 0.8f, 0.8f);

	ZeroMemory(&g_TriWindMTL, sizeof(g_TriWindMTL));
	g_TriWindMTL.Diffuse = { 1, 1, 1, 1 };
	g_TriWindMTL.Ambient = { 0.8f, 0.8f, 0.8f, 1 };
	g_TriWindMTL.Specular = { 1, 1, 1, 1 };
	g_TriWindMTL.Power = 800.0f;

	ZeroMemory(&g_TriWindWingMTL, sizeof(g_TriWindWingMTL));
	g_TriWindWingMTL.Diffuse = { 1, 1, 1, 1 };
	g_TriWindWingMTL.Ambient = { 0.8f, 0.8f, 0.8f, 1 };
	g_TriWindWingMTL.Specular = { 1, 1, 1, 1 };
	g_TriWindWingMTL.Power = 800.0f;

	// ǳ�� ��ü��. ���� ���� ����.
	if (FAILED(g_pDevice->CreateVertexBuffer(
		sizeof(g_MeshTriWindmill_Body),	//��	
		0,
		VERTEX::FVF,					//��
		D3DPOOL_MANAGED,
		&g_pVBTriWindmill_Body,			//��
		NULL)))
	{
		return E_FAIL;
	}

	//���� ä���.
	VOID*	pBuff;
	if (FAILED(g_pVBTriWindmill_Body->Lock(0, sizeof(g_MeshTriWindmill_Body), (void**)&pBuff, 0)))
	{
		return E_FAIL;
	}

	memcpy(pBuff, g_MeshTriWindmill_Body, sizeof(g_MeshTriWindmill_Body));
	g_pVBTriWindmill_Body->Unlock();


	//
	// ǳ�� ������ ���� ���� ����.
	//
	for (int i = 0; i < 3; i++)
	{
		if (FAILED(g_pDevice->CreateVertexBuffer(
			sizeof(g_MeshTriWindmill_Wing),	//��	
			0,
			VERTEX::FVF,					//��
			D3DPOOL_MANAGED,
			&g_pVBTriWindmill_Wing[i],			//��
			NULL)))
		{
			return E_FAIL;
		}

		//���� ä���.
		if (FAILED(g_pVBTriWindmill_Wing[i]->Lock(0, sizeof(g_MeshTriWindmill_Wing), (void**)&pBuff, 0)))
		{
			return E_FAIL;
		}

		memcpy(pBuff, g_MeshTriWindmill_Wing, sizeof(g_MeshTriWindmill_Wing));
		g_pVBTriWindmill_Wing[i]->Unlock();
	}

	//
	// ǳ�� �ٴڿ� ���� ���� ����.
	//
	if (FAILED(g_pDevice->CreateVertexBuffer(
		sizeof(g_MeshTriWindMillBottom),	//��	
		0,
		VERTEX::FVF,					//��
		D3DPOOL_MANAGED,
		&g_pVBTriWindmill_Bottom,			//��
		NULL)))
	{
		return E_FAIL;
	}

	//���� ä���.
	if (FAILED(g_pVBTriWindmill_Bottom->Lock(0, sizeof(g_MeshTriWindMillBottom), (void**)&pBuff, 0)))
	{
		return E_FAIL;
	}

	memcpy(pBuff, g_MeshTriWindMillBottom, sizeof(g_MeshTriWindMillBottom));
	g_pVBTriWindmill_Bottom->Unlock();

	return TRUE;
}


//HRESULT WINDMILL::InitIB() 
//{
//    INDEX  indices[] = {
//         { 0,  1,  2 },
//         { 5,  3,  4 },
//         { 8,  6,  7 },
//         { 9,  10,  11 },
//
//    };
//
//    if (FAILED(g_pDevice->CreateIndexBuffer(sizeof(indices),
//        0,
//        D3DFMT_INDEX16,		
//        D3DPOOL_DEFAULT,
//        &g_pTripleWindmill->INDEX_BUFFER, NULL)))
//    {
//        return E_FAIL;
//    }
//    void* pIB = NULL;
//    if (FAILED(g_pTripleWindmill->INDEX_BUFFER->Lock(0, sizeof(indices), (void**)&pIB, 0)))
//        return E_FAIL;
//    memcpy(pIB, indices, sizeof(indices));
//    g_pTripleWindmill->INDEX_BUFFER->Unlock();
//
//    return S_OK;
//}



////////////////////////////////////////////////////////////////////////////
//
void TripleWindmillUpdate(float dTime)
{
	D3DXMATRIX RotateWing;
	D3DXMatrixIdentity(&RotateWing);

	//-------------------------------------------------------------------------- 
	// ǳ�� ��ü ��� ���.
	//--------------------------------------------------------------------------  

	// ǳ�� ��ü �̵�  
	static float mov = 10.0f;

	if (IsKeyDown('T'))		g_pTripleWindmill->vPos.z += mov * dTime;
	if (IsKeyDown('G'))		g_pTripleWindmill->vPos.z -= mov * dTime;
	if (IsKeyDown('H'))		g_pTripleWindmill->vPos.x += mov * dTime;
	if (IsKeyDown('F'))		g_pTripleWindmill->vPos.x -= mov * dTime;

	D3DXMatrixTranslation(&g_pTripleWindmill->mTrans,
		g_pTripleWindmill->vPos.x,
		g_pTripleWindmill->vPos.y,
		g_pTripleWindmill->vPos.z);		// ǳ�� ��ü �̵���� �����.	ó���� �ѹ��� ���. ��


	// ǳ�� ȸ��
	//
	static float WM_angle = 0.0f;

	if (IsKeyDown('R'))
	{
		WM_angle += D3DX_PI * dTime;
	}
	if (IsKeyDown('Y'))
	{
		WM_angle -= D3DX_PI * dTime;
	}

	D3DXMATRIX mRot;
	D3DXMatrixRotationY(&g_pTripleWindmill->mRot, WM_angle);


	// 'ǳ�� ���� ��ȯ �� - TM -  ����ϱ� :  
	// 
	// BodyTM = S * R * T
	//
	//g_pWindmill->mTM = g_pWindmill->mTrans;		
	g_pTripleWindmill->mTM = g_pTripleWindmill->mScale * g_pTripleWindmill->mRot * g_pTripleWindmill->mTrans;

	//-------------------------------------------------------------------------- 
	// ���� ��� ���.
	//--------------------------------------------------------------------------

	// ����1 �̵�, ȸ�� ��� 
	for (int i = 0; i < 3; i++)
	{
		D3DXMatrixTranslation(&g_pTripleWindmill->Wing[i].mTrans,
			g_pTripleWindmill->Wing[i].vPos.x,
			g_pTripleWindmill->Wing[i].vPos.y,
			g_pTripleWindmill->Wing[i].vPos.z);
	}

	static float angle[3] = { 0.0f, 0.0f, 0.0f };
	static float speed = 1;

	if (g_SeasonState == Ss_WINTER)
	{
		speed -= dTime * 0.5;
		if (speed <= 0) speed = 0;
		angle[0] += D3DX_PI * dTime / 4 * speed;					//180(��)/sec  ��, 1ȸ���� 4�� �ҿ�.
		D3DXMatrixRotationZ(&g_pTripleWindmill->Wing[0].mRot, angle[0]);
		angle[1] += D3DX_PI * -dTime * speed;						//180(��)/sec  ��, 1ȸ���� 2�� �ҿ�.
		D3DXMatrixRotationZ(&g_pTripleWindmill->Wing[1].mRot, angle[1]);
		angle[2] += D3DX_PI * dTime * 2 * speed;					//180(��)/sec  ��, 1ȸ���� 1�� �ҿ�.
		D3DXMatrixRotationZ(&g_pTripleWindmill->Wing[2].mRot, angle[2]);
	}
	else if (g_SeasonState != Ss_WINTER)
	{
		if (speed < 1) speed += dTime * 0.5;
		else if (speed >= 1) speed = 1;
		angle[0] += D3DX_PI * dTime / 4 * speed;					//180(��)/sec  ��, 1ȸ���� 4�� �ҿ�.
		D3DXMatrixRotationZ(&g_pTripleWindmill->Wing[0].mRot, angle[0]);
		angle[1] += D3DX_PI * -dTime * speed;						//180(��)/sec  ��, 1ȸ���� 2�� �ҿ�.
		D3DXMatrixRotationZ(&g_pTripleWindmill->Wing[1].mRot, angle[1]);
		angle[2] += D3DX_PI * dTime * 2 * speed;					//180(��)/sec  ��, 1ȸ���� 1�� �ҿ�.
		D3DXMatrixRotationZ(&g_pTripleWindmill->Wing[2].mRot, angle[2]);
	}
	
	D3DXMatrixRotationY(&RotateWing, D3DXToRadian(-90));		// ������ ����������� ������ ���� ���� ȸ������� ���� X������ -90�� ȸ������ �ִ´�.
	g_pTripleWindmill->Wing[1].mRot *= RotateWing;						// ���� X�� ���� -90�� ȸ���ϴ� ȸ������� "����"�� ȸ����Ŀ� �����ش�.

	D3DXMatrixRotationY(&RotateWing, D3DXToRadian(135));		
	g_pTripleWindmill->Wing[2].mRot *= RotateWing;			


	// ǳ��1 ���� ���� TM
	// wingTM = S * R * T
	// D3DXMatrixInverse(&���� ���, NULL[�Ǻ���], &������� ���� �Լ�)
	D3DXMatrixInverse(&g_pTripleWindmill->Sinverse, NULL, &g_pTripleWindmill->mScale);

	for (int i = 0; i < 3; i++)
	{
		g_pTripleWindmill->Wing[i].mTM = g_pTripleWindmill->Wing[i].mScale * g_pTripleWindmill->Wing[i].mRot * g_pTripleWindmill->Wing[i].mTrans * g_pTripleWindmill->Sinverse;
		g_pTripleWindmill->Wing[i].mTM *= g_pTripleWindmill->mTM;
	}

	//-------------------------------------------------------------------------- 
	// ǳ�� �ٴ� ��� ���.
	//--------------------------------------------------------------------------  
	D3DXMatrixScaling(&g_pTripleWindmill->Bottom.mScale, 1.70, 1, 1.70);
	g_pTripleWindmill->Bottom.mRot = g_pTripleWindmill->mRot;
	D3DXMatrixTranslation(&g_pTripleWindmill->Bottom.mTrans, g_pTripleWindmill->vPos.x, g_pTripleWindmill->vPos.y + 1, g_pTripleWindmill->vPos.z);

	g_pTripleWindmill->Bottom.mTM = g_pTripleWindmill->Bottom.mScale * g_pTripleWindmill->Bottom.mRot * g_pTripleWindmill->Bottom.mTrans;
}

void WindMillBottomDraw1(float dTime)
{
	if (g_bAlphaT)
	{
		g_pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);				// ���� �׽�Ʈ ON!
		g_pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);			// ũ�ų� ������ ���.��
		g_pDevice->SetRenderState(D3DRS_ALPHAREF, (DWORD)(0.0 * 255));
	}

	if (g_bAlphaB)
	{
		g_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);			// ���� ���� ON! 
		g_pDevice->SetRenderState(D3DRS_SRCBLEND, D3DRS_BLENDFACTOR);
		g_pDevice->SetRenderState(D3DRS_BLENDFACTOR, D3DXCOLOR(0.25, 0.25, 0.25, 0.25));
		g_pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	}

	g_pDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_SELECTARG1);
	g_pDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	g_pDevice->SetTexture(0, g_pWindmill->Bottom.pTex);

	g_pDevice->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_MODULATE);
	g_pDevice->SetTextureStageState(1, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	g_pDevice->SetTextureStageState(1, D3DTSS_COLORARG2, D3DTA_CURRENT);
	g_pDevice->SetTexture(1, g_pMap->pTex[0]);

	g_pDevice->SetTextureStageState(2, D3DTSS_COLOROP, D3DTOP_DISABLE);


	g_pDevice->SetFVF(VERTEX::FVF);
	g_pDevice->SetStreamSource(0, g_pVBTriWindmill_Bottom, 0, sizeof VERTEX);
	g_pDevice->SetTransform(D3DTS_WORLD, &g_pTripleWindmill->Bottom.mTM);
	g_pDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 2);

	/* �⺻������ ��ȯ */
	g_pDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
	g_pDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	g_pDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);

	g_pDevice->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_DISABLE);

	g_pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	g_pDevice->SetTexture(0, NULL);

}

////////////////////////////////////////////////////////////////////////////
//
void TripleWindmillDraw(float dTime)
{
	g_pDevice->SetRenderState(D3DRS_NORMALIZENORMALS, TRUE);

	float alpha = 0.49f;

	g_pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, g_bAlphaT);			// ���� �׽�Ʈ
	g_pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);		// ũ�ų� ������ ���.��
	g_pDevice->SetRenderState(D3DRS_ALPHAREF, (DWORD)(alpha * 255));

	g_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, g_bAlphaB);		// ���� ����
	g_pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);


	g_pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);

	if (g_pTripleWindmill->bShowInnerLight)
	{
		g_pDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_SELECTARG1);
		g_pDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
		g_pDevice->SetTexture(0, g_pWindmill->Wing->pTex[0]);

		g_pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);
		g_pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	}
	else
	{
		g_pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);
		g_pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);		//���� ���� 
		g_pDevice->SetTexture(0, g_pWindmill->Wing->pTex[0]);
	}

	// ���� ��ü �׸���.
	g_pDevice->SetMaterial(&g_TriWindMTL);
	g_pDevice->SetFVF(VERTEX::FVF);
	g_pDevice->SetStreamSource(0, g_pVBTriWindmill_Body, 0, sizeof VERTEX);	//��
	g_pDevice->SetTransform(D3DTS_WORLD, &g_pTripleWindmill->mTM);
    g_pDevice->SetIndices(g_pTripleWindmill->INDEX_BUFFER);
    g_pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 24, 0, 4);
	g_pDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 4);
    //g_pDevice->SetIndices(g_pTripleWindmill->INDEX_BUFFER);
    //g_pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 12, 0, 4);
	DrawVisibleNormal(g_MeshTriWindmill_Body, _countof(g_MeshTriWindmill_Body));

	g_pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);					// �ٱ���

	if (g_pTripleWindmill->bShowInnerLight)
	{
		g_pDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
		g_pDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
		g_pDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
		g_pDevice->SetTexture(0, g_pWindmill->Wing->pTex[0]);

		g_pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);
		g_pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);		//���� ���� 
	}

	if (g_SeasonState == Ss_WINTER)
	{
		// <Stage 0> �ؽ���
		g_pDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_SELECTARG1);
		g_pDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
		g_pDevice->SetTexture(0, g_pWindmill->Wing->pTex[0]);

		g_pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);
		g_pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);		//��

		// <Stage 1> �ؽ��� + ����ũ
		g_pDevice->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_ADDSIGNED);
		g_pDevice->SetTextureStageState(1, D3DTSS_COLORARG1, D3DTA_CURRENT);
		g_pDevice->SetTextureStageState(1, D3DTSS_COLORARG2, D3DTA_TEXTURE);

		g_pDevice->SetTexture(1, g_pWindmill->Wing->pTex[1]);

		// <Stage 2> �ؽ��� * ����
		g_pDevice->SetTextureStageState(2, D3DTSS_COLOROP, D3DTOP_MODULATE);
		g_pDevice->SetTextureStageState(2, D3DTSS_COLORARG1, D3DTA_CURRENT);
		g_pDevice->SetTextureStageState(2, D3DTSS_COLORARG2, D3DTA_DIFFUSE);

	}
	else if (g_SeasonState != Ss_WINTER)
	{
		g_pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);
		g_pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);		//���� ���� 
		g_pDevice->SetTexture(0, g_pWindmill->Wing->pTex[0]);
	}

	// �ٱ� ��ü �׸���.
	g_pDevice->SetMaterial(&g_TriWindMTL);
	g_pDevice->SetFVF(VERTEX::FVF);
	g_pDevice->SetStreamSource(0, g_pVBTriWindmill_Body, 0, sizeof VERTEX);	//��
	g_pDevice->SetTransform(D3DTS_WORLD, &g_pTripleWindmill->mTM);
	g_pDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 4);
    //g_pDevice->SetIndices(g_pTripleWindmill->INDEX_BUFFER);
    //g_pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, _countof(g_MeshTriWindmill_Body), 0, _countof(g_indices));
	DrawVisibleNormal(g_MeshTriWindmill_Body, _countof(g_MeshTriWindmill_Body));

	g_pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	// ����1 �׸���.
	// ǳ�� ������ ����̽��� ����Ѵ�. 
	for (int i = 0; i < 3; i++)
	{
		g_pDevice->SetMaterial(&g_TriWindWingMTL);
		g_pDevice->SetFVF(VERTEX::FVF);
		g_pDevice->SetStreamSource(0, g_pVBTriWindmill_Wing[i], 0, sizeof VERTEX);	//��
		g_pDevice->SetTransform(D3DTS_WORLD, &g_pTripleWindmill->Wing[i].mTM);		//������ TM(ȸ��..) ����.��
		g_pDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 8);							//���� �׸���.
		DrawVisibleNormal(g_MeshTriWindmill_Wing, _countof(g_MeshTriWindmill_Wing));
	}


	//----------------------------------------------------------------
	//						�⺻������ ��ȯ
	g_pDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
	g_pDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	g_pDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);

	g_pDevice->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_DISABLE);

	g_pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	g_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
	g_pDevice->SetRenderState(D3DRS_NORMALIZENORMALS, FALSE);
	//----------------------------------------------------------------
}


////////////////////////////////////////////////////////////////////////////
//
void TripleWindmillRelease()
{
	SAFE_RELEASE(g_pVBTriWindmill_Body);	//ǳ���� ���� ������ ������...��
	for (int i = 0; i < 3; i++)
	SAFE_RELEASE(g_pVBTriWindmill_Wing[i]);	//ǳ���� ���� ������ ������...��
	SAFE_RELEASE(g_pVBTriWindmill_Bottom);

	SAFE_DELETE(g_pTripleWindmill);			//ǳ�� ��ü ����...
}
















/****************** end of file "TripleWindmill.h" ************************/
