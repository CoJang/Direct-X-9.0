#include "d3dx9.h" 
#include "assert.h"
#include "Device.h"
#include "Windmill.h"
#include "Render.h"

#include "Vertex.h"
#include "Normal.h"

#include "Map.h"
#include "Hero.h"
#include "Season.h"


////////////////////////////////////////////////////////////////////////////
//
//주인공 클래스 개체 포인터 
HERO* g_pHero = NULL;
LPD3DXMESH  g_pHeroMeshSphere = NULL;
FLOAT h_scale = 0.5f;
D3DMATERIAL9 g_HeroMaterial;

//주인공 모델 - 기하 데이터들. 
struct VTX_LINE
{
	D3DXVECTOR3 vPos;
	DWORD		color;
};
#define FVF_HERO (D3DFVF_XYZ | D3DFVF_DIFFUSE)

VERTEX  g_MeshHero[] = {

	// -2.25f를 해준 이유는 회전축을 중앙으로 옮기기 위함이다.
	// 왼 다리
	{ D3DXVECTOR3(0.5f - 2.25f, 2.0f, 0.0f)*h_scale, D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DXVECTOR2(0.453, 0.824) },	//	8
	{ D3DXVECTOR3(2.0f - 2.25f, 2.0f, 0.0f)*h_scale, D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DXVECTOR2(0.542, 0.832) },	//	9
	{ D3DXVECTOR3(1.0f - 2.25f, 0.0f, 0.0f)*h_scale, D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DXVECTOR2(0.484, 0.982) },	// 10
	// 오른 다리
	{ D3DXVECTOR3(3.0f - 2.25f, 2.0f, 0.0f)*h_scale, D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DXVECTOR2(0.542, 0.832) },	//	9
	{ D3DXVECTOR3(4.0f - 2.25f, 0.0f, 0.0f)*h_scale, D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DXVECTOR2(0.484, 0.982) },	// 10
	{ D3DXVECTOR3(4.5f - 2.25f, 2.0f, 0.0f)*h_scale, D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DXVECTOR2(0.453, 0.824) },	//	8
	// 몸통
	{ D3DXVECTOR3(0.5f - 2.25f, 2.0f, 0.0f)*h_scale, D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DXVECTOR2(0.539, 0.703) },
	{ D3DXVECTOR3(4.5f - 2.25f, 2.0f, 0.0f)*h_scale, D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DXVECTOR2(0.617, 0.703) },
	{ D3DXVECTOR3(2.25f - 2.25f, 7.0f, 0.0f)*h_scale, D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DXVECTOR2(0.582, 0.605) },
	// 왼 팔
	{ D3DXVECTOR3(0.0f - 2.25f, 6.0f, -1.0f)*h_scale, D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DXVECTOR2(0.332, 0.729) },	// 7
	{ D3DXVECTOR3(1.9f - 2.25f, 6.0f, 0.0f)*h_scale, D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DXVECTOR2(0.394, 0.510) },	// 5
	{ D3DXVECTOR3(1.7f - 2.25f, 5.3f, 0.0f)*h_scale, D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DXVECTOR2(0.516, 0.587) },	// 6
	// 오른 팔
	{ D3DXVECTOR3(5.0f - 2.25f, 6.0f, -1.5f)*h_scale, D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DXVECTOR2(0.332, 0.729) },	// 7
	{ D3DXVECTOR3(2.7f - 2.25f, 6.0f, 0.0f)*h_scale, D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DXVECTOR2(0.394, 0.510) },	// 5
	{ D3DXVECTOR3(3.0f - 2.25f, 5.3f, 0.0f)*h_scale, D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DXVECTOR2(0.516, 0.587) },	// 6
	// 下 악
	{ D3DXVECTOR3(2.25f - 2.25f, 7.0f, 0.0f)*h_scale, D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DXVECTOR2(0.339, 0.446) },	//목과 연결점	4
	{ D3DXVECTOR3(2.25f - 2.25f, 8.0f, 1.0f)*h_scale, D3DXVECTOR3(0.0f, 1.0f, -0.5f), D3DXVECTOR2(0.589, 0.300) },	// 3
	{ D3DXVECTOR3(2.25f - 2.25f, 8.0f, -1.5f)*h_scale, D3DXVECTOR3(0.0f, 1.0f, -0.5f), D3DXVECTOR2(0.105, 0.300) },	// 2
	// 上 악
	{ D3DXVECTOR3(2.25f - 2.25f, 9.0f, 0.0f)*h_scale, D3DXVECTOR3(0.0f, 1.0f, -0.5f), D3DXVECTOR2(0.375, 0.034) },	// 1
	{ D3DXVECTOR3(2.25f - 2.25f, 8.0f, 1.0f)*h_scale, D3DXVECTOR3(0.0f, 1.0f, -0.5f), D3DXVECTOR2(0.589, 0.300) },	// 3
	{ D3DXVECTOR3(2.25f - 2.25f, 8.0f, -1.5f)*h_scale, D3DXVECTOR3(0.0f, 1.0f, -0.5f), D3DXVECTOR2(0.105, 0.300) },	// 2
	// 꼬리 근육
	{ D3DXVECTOR3(2.30f - 2.25f, 3.66f, 0.05f)*h_scale, D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DXVECTOR2(0.679, 0.751) }, //11
	{ D3DXVECTOR3(2.35f - 2.25f, 2.0f, 0.05f)*h_scale, D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DXVECTOR2(0.773, 0.948) },	 //12
	{ D3DXVECTOR3(1.0f - 2.25f, 6.0f, 4.0f)*h_scale, D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DXVECTOR2(0.863, 0.618) },	 //13
	// 꼬리 아래 불꽃
	{ D3DXVECTOR3(1.0f - 2.25f, 6.0f, 4.0f)*h_scale, D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DXVECTOR2(0.863, 0.618) },	//꼬리와 연결점 13
	{ D3DXVECTOR3(0.5f - 2.25f, 6.5f, 4.3f)*h_scale, D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DXVECTOR2(0.757, 0.476) },	// 14
	{ D3DXVECTOR3(1.5f - 2.25f, 6.5f, 4.3f)*h_scale, D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DXVECTOR2(0.953, 0.476) },	// 15
	// 꼬리 윗 불꽃
	{ D3DXVECTOR3(1.0f - 2.25f, 7.8f, 4.8f)*h_scale, D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DXVECTOR2(0.867, 0.317) },	// 16
	{ D3DXVECTOR3(0.5f - 2.25f, 6.5f, 4.3f)*h_scale, D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DXVECTOR2(0.757, 0.476) },	// 14
	{ D3DXVECTOR3(1.5f - 2.25f, 6.5f, 4.3f)*h_scale, D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DXVECTOR2(0.953, 0.476) },	// 15


};

