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

// 풍차 몸체 : 피라미드 형태.
VERTEX g_MeshTriWindmill_Body[] = {
	// 4방향의 벽체..
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

	//'밑면' 은 필요 없다..
};



//풍차 날개.
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

	//바닥.  ( Face#1)
	{ D3DXVECTOR3(1.0, -1.0, 1.0), D3DXVECTOR3(0.0, 0.0, 0.0), D3DXVECTOR2(0.0, 0.0) },
	{ D3DXVECTOR3(-1.0, -1.0, 1.0), D3DXVECTOR3(0.0, 0.0, 0.0), D3DXVECTOR2(1.0, 0.0) },
	{ D3DXVECTOR3(-1.0, -1.0, -1.0), D3DXVECTOR3(0.0, 0.0, 0.0), D3DXVECTOR2(1.0, 1.0) },
	//		 ( Face#2)
	{ D3DXVECTOR3(1.0, -1.0, 1.0), D3DXVECTOR3(0.0, 0.0, 0.0), D3DXVECTOR2(0.0, 0.0) },
	{ D3DXVECTOR3(-1.0, -1.0, -1.0), D3DXVECTOR3(0.0, 0.0, 0.0), D3DXVECTOR2(1.0, 1.0) },
	{ D3DXVECTOR3(1.0, -1.0, -1.0), D3DXVECTOR3(0.0, 0.0, 0.0), D3DXVECTOR2(0.0, 1.0) },

};

