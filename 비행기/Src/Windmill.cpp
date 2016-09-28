//
// Windmill.cpp
//
//
// 2007.01.25. Kihong Kim / mad_dog@hanmail.net
//

#include "windows.h"
#include "assert.h"
#include "Device.h"

#include "Vertex.h"
#include "Normal.h"
#include "Render.h"

#include "Map.h"
#include "Windmill.h"
#include "Hero.h"
#include "Season.h"
 

////////////////////////////////////////////////////////////////////////////
//
WINDMILL* g_pWindmill = NULL;
D3DMATERIAL9 g_Windmill_MTL;
D3DMATERIAL9 g_WindmillWing_MTL;

// 풍차 몸체 : 피라미드 형태.
VERTEX g_MeshWindmill_Body[] = {
		
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
VERTEX g_MeshWindmill_Wing[] = {
	{ D3DXVECTOR3(-2, -0.5, 0), D3DXVECTOR3(0, 0, -1), D3DXVECTOR2(0.710f, 0.978f), D3DXVECTOR2(0.710f, 0.978f) },
	{ D3DXVECTOR3(-2, 0.3, 0), D3DXVECTOR3(0, 0, -1), D3DXVECTOR2(0.574f, 0.978f), D3DXVECTOR2(0.574f, 0.978f) },
	{ D3DXVECTOR3(0, -0.5, 0), D3DXVECTOR3(0, 0, -1), D3DXVECTOR2(0.710f, 0.472f), D3DXVECTOR2(0.710f, 0.472f) },

	{ D3DXVECTOR3(0, -0.5, 0), D3DXVECTOR3(0, 0, -1), D3DXVECTOR2(0.710f, 0.472f), D3DXVECTOR2(0.710f, 0.472f) },
	{ D3DXVECTOR3(0, 0.3, 0), D3DXVECTOR3(0, 0, -1), D3DXVECTOR2(0.574f, 0.472f), D3DXVECTOR2(0.574f, 0.472f) },
	{ D3DXVECTOR3(-2, 0.3, 0), D3DXVECTOR3(0, 0, -1), D3DXVECTOR2(0.574f, 0.978f), D3DXVECTOR2(0.574f, 0.978f) },

	{ D3DXVECTOR3(2, -0.3, 0), D3DXVECTOR3(0, 0, -1), D3DXVECTOR2(0.574f, 0.978f), D3DXVECTOR2(0.574f, 0.978f) },
	{ D3DXVECTOR3(2, 0.5, 0), D3DXVECTOR3(0, 0, -1), D3DXVECTOR2(0.710f, 0.978f), D3DXVECTOR2(0.710f, 0.978f) },
	{ D3DXVECTOR3(0, -0.3, 0), D3DXVECTOR3(0, 0, -1), D3DXVECTOR2(0.574f, 0.472f), D3DXVECTOR2(0.574f, 0.472f) },

	{ D3DXVECTOR3(0, -0.3, 0), D3DXVECTOR3(0, 0, -1), D3DXVECTOR2(0.574f, 0.472f), D3DXVECTOR2(0.574f, 0.472f) },
	{ D3DXVECTOR3(0, 0.5, 0), D3DXVECTOR3(0, 0, -1), D3DXVECTOR2(0.710f, 0.472f), D3DXVECTOR2(0.710f, 0.472f) },
	{ D3DXVECTOR3(2, 0.5, 0), D3DXVECTOR3(0, 0, -1), D3DXVECTOR2(0.710f, 0.978f), D3DXVECTOR2(0.710f, 0.978f) },

	{ D3DXVECTOR3(-0.3, -2, 0), D3DXVECTOR3(0, 0, -1), D3DXVECTOR2(0.574f, 0.978f), D3DXVECTOR2(0.574f, 0.978f) },
	{ D3DXVECTOR3(0.5, -2, 0), D3DXVECTOR3(0, 0, -1), D3DXVECTOR2(0.710f, 0.978f), D3DXVECTOR2(0.710f, 0.978f) },
	{ D3DXVECTOR3(-0.3, 0, 0), D3DXVECTOR3(0, 0, -1), D3DXVECTOR2(0.574f, 0.472f), D3DXVECTOR2(0.574f, 0.472f) },

	{ D3DXVECTOR3(-0.3, 0, 0), D3DXVECTOR3(0, 0, -1), D3DXVECTOR2(0.574f, 0.472f), D3DXVECTOR2(0.574f, 0.472f) },
	{ D3DXVECTOR3(0.5, 0, 0), D3DXVECTOR3(0, 0, -1), D3DXVECTOR2(0.710f, 0.472f), D3DXVECTOR2(0.710f, 0.472f) },
	{ D3DXVECTOR3(0.5, -2, 0), D3DXVECTOR3(0, 0, -1), D3DXVECTOR2(0.710f, 0.978f), D3DXVECTOR2(0.710f, 0.978f) },

	{ D3DXVECTOR3(-0.5, 2, 0), D3DXVECTOR3(0, 0, -1), D3DXVECTOR2(0.710f, 0.978f), D3DXVECTOR2(0.710f, 0.978f)},
	{ D3DXVECTOR3(0.3, 2, 0), D3DXVECTOR3(0, 0, -1), D3DXVECTOR2(0.574f, 0.978f), D3DXVECTOR2(0.574f, 0.978f) },
	{ D3DXVECTOR3(-0.5, 0, 0), D3DXVECTOR3(0, 0, -1), D3DXVECTOR2(0.710f, 0.472f), D3DXVECTOR2(0.710f, 0.472f) },

	{ D3DXVECTOR3(-0.5, 0, 0), D3DXVECTOR3(0, 0, -1), D3DXVECTOR2(0.710f, 0.472f), D3DXVECTOR2(0.710f, 0.472f) },
	{ D3DXVECTOR3(0.3, 0, 0), D3DXVECTOR3(0, 0, -1), D3DXVECTOR2(0.574f, 0.472f), D3DXVECTOR2(0.574f, 0.472f) },
	{ D3DXVECTOR3(0.3, 2, 0), D3DXVECTOR3(0, 0, -1), D3DXVECTOR2(0.574f, 0.978f), D3DXVECTOR2(0.574f, 0.978f) },

};

VERTEX g_MeshWindMillBottom[] = {

	//바닥.  ( Face#1)
	{ D3DXVECTOR3(1.0, -1.0, 1.0), D3DXVECTOR3(0.0, 0.0, 0.0), D3DXVECTOR2(0.0, 0.0) },
	{ D3DXVECTOR3(-1.0, -1.0, 1.0), D3DXVECTOR3(0.0, 0.0, 0.0), D3DXVECTOR2(1.0, 0.0) },
	{ D3DXVECTOR3(-1.0, -1.0, -1.0), D3DXVECTOR3(0.0, 0.0, 0.0), D3DXVECTOR2(1.0, 1.0) },
	//		 ( Face#2)
	{ D3DXVECTOR3(1.0, -1.0, 1.0), D3DXVECTOR3(0.0, 0.0, 0.0), D3DXVECTOR2(0.0, 0.0) },
	{ D3DXVECTOR3(-1.0, -1.0, -1.0), D3DXVECTOR3(0.0, 0.0, 0.0), D3DXVECTOR2(1.0, 1.0) },
	{ D3DXVECTOR3(1.0, -1.0, -1.0), D3DXVECTOR3(0.0, 0.0, 0.0), D3DXVECTOR2(0.0, 1.0) },

};


LPDIRECT3DVERTEXBUFFER9	g_pVBWindmill_Body = NULL;		//정점 버퍼용 포인터.(몸체)
LPDIRECT3DVERTEXBUFFER9	g_pVBWindmill_Wing = NULL;		//정점 버퍼용 포인터.(날개)
LPDIRECT3DVERTEXBUFFER9	g_pVBWindmill_Bottom = NULL;	//정점 버퍼용 포인터.(바닥)





////////////////////////////////////////////////////////////////////////////
//
int WindmillInit(D3DXVECTOR3 vPos)
{
	int i;

	for (i = 0; i < _countof(g_MeshWindmill_Body); ++i)
		D3DXVec3Normalize(&g_MeshWindmill_Body[i].vNormal, &g_MeshWindmill_Body[i].vNormal);

	for (i = 0; i < _countof(g_MeshWindmill_Wing); ++i)
		D3DXVec3Normalize(&g_MeshWindmill_Wing[i].vNormal, &g_MeshWindmill_Wing[i].vNormal);

	g_pWindmill = new WINDMILL;
	assert(g_pWindmill != NULL);
	isHeroSelect = FALSE;
	g_pWindmill->bShowInnerLight = FALSE;

	g_pWindmill->vPos = vPos;								//풍차 시작 위치
	g_pWindmill->vRot = D3DXVECTOR3(0, 0, 0);				//풍차 회전 없음.

	g_pWindmill->Bottom.vPos = vPos;								//풍차 시작 위치
	g_pWindmill->Bottom.vRot = D3DXVECTOR3(0, 0, 0);				//풍차 회전 없음.

	D3DXMatrixIdentity(&g_pWindmill->mTM);					// 몸통 행렬 변수의 초기화.
	D3DXMatrixIdentity(&g_pWindmill->mRot);
	D3DXMatrixIdentity(&g_pWindmill->mScale);
	D3DXMatrixIdentity(&g_pWindmill->mTrans);

	D3DXMatrixIdentity(&g_pWindmill->Wing[0].mTM);			// 날개 행렬 변수의 초기화.
	D3DXMatrixIdentity(&g_pWindmill->Wing[0].mRot);
	D3DXMatrixIdentity(&g_pWindmill->Wing[0].mScale);
	D3DXMatrixIdentity(&g_pWindmill->Wing[0].mTrans);

	D3DXMatrixIdentity(&g_pWindmill->Bottom.mTM);
	D3DXMatrixIdentity(&g_pWindmill->Bottom.mTrans);
	D3DXMatrixIdentity(&g_pWindmill->Bottom.mScale);
	D3DXMatrixIdentity(&g_pWindmill->Bottom.mRot);

	ZeroMemory(&g_Windmill_MTL, sizeof(g_Windmill_MTL));
	g_Windmill_MTL.Diffuse = { 1, 1, 1, 1 };
	g_Windmill_MTL.Ambient = { 0.8f, 0.8f, 0.8f, 1 };

	ZeroMemory(&g_WindmillWing_MTL, sizeof(g_WindmillWing_MTL));
	g_WindmillWing_MTL.Diffuse = { 1, 1, 1, 1 };
	g_WindmillWing_MTL.Ambient = { 0.8f, 0.8f, 0.8f, 1 };

	ZeroMemory(&g_pWindmill->Bottom.WMBOT_MTL, sizeof(g_pWindmill->Bottom.WMBOT_MTL));
	g_pWindmill->Bottom.WMBOT_MTL.Ambient = g_pWindmill->Bottom.WMBOT_MTL.Diffuse = { 1, 1, 1, 1 };
	

	g_pWindmill->Wing->g_TextureName[0] = "./Data/windmill.dds";

	if (FAILED(D3DXCreateTextureFromFile(g_pDevice, g_pWindmill->Wing->g_TextureName[0], &g_pWindmill->Wing->pTex[0])))
	{
		MessageBox(NULL, "(기본풍차_날개)텍스쳐 로드 실패.", "에러", MB_ICONERROR | MB_OK);
		return E_FAIL;
	}

	g_pWindmill->Wing->g_TextureName[1] = "./Data/WM_mask3.png";
	D3DXCreateTextureFromFile(g_pDevice, g_pWindmill->Wing->g_TextureName[1], &g_pWindmill->Wing->pTex[1]);

	g_pWindmill->Bottom.g_TextureName = "./Data/Lit.dds";
	D3DXCreateTextureFromFile(g_pDevice, g_pWindmill->Bottom.g_TextureName, &g_pWindmill->Bottom.pTex);

	// 
	// 풍차 몸체용. 정점 버퍼 생성.
	//
	if(FAILED(g_pDevice->CreateVertexBuffer(
										sizeof(g_MeshWindmill_Body),	//★	
										0, 
										VERTEX::FVF,					//★
										D3DPOOL_MANAGED,	
										&g_pVBWindmill_Body,			//★
										NULL)))
	{
		return E_FAIL;
	}

	//버퍼 채우기.
	VOID*	pBuff;
 	if(FAILED(g_pVBWindmill_Body->Lock(0, sizeof(g_MeshWindmill_Body), (void**)&pBuff, 0 )))
	{
		return E_FAIL;
	}

	memcpy(pBuff, g_MeshWindmill_Body, sizeof(g_MeshWindmill_Body));
	g_pVBWindmill_Body->Unlock();

	
	//
	// 풍차 날개용 정점 버퍼 생성.
	//
	if(FAILED(g_pDevice->CreateVertexBuffer(
										sizeof(g_MeshWindmill_Wing),	//★	
										0, 
										VERTEX::FVF,					//★
										D3DPOOL_MANAGED,	
										&g_pVBWindmill_Wing,			//★
										NULL)))
	{
		return E_FAIL;
	}

	//버퍼 채우기.
  	if(FAILED(g_pVBWindmill_Wing->Lock(0, sizeof(g_MeshWindmill_Wing), (void**)&pBuff, 0 )))
	{
		return E_FAIL;
	}

	memcpy(pBuff, g_MeshWindmill_Wing, sizeof(g_MeshWindmill_Wing));
	g_pVBWindmill_Wing->Unlock();

	//
	// 풍차 바닥용 정점 버퍼 생성.
	//
	if (FAILED(g_pDevice->CreateVertexBuffer(
		sizeof(g_MeshWindMillBottom),	//★	
		0,
		VERTEX::FVF,					//★
		D3DPOOL_MANAGED,
		&g_pVBWindmill_Bottom,			//★
		NULL)))
	{
		return E_FAIL;
	}

	//버퍼 채우기.
	if (FAILED(g_pVBWindmill_Bottom->Lock(0, sizeof(g_MeshWindMillBottom), (void**)&pBuff, 0)))
	{
		return E_FAIL;
	}

	memcpy(pBuff, g_MeshWindMillBottom, sizeof(g_MeshWindMillBottom));
	g_pVBWindmill_Bottom->Unlock();



	return TRUE;
}




////////////////////////////////////////////////////////////////////////////
//
void WindmillUpdate(float dTime)
{
	D3DXMATRIX RotateWing;
	D3DXMatrixIdentity(&RotateWing);

	if (IsKeyUp(VK_F5))
	{
		if (isHeroSelect == FALSE)
			isHeroSelect = TRUE;

		else if (isHeroSelect == TRUE)
			isHeroSelect = FALSE;
	}


	//-------------------------------------------------------------------------- 
	// 풍차 몸체 행렬 계산.
	//--------------------------------------------------------------------------  

	// 풍차 몸체 이동  
	static float mov = 10.0f;

	if (IsKeyDown('W'))		g_pWindmill->vPos.z += mov * dTime;
	if (IsKeyDown('S'))		g_pWindmill->vPos.z -= mov * dTime;
	if (IsKeyDown('D'))		g_pWindmill->vPos.x += mov * dTime;
	if (IsKeyDown('A'))		g_pWindmill->vPos.x -= mov * dTime;

	D3DXMatrixTranslation(&g_pWindmill->mTrans,
							g_pWindmill->vPos.x,
							g_pWindmill->vPos.y,
							g_pWindmill->vPos.z);		// 풍차 몸체 이동행렬 만들기.	처음에 한번만 계산. ★

	// 풍차 회전
	//
	static float WM_angle = 0.0f;

	if (IsKeyDown('Q'))
	{
		WM_angle += D3DX_PI * dTime;
	}
	if (IsKeyDown('E'))
	{
		WM_angle -= D3DX_PI * dTime;
	}

	D3DXMATRIX mRot;
	D3DXMatrixRotationY(&g_pWindmill->mRot, WM_angle);


	// '풍차 최종 변환 값 - TM -  계산하기 :  
	// 
	// BodyTM = S * R * T
 	//
	//g_pWindmill->mTM = g_pWindmill->mTrans;		
	D3DXMatrixMultiply(&g_pWindmill->mTM, &g_pWindmill->mScale, &g_pWindmill->mRot);
  	D3DXMatrixMultiply(&g_pWindmill->mTM, &g_pWindmill->mTM, &g_pWindmill->mTrans);	 


	//-------------------------------------------------------------------------- 
	// 날개 행렬 계산.
	//-------------------------------------------------------------------------- 
	// 날개 회전 값 계산. : 회전 행렬 생성. 

	static float angle = 0.0f;	
	static float speed = 1;
	if (g_SeasonState == Ss_WINTER)
	{
		speed -= dTime * 0.5;
		if (speed <= 0)
			speed = 0;
		angle += D3DX_PI * dTime * speed;
		D3DXMatrixRotationZ(&g_pWindmill->Wing[0].mRot, angle);		 
	}
	else if (g_SeasonState != Ss_WINTER)
	{
		if (speed < 1)
			speed += dTime * 0.5;
		else if (speed >= 1)
			speed = 1;
		
		angle += D3DX_PI * dTime * speed;				
		D3DXMatrixRotationZ(&g_pWindmill->Wing[0].mRot, angle);
	}

	// 날개 이동 행렬 만들기. 
	D3DXMatrixTranslation(&g_pWindmill->Wing[0].mTrans,
							g_pWindmill->Wing[0].vPos.x,
							g_pWindmill->Wing[0].vPos.y,
							g_pWindmill->Wing[0].vPos.z);

	// D3DXMatrixInverse(&저장 행렬, NULL[판별식], &역행렬을 취할 함수)

	// F5누름에 따른 날개 위치이동 및 회전변환 						

	if (isHeroSelect == TRUE)
	{
		D3DXMatrixRotationX(&RotateWing, D3DXToRadian(90));		// 날개를 수평방향으로 돌려서 놓기 위해 회전행렬을 만들어서 X축으로 90도 회전값을 넣는다.
		g_pWindmill->Wing[0].mRot *= RotateWing;						// 위에 X축 기준 90도 회전하는 회전행렬을 "날개"의 회전행렬에 곱해준다.
		//(히어로 기준 상대좌표. (0, 5, 0))
		g_pWindmill->Wing[0].vPos = D3DXVECTOR3(0, 5, 0);

	}
	else if (isHeroSelect == FALSE)
	{
		//(몸체기준 상대좌표. (0, 2, -1))
		g_pWindmill->Wing[0].vPos = D3DXVECTOR3(0, 2, -1.0f);
	}

	// 풍차 날개 최종 TM
	// wingTM = S * R * T

	D3DXMatrixMultiply(&g_pWindmill->Wing[0].mTM, &g_pWindmill->Wing[0].mScale, &g_pWindmill->Wing[0].mRot);
	D3DXMatrixMultiply(&g_pWindmill->Wing[0].mTM, &g_pWindmill->Wing[0].mTM, &g_pWindmill->Wing[0].mTrans);		 


	//-------------------------------------------------------------------------- 
	// 풍차 날개를 바디에 붙이기.★
	//-------------------------------------------------------------------------- 
	// wingLastTM = wingTM * BodyTM
	//
	if (isHeroSelect == TRUE)		// 토글 ON이면 히어로 행렬을 곱하여 붙인다
		D3DXMatrixMultiply(&g_pWindmill->Wing[0].mTM, &g_pWindmill->Wing[0].mTM, &g_pHero->mTM);		
	if (isHeroSelect == FALSE)		// 토글 OFF이면 풍차[바디] 행렬을 곱하여 붙인다
		D3DXMatrixMultiply(&g_pWindmill->Wing[0].mTM, &g_pWindmill->Wing[0].mTM, &g_pWindmill->mTM);

	//-------------------------------------------------------------------------- 
	// 풍차 바닥 행렬 계산.
	//--------------------------------------------------------------------------  
	D3DXMatrixScaling(&g_pWindmill->Bottom.mScale, 1.70, 1, 1.70);
	g_pWindmill->Bottom.mRot = g_pWindmill->mRot;
	D3DXMatrixTranslation(&g_pWindmill->Bottom.mTrans, g_pWindmill->vPos.x, g_pWindmill->vPos.y + 1, g_pWindmill->vPos.z);

	g_pWindmill->Bottom.mTM = g_pWindmill->Bottom.mScale * g_pWindmill->Bottom.mRot * g_pWindmill->Bottom.mTrans;
}


void WindMillBottomDraw(float dTime)
{
	g_pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, g_bAlphaT);		// 알파 테스트 ON / OFF!
	g_pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);			// 크거나 같으면 통과.★
	g_pDevice->SetRenderState(D3DRS_ALPHAREF, (DWORD)(0.0 * 255));
	
	g_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, g_bAlphaB);			// 알파 블렌딩 ON! 
	g_pDevice->SetRenderState(D3DRS_SRCBLEND, D3DRS_BLENDFACTOR);			// 배경
	g_pDevice->SetRenderState(D3DRS_BLENDFACTOR, D3DXCOLOR(0.25, 0.25, 0.25, 0.25));
	g_pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);				// 마스크

	///////////////////////// 알파 존 ////////////////////////////////

	g_pDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_SELECTARG1);
	g_pDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	g_pDevice->SetTexture(0, g_pWindmill->Bottom.pTex);

	g_pDevice->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_MODULATE);
	g_pDevice->SetTextureStageState(1, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	g_pDevice->SetTextureStageState(1, D3DTSS_COLORARG2, D3DTA_CURRENT);
	g_pDevice->SetTexture(1, g_pMap->pTex[0]);

	g_pDevice->SetTextureStageState(2, D3DTSS_COLOROP, D3DTOP_DISABLE);

	g_pDevice->SetFVF(VERTEX::FVF);
	g_pDevice->SetStreamSource(0, g_pVBWindmill_Bottom, 0, sizeof VERTEX);	
	g_pDevice->SetTransform(D3DTS_WORLD, &g_pWindmill->Bottom.mTM);
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
void WindmillDraw(float dTime)
{ 
	float alpha = 0.49f;

	if (g_bAlphaT)
	{
		g_pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
		g_pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);			//크거나 같으면 통과.★
		g_pDevice->SetRenderState(D3DRS_ALPHAREF, (DWORD)(alpha * 255));
	}

	if (g_bAlphaB)
	{
		g_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);			//알파 블렌딩 ON! 
		g_pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		// 블렌딩 방법 결정 : "알파 기준" 블렌딩...★
		g_pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	}

	///////////////////////////////////// 안 쪽면//////////////////////////////////////////////// 
	

	g_pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);					

	if (g_pWindmill->bShowInnerLight)
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
	g_pDevice->SetMaterial(&g_Windmill_MTL);
	g_pDevice->SetFVF(VERTEX::FVF);
	g_pDevice->SetStreamSource(0, g_pVBWindmill_Body, 0, sizeof VERTEX);	//★
  	g_pDevice->SetTransform(D3DTS_WORLD, &g_pWindmill->mTM);	
  	g_pDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 4);		
	DrawVisibleNormal(g_MeshWindmill_Body, _countof(g_MeshWindmill_Body));

	///////////////////////////////////// 안 쪽면//////////////////////////////////////////////// 


	///////////////////////////////////// // 바깥 쪽면///////////////////////////////////////////
	g_pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);					 

	if (g_pWindmill->bShowInnerLight)
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
	g_pDevice->SetMaterial(&g_Windmill_MTL);
	g_pDevice->SetFVF(VERTEX::FVF);
	g_pDevice->SetStreamSource(0, g_pVBWindmill_Body, 0, sizeof VERTEX);	//★
	g_pDevice->SetTransform(D3DTS_WORLD, &g_pWindmill->mTM);
	g_pDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 4);
	DrawVisibleNormal(g_MeshWindmill_Body, _countof(g_MeshWindmill_Body));

	g_pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);	// 컬링 모드 OFF 

	///////////////////////////////////// // 바깥 쪽면///////////////////////////////////////////

	// 날개 그리기.
	g_pDevice->SetMaterial(&g_WindmillWing_MTL);
	g_pDevice->SetFVF(VERTEX::FVF);
	g_pDevice->SetStreamSource(0, g_pVBWindmill_Wing, 0, sizeof VERTEX);	//★
	g_pDevice->SetTransform(D3DTS_WORLD, &g_pWindmill->Wing[0].mTM);		//날개의 TM(회전..) 설정.★
	g_pDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 8);						//날개 그리기.		
	DrawVisibleNormal(g_MeshWindmill_Wing, _countof(g_MeshWindmill_Wing));
 
	//----------------------------------------------------------------
	//텍스처 스테이지 설정 : 기본값으로 전환
	g_pDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
	g_pDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	g_pDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);

	g_pDevice->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_DISABLE);

	g_pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);	// 알파 테스트 OFF
	g_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);	// 알파 블랜딩 OFF
	//----------------------------------------------------------------
}










////////////////////////////////////////////////////////////////////////////
//
void WindmillRelease()
{	
	SAFE_RELEASE(g_pVBWindmill_Body);		//풍차용 정점 데이터 릴리즈...★
	SAFE_RELEASE(g_pVBWindmill_Wing);		//풍차용 정점 데이터 릴리즈...★
	SAFE_RELEASE(g_pVBWindmill_Bottom);

	SAFE_DELETE(g_pWindmill);			//풍차 객체 제거...
}
















/****************** end of file "Windmill.h" ************************/