VERTEX g_MeshHeroBottom[] = {

	//바닥.  ( Face#1)
	{ D3DXVECTOR3(1.0, -1.0, 1.0), D3DXVECTOR3(0.0, 0.0, 0.0), D3DXVECTOR2(0.0, 0.0) },
	{ D3DXVECTOR3(-1.0, -1.0, 1.0), D3DXVECTOR3(0.0, 0.0, 0.0), D3DXVECTOR2(1.0, 0.0) },
	{ D3DXVECTOR3(-1.0, -1.0, -1.0), D3DXVECTOR3(0.0, 0.0, 0.0), D3DXVECTOR2(1.0, 1.0) },
	//		 ( Face#2)
	{ D3DXVECTOR3(1.0, -1.0, 1.0), D3DXVECTOR3(0.0, 0.0, 0.0), D3DXVECTOR2(0.0, 0.0) },
	{ D3DXVECTOR3(-1.0, -1.0, -1.0), D3DXVECTOR3(0.0, 0.0, 0.0), D3DXVECTOR2(1.0, 1.0) },
	{ D3DXVECTOR3(1.0, -1.0, -1.0), D3DXVECTOR3(0.0, 0.0, 0.0), D3DXVECTOR2(0.0, 1.0) },

};

VTX_LINE g_DirHeroLine[2];