LPDIRECT3DVERTEXBUFFER9	g_pVBTriWindmill_Body = NULL;					//정점 버퍼용 포인터.(몸체)
LPDIRECT3DVERTEXBUFFER9	g_pVBTriWindmill_Wing[3] = { NULL, NULL, NULL };//정점 버퍼용 포인터.(날개)
LPDIRECT3DVERTEXBUFFER9	g_pVBTriWindmill_Bottom = NULL;					//정점 버퍼용 포인터.(바닥)


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

	// [ 풍차 바디 행렬변수 초기화 및 Y축 2배 스케일 ]
	g_pTripleWindmill->vPos = vPos;								//풍차 시작 위치
	g_pTripleWindmill->vRot = D3DXVECTOR3(0, 0, 0);				//풍차 회전 없음.
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

	// 풍차 몸체용. 정점 버퍼 생성.
	if (FAILED(g_pDevice->CreateVertexBuffer(
		sizeof(g_MeshTriWindmill_Body),	//★	
		0,
		VERTEX::FVF,					//★
		D3DPOOL_MANAGED,
		&g_pVBTriWindmill_Body,			//★
		NULL)))
	{
		return E_FAIL;
	}

	//버퍼 채우기.
	VOID*	pBuff;
	if (FAILED(g_pVBTriWindmill_Body->Lock(0, sizeof(g_MeshTriWindmill_Body), (void**)&pBuff, 0)))
	{
		return E_FAIL;
	}

	memcpy(pBuff, g_MeshTriWindmill_Body, sizeof(g_MeshTriWindmill_Body));
	g_pVBTriWindmill_Body->Unlock();


	//
	// 풍차 날개용 정점 버퍼 생성.
	//
	for (int i = 0; i < 3; i++)
	{
		if (FAILED(g_pDevice->CreateVertexBuffer(
			sizeof(g_MeshTriWindmill_Wing),	//★	
			0,
			VERTEX::FVF,					//★
			D3DPOOL_MANAGED,
			&g_pVBTriWindmill_Wing[i],			//★
			NULL)))
		{
			return E_FAIL;
		}

		//버퍼 채우기.
		if (FAILED(g_pVBTriWindmill_Wing[i]->Lock(0, sizeof(g_MeshTriWindmill_Wing), (void**)&pBuff, 0)))
		{
			return E_FAIL;
		}

		memcpy(pBuff, g_MeshTriWindmill_Wing, sizeof(g_MeshTriWindmill_Wing));
		g_pVBTriWindmill_Wing[i]->Unlock();
	}

	//
	// 풍차 바닥용 정점 버퍼 생성.
	//
	if (FAILED(g_pDevice->CreateVertexBuffer(
		sizeof(g_MeshTriWindMillBottom),	//★	
		0,
		VERTEX::FVF,					//★
		D3DPOOL_MANAGED,
		&g_pVBTriWindmill_Bottom,			//★
		NULL)))
	{
		return E_FAIL;
	}

	//버퍼 채우기.
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
	// 풍차 몸체 행렬 계산.
	//--------------------------------------------------------------------------  

	// 풍차 몸체 이동  
	static float mov = 10.0f;

	if (IsKeyDown('T'))		g_pTripleWindmill->vPos.z += mov * dTime;
	if (IsKeyDown('G'))		g_pTripleWindmill->vPos.z -= mov * dTime;
	if (IsKeyDown('H'))		g_pTripleWindmill->vPos.x += mov * dTime;
	if (IsKeyDown('F'))		g_pTripleWindmill->vPos.x -= mov * dTime;

	D3DXMatrixTranslation(&g_pTripleWindmill->mTrans,
		g_pTripleWindmill->vPos.x,
		g_pTripleWindmill->vPos.y,
		g_pTripleWindmill->vPos.z);		// 풍차 몸체 이동행렬 만들기.	처음에 한번만 계산. ★


	// 풍차 회전
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


	// '풍차 최종 변환 값 - TM -  계산하기 :  
	// 
	// BodyTM = S * R * T
	//
	//g_pWindmill->mTM = g_pWindmill->mTrans;		
	g_pTripleWindmill->mTM = g_pTripleWindmill->mScale * g_pTripleWindmill->mRot * g_pTripleWindmill->mTrans;

	//-------------------------------------------------------------------------- 
	// 날개 행렬 계산.
	//--------------------------------------------------------------------------

	// 날개1 이동, 회전 행렬 
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
		angle[0] += D3DX_PI * dTime / 4 * speed;					//180(도)/sec  즉, 1회전에 4초 소요.
		D3DXMatrixRotationZ(&g_pTripleWindmill->Wing[0].mRot, angle[0]);
		angle[1] += D3DX_PI * -dTime * speed;						//180(도)/sec  즉, 1회전에 2초 소요.
		D3DXMatrixRotationZ(&g_pTripleWindmill->Wing[1].mRot, angle[1]);
		angle[2] += D3DX_PI * dTime * 2 * speed;					//180(도)/sec  즉, 1회전에 1초 소요.
		D3DXMatrixRotationZ(&g_pTripleWindmill->Wing[2].mRot, angle[2]);
	}
	else if (g_SeasonState != Ss_WINTER)
	{
		if (speed < 1) speed += dTime * 0.5;
		else if (speed >= 1) speed = 1;
		angle[0] += D3DX_PI * dTime / 4 * speed;					//180(도)/sec  즉, 1회전에 4초 소요.
		D3DXMatrixRotationZ(&g_pTripleWindmill->Wing[0].mRot, angle[0]);
		angle[1] += D3DX_PI * -dTime * speed;						//180(도)/sec  즉, 1회전에 2초 소요.
		D3DXMatrixRotationZ(&g_pTripleWindmill->Wing[1].mRot, angle[1]);
		angle[2] += D3DX_PI * dTime * 2 * speed;					//180(도)/sec  즉, 1회전에 1초 소요.
		D3DXMatrixRotationZ(&g_pTripleWindmill->Wing[2].mRot, angle[2]);
	}
	
	D3DXMatrixRotationY(&RotateWing, D3DXToRadian(-90));		// 날개를 수평방향으로 돌려서 놓기 위해 회전행렬을 만들어서 X축으로 -90도 회전값을 넣는다.
	g_pTripleWindmill->Wing[1].mRot *= RotateWing;						// 위에 X축 기준 -90도 회전하는 회전행렬을 "날개"의 회전행렬에 곱해준다.

	D3DXMatrixRotationY(&RotateWing, D3DXToRadian(135));		
	g_pTripleWindmill->Wing[2].mRot *= RotateWing;			


	// 풍차1 날개 최종 TM
	// wingTM = S * R * T
	// D3DXMatrixInverse(&저장 행렬, NULL[판별식], &역행렬을 취할 함수)
	D3DXMatrixInverse(&g_pTripleWindmill->Sinverse, NULL, &g_pTripleWindmill->mScale);

	for (int i = 0; i < 3; i++)
	{
		g_pTripleWindmill->Wing[i].mTM = g_pTripleWindmill->Wing[i].mScale * g_pTripleWindmill->Wing[i].mRot * g_pTripleWindmill->Wing[i].mTrans * g_pTripleWindmill->Sinverse;
		g_pTripleWindmill->Wing[i].mTM *= g_pTripleWindmill->mTM;
	}

	//-------------------------------------------------------------------------- 
	// 풍차 바닥 행렬 계산.
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
		g_pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);				// 알파 테스트 ON!
		g_pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);			// 크거나 같으면 통과.★
		g_pDevice->SetRenderState(D3DRS_ALPHAREF, (DWORD)(0.0 * 255));
	}

	if (g_bAlphaB)
	{
		g_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);			// 알파 블렌딩 ON! 
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

	/* 기본값으로 전환 */
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

	g_pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, g_bAlphaT);			// 알파 테스트
	g_pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);		// 크거나 같으면 통과.★
	g_pDevice->SetRenderState(D3DRS_ALPHAREF, (DWORD)(alpha * 255));

	g_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, g_bAlphaB);		// 알파 블랜딩
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
		g_pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);		//알파 블랜딩 
		g_pDevice->SetTexture(0, g_pWindmill->Wing->pTex[0]);
	}

	// 안쪽 몸체 그리기.
	g_pDevice->SetMaterial(&g_TriWindMTL);
	g_pDevice->SetFVF(VERTEX::FVF);
	g_pDevice->SetStreamSource(0, g_pVBTriWindmill_Body, 0, sizeof VERTEX);	//★
	g_pDevice->SetTransform(D3DTS_WORLD, &g_pTripleWindmill->mTM);
    g_pDevice->SetIndices(g_pTripleWindmill->INDEX_BUFFER);
    g_pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 24, 0, 4);
	g_pDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 4);
    //g_pDevice->SetIndices(g_pTripleWindmill->INDEX_BUFFER);
    //g_pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 12, 0, 4);
	DrawVisibleNormal(g_MeshTriWindmill_Body, _countof(g_MeshTriWindmill_Body));

	g_pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);					// 바깥면

	if (g_pTripleWindmill->bShowInnerLight)
	{
		g_pDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
		g_pDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
		g_pDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
		g_pDevice->SetTexture(0, g_pWindmill->Wing->pTex[0]);

		g_pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);
		g_pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);		//알파 블랜딩 
	}

	if (g_SeasonState == Ss_WINTER)
	{
		// <Stage 0> 텍스쳐
		g_pDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_SELECTARG1);
		g_pDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
		g_pDevice->SetTexture(0, g_pWindmill->Wing->pTex[0]);

		g_pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);
		g_pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);		//★

		// <Stage 1> 텍스쳐 + 마스크
		g_pDevice->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_ADDSIGNED);
		g_pDevice->SetTextureStageState(1, D3DTSS_COLORARG1, D3DTA_CURRENT);
		g_pDevice->SetTextureStageState(1, D3DTSS_COLORARG2, D3DTA_TEXTURE);

		g_pDevice->SetTexture(1, g_pWindmill->Wing->pTex[1]);

		// <Stage 2> 텍스쳐 * 조명
		g_pDevice->SetTextureStageState(2, D3DTSS_COLOROP, D3DTOP_MODULATE);
		g_pDevice->SetTextureStageState(2, D3DTSS_COLORARG1, D3DTA_CURRENT);
		g_pDevice->SetTextureStageState(2, D3DTSS_COLORARG2, D3DTA_DIFFUSE);

	}
	else if (g_SeasonState != Ss_WINTER)
	{
		g_pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);
		g_pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);		//알파 블랜딩 
		g_pDevice->SetTexture(0, g_pWindmill->Wing->pTex[0]);
	}

	// 바깥 몸체 그리기.
	g_pDevice->SetMaterial(&g_TriWindMTL);
	g_pDevice->SetFVF(VERTEX::FVF);
	g_pDevice->SetStreamSource(0, g_pVBTriWindmill_Body, 0, sizeof VERTEX);	//★
	g_pDevice->SetTransform(D3DTS_WORLD, &g_pTripleWindmill->mTM);
	g_pDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 4);
    //g_pDevice->SetIndices(g_pTripleWindmill->INDEX_BUFFER);
    //g_pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, _countof(g_MeshTriWindmill_Body), 0, _countof(g_indices));
	DrawVisibleNormal(g_MeshTriWindmill_Body, _countof(g_MeshTriWindmill_Body));

	g_pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	// 날개1 그리기.
	// 풍차 날개를 디바이스에 등록한다. 
	for (int i = 0; i < 3; i++)
	{
		g_pDevice->SetMaterial(&g_TriWindWingMTL);
		g_pDevice->SetFVF(VERTEX::FVF);
		g_pDevice->SetStreamSource(0, g_pVBTriWindmill_Wing[i], 0, sizeof VERTEX);	//★
		g_pDevice->SetTransform(D3DTS_WORLD, &g_pTripleWindmill->Wing[i].mTM);		//날개의 TM(회전..) 설정.★
		g_pDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 8);							//날개 그리기.
		DrawVisibleNormal(g_MeshTriWindmill_Wing, _countof(g_MeshTriWindmill_Wing));
	}


	//----------------------------------------------------------------
	//						기본값으로 전환
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
	SAFE_RELEASE(g_pVBTriWindmill_Body);	//풍차용 정점 데이터 릴리즈...★
	for (int i = 0; i < 3; i++)
	SAFE_RELEASE(g_pVBTriWindmill_Wing[i]);	//풍차용 정점 데이터 릴리즈...★
	SAFE_RELEASE(g_pVBTriWindmill_Bottom);

	SAFE_DELETE(g_pTripleWindmill);			//풍차 객체 제거...
}
















/****************** end of file "TripleWindmill.h" ************************/