//정점 버퍼용 포인터.
LPDIRECT3DVERTEXBUFFER9	g_pVBHero = NULL;
LPDIRECT3DVERTEXBUFFER9	g_pVBHero_Bottom = NULL;




////////////////////////////////////////////////////////////////////////////
//
int HeroInit(char* name, D3DXVECTOR3 vPos)
{
	g_pHero = new HERO;
	assert(g_pHero != NULL);

	g_pHero->Hp = 100;
	g_pHero->Lv = 1;
	g_pHero->Exp = 0;
	strcpy(g_pHero->Name, name);

	g_pHero->vPos = vPos;								//주인공 시작위치.
	g_pHero->vOrgPos = vPos;
	g_pHero->fVelo = 0.0f;								//★
	g_pHero->vDir = D3DXVECTOR3(0, 0, -1);				//★
	g_pHero->vCenterL = D3DXVECTOR3(0, 0, 0);
	g_pHero->vCenterW = D3DXVECTOR3(0, 0, 0);
	g_pHero->fRadius = 0.8f;
	
	D3DXMatrixIdentity(&g_pHero->mTM);					//행렬 변수의 초기화.
	D3DXMatrixIdentity(&g_pHero->mRot);
	D3DXMatrixIdentity(&g_pHero->mScale);
	D3DXMatrixIdentity(&g_pHero->mTrans);

	D3DXMatrixIdentity(&g_pHero->mLRot);
	D3DXMatrixIdentity(&g_pHero->mRRot);
	D3DXMatrixIdentity(&g_pHero->temp_mTM);
	D3DXMatrixIdentity(&g_pHero->R_mTM);

	g_DirHeroLine[0] = { D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0xff00ff05 };
	g_DirHeroLine[1] = { D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0xff00ff05 };

	for (int i = 0; i < _countof(g_MeshHero); ++i)
		D3DXVec3Normalize(&g_MeshHero[i].vNormal, &g_MeshHero[i].vNormal);

	ZeroMemory(&g_HeroMaterial, sizeof(g_HeroMaterial));
	g_HeroMaterial.Diffuse = { 1, 1, 1, 1 };
	g_HeroMaterial.Ambient = { 0.8f, 0.8f, 0.8f, 1 };
	g_HeroMaterial.Specular = { 1, 1, 1, 1 };
	g_HeroMaterial.Power = 800.f;
	
	g_pHero->g_TextureName = "./Data/Pa2Ry_a.dds";
	if (FAILED(D3DXCreateTextureFromFile(g_pDevice, g_pHero->g_TextureName, &g_pHero->pTex)))
	{
		MessageBox(NULL, "(히어로)텍스쳐 로드 실패.", "에러", MB_ICONERROR | MB_OK);
		return E_FAIL;
	}

	g_pHero->bot.g_TextureName = "./Data/flare0.dds";
	D3DXCreateTextureFromFile(g_pDevice, g_pHero->bot.g_TextureName, &g_pHero->bot.pTex);
	//정점 버퍼 생성.
	if(FAILED(g_pDevice->CreateVertexBuffer(
										sizeof(g_MeshHero),		
										0, 
										VERTEX::FVF,			
										D3DPOOL_MANAGED,	
										&g_pVBHero,			
										NULL)))
	{
		return E_FAIL;
	}

	//버퍼 채우기.
	VOID*	pBuff;
 	if(FAILED(g_pVBHero->Lock(0, sizeof(g_MeshHero), (void**)&pBuff, 0 )))
	{
		return E_FAIL;
	}
	memcpy(pBuff, g_MeshHero, sizeof(g_MeshHero));
	g_pVBHero->Unlock();

	// 바닥용 정점 버퍼 생성.
	if (FAILED(g_pDevice->CreateVertexBuffer(
		sizeof(g_MeshHeroBottom),	//★	
		0,
		VERTEX::FVF,					//★
		D3DPOOL_MANAGED,
		&g_pVBHero_Bottom,			//★
		NULL)))
	{
		return E_FAIL;
	}

	//버퍼 채우기.
	if (FAILED(g_pVBHero_Bottom->Lock(0, sizeof(g_MeshHeroBottom), (void**)&pBuff, 0)))
	{
		return E_FAIL;
	}

	memcpy(pBuff, g_MeshHeroBottom, sizeof(g_MeshHeroBottom));
	g_pVBHero_Bottom->Unlock();

	return TRUE;
}




////////////////////////////////////////////////////////////////////////////
//
void HeroMove(float dTime)
{
	static float angle = 0.0f;

	if(IsKeyDown(VK_F9))		//리셋 코드.(디버깅시 필요)
	{
		g_pHero->vPos = g_pHero->vOrgPos;
		g_pHero->vPos  = D3DXVECTOR3(0,0,0);
		angle = 0.0f;
	}

	// 
	// 회전 값 계산. : 회전 행렬 생성.

	g_pHero->fVelo = 0.0f;

	D3DXMatrixRotationY(&g_pHero->mLRot, -3.14 * dTime);
	D3DXMatrixRotationY(&g_pHero->mRRot, 3.14 * dTime);

	if (IsKeyDown(VK_UP))		g_pHero->fVelo = 10.0f;		//전전은 빠르게..

	if (IsKeyDown(VK_DOWN))		g_pHero->fVelo = -8.0f;		//후진은 좀 느리게...

	if (IsKeyDown(VK_LEFT))
	{
		D3DXVec3TransformNormal(&g_pHero->vDir, &g_pHero->vDir, &g_pHero->mLRot);
		angle += -3.14 * dTime;
	}
	if (IsKeyDown(VK_RIGHT))
	{
		D3DXVec3TransformNormal(&g_pHero->vDir, &g_pHero->vDir, &g_pHero->mRRot);
		angle += 3.14f * dTime;
	}


 	D3DXMatrixRotationY(&g_pHero->mRot, angle);		 

	g_pHero->vPos += g_pHero->vDir * g_pHero->fVelo * dTime;

	D3DXVec3Normalize(&g_pHero->vDir, &g_pHero->vDir);
	D3DXMatrixTranslation(&g_pHero->mTrans, g_pHero->vPos.x, g_pHero->vPos.y, g_pHero->vPos.z);	// 이동행렬 만들기.	
	// 
	// '주인공 최종 변환 값 - TM -  계산하기 :  
	//

	g_DirHeroLine[0] = { D3DXVECTOR3(0.0f, 3.0f, 0.0f), 0xff00ff05 };
	g_DirHeroLine[1] = { D3DXVECTOR3(g_pHero->vDir.x, g_pHero->vDir.y + 3, g_pHero->vDir.z), 0xff00ff05 };

	/* 히어로 무게중심 바닥에 충돌구체 부착 */
#define  hero  (* g_pHero)

	D3DXMatrixTranslation(&hero.mTrans, hero.vPos.x, hero.vPos.y, hero.vPos.z);
	hero.mTM = hero.mScale * hero.mRot * hero.mTrans;
	hero.vCenterW = hero.vPos;
	D3DXVec3TransformCoord(&hero.vCenterW, &hero.vCenterL, &hero.mTM);

#undef hero

	g_pHero->mTM = g_pHero->mScale * g_pHero->mRot * g_pHero->mTrans;

}

void HeroBSphereDraw(float dTime)
{
	//충돌구는 오브제별로 다르므로, 크기 계산이 필요.
	//적절히 스케일링 하여 사용.(현재 나무는 동일크기, 생략..)
	D3DXMATRIX mTM, mTrans, mScale, mRot;
#define  hero  (* g_pHero)

	DWORD bWire;
	g_pDevice->GetRenderState(D3DRS_FILLMODE, &bWire);
	g_pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	g_pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	D3DXMatrixScaling(&mScale, hero.fRadius, hero.fRadius, hero.fRadius);
	D3DXMatrixRotationX(&mRot, D3DX_PI*0.5f);
	D3DXMatrixTranslation(&mTrans, hero.vCenterW.x, hero.vCenterW.y, hero.vCenterW.z);
	mTM = mScale * mRot * mTrans;
	g_pDevice->SetTransform(D3DTS_WORLD, &mTM);

	g_pHeroMeshSphere->DrawSubset(0);

	g_pDevice->SetRenderState(D3DRS_FILLMODE, bWire);
	g_pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

#undef hero
}



////////////////////////////////////////////////////////////////////////////
//
void HeroDraw(float dTime)
{
	D3DXMATRIX m_Temp;
	D3DXMatrixIdentity(&m_Temp);
	m_Temp *= g_pHero->mTrans;
	g_pDevice->SetTransform(D3DTS_WORLD, &m_Temp);
	g_pDevice->DrawPrimitiveUP(D3DPT_LINELIST, 1, g_DirHeroLine, sizeof(VTX_LINE));

	float alpha = 0.49f;

	g_pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, g_bAlphaT);			//알파 테스트 
	g_pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);				//크거나 같으면 통과.★
	g_pDevice->SetRenderState(D3DRS_ALPHAREF, (DWORD)(alpha * 255));	

	g_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, g_bAlphaB);			//알파 블랜딩 
	g_pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);
	g_pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);		
	 
	g_pDevice->SetFVF(VERTEX::FVF);				
	g_pDevice->SetTexture(0, g_bShowFrame ? NULL : g_pHero->pTex);
	g_pDevice->SetStreamSource(0, g_pVBHero, 0, sizeof(VERTEX)); //주인공 메쉬를 디바이스에 등록한다. 
	g_pDevice->SetTransform(D3DTS_WORLD, &g_pHero->mTM);	// "월드 공간, 위치 정보 등록" 
	
	g_pDevice->SetMaterial(&g_HeroMaterial);
	g_pDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 10); // 히어로 그리기
	
	DrawVisibleNormal(g_MeshHero, _countof(g_MeshHero));

	g_pDevice->SetTexture(0, NULL);
	SetDefault();
}

void HeroBottomDraw(float dTime)
{
	if (g_bAlphaT)
	{
		g_pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);				// 알파 테스트 ON!
		g_pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);			// 크거나 같으면 통과.★
		g_pDevice->SetRenderState(D3DRS_ALPHAREF, (DWORD)(0.05 * 255));
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
	g_pDevice->SetTexture(0, g_pHero->bot.pTex);

	g_pDevice->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_MODULATE);
	g_pDevice->SetTextureStageState(1, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	g_pDevice->SetTextureStageState(1, D3DTSS_COLORARG2, D3DTA_CURRENT);
	g_pDevice->SetTexture(1, g_pMap->pTex[0]);

	g_pDevice->SetTextureStageState(2, D3DTSS_COLOROP, D3DTOP_DISABLE);

	g_pDevice->SetFVF(VERTEX::FVF);
	g_pDevice->SetStreamSource(0, g_pVBHero_Bottom, 0, sizeof VERTEX);
	g_pDevice->SetTransform(D3DTS_WORLD, &g_pHero->bot.mTM);
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

///////////////////////////////////////////////////////////////////////////
//
void HeroRelease()
{	
	SAFE_RELEASE(g_pVBHero);		//주인공용 정점 데이터 릴리즈... 
	SAFE_DELETE(g_pHero);			//주인공 객체 제거...
}
















/****************** end of file "Hero.h" ************************/
