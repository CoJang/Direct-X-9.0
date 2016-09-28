#include "windows.h"
#include "mmsystem.h"
#include "Device.h"

#include "Normal.h"
#include "Hero.h"	
#include "Map.h"		
#include "Tree.h"	
#include "Windmill.h"
#include "Box.h"
#include "Season.h"
#include "Render.h"
#include "Plane.h"


char* g_WindowName = "B3Yena:: SKY - World" ; 
char* g_cLightState = "N/A";
char* g_cblendingState = "N/A";
char* g_ctestingState = "N/A";

//////////////////////////////////////////////////////////////////////////////
//
// 전역 변수.
// 
// ID3DXMesh : DX 내장 '모델' 클래스 개체 (인터페이스) ★
// 구sphere,박스box,콘corn,주전자teapot 등을 지원하며, 
// 정점속성,FVF,VB,IB 등의 기하구성의 자동화 및 그리기 API 를 제공합니다.
// DX 도움말을 참고하십시요.
extern LPD3DXMESH g_pTreeMeshSphere;	//모델 1개당 1개의 인터페이스 포인터 필요.★
extern LPD3DXMESH g_pWingMeshSphere;
extern LPD3DXMESH g_pHeroMeshSphere;

LPD3DXMESH g_pDotLightMesh = NULL;	// 횃불의 위치 표시용 구

D3DXMATRIXA16 g_matLightTM;		// 위치 최신화를 위한 행렬
D3DLIGHT9 Dotlight;				// 방향광

BOOL g_bLightSwitch = TRUE;		// (방향광)조명을 끄고 켜는 불
BOOL g_bShowBSphere = FALSE;	// 충돌구체를 끄고 켜는 불
BOOL g_bShowNormal = FALSE;		// 노말라인을 끄고 켜는 불	
BOOL g_bShowTorch = TRUE;		// 횃불을 끄고 켜는 불

BOOL g_bAlphaB = TRUE;			// 알파 블랜딩 [ON / OFF]
BOOL g_bAlphaT = TRUE;			// 알파 테스트 [ON / OFF]

BOOL g_bSpec = TRUE;			// 반사(스팩큘러) [ON / OFF]
	
B3Mesh*		g_pMesh = NULL;		//★
char		g_pMeshName[256] = "N/A";
CHAR		g_pMeshPath[256] = "N/A";

enum : unsigned char	// 조명의 4가지 상태
{
	ls_NOON,
	ls_SUNSET,
	ls_MIDNIGHT,
	ls_SUNRISE
}
static g_LightState;	// 상태를 저장하는 곳

// 조명 처리를 위한 GPU / 렌더링 상태 설정.
void LightsUpdate()
{

	//---------------- 
	// 광원 설정 
	//---------------- 
	D3DLIGHT9 light;											// 빛 구조체. 
	ZeroMemory(&light, sizeof(light));
	light.Type = D3DLIGHT_DIRECTIONAL;							//표준 '태양광'.

	switch (g_LightState)
	{
	case ls_NOON : 
		light.Diffuse = D3DXCOLOR(1, 1, 1, 1);
		if (g_bShowFrame) 
			g_BkColor = D3DXCOLOR(0.12f, 0.12f, 0.12f, 1);
		else
			g_BkColor = D3DXCOLOR(0.2, 0.5, 0.956, 1);
		g_cLightState = "정오";
		if (IsKeyUp(VK_F11))
			g_LightState = ls_SUNSET;
		break;

	case ls_SUNSET:
		light.Diffuse = D3DXCOLOR(1, 0.65, 0.282, 1);
		if (g_bShowFrame)
			g_BkColor = D3DXCOLOR(0.12f, 0.12f, 0.12f, 1);
		else
			g_BkColor = D3DXCOLOR(1, 0.6, 0.2, 1);
		g_cLightState = "석양이... 진다..";
		if (IsKeyUp(VK_F11))
			g_LightState = ls_MIDNIGHT;
		break;

	case ls_MIDNIGHT:
		light.Diffuse = D3DXCOLOR(0, 0, 0.005, 1);
		if (g_bShowFrame)
			g_BkColor = D3DXCOLOR(0.12f, 0.12f, 0.12f, 1);
		else
			g_BkColor = D3DXCOLOR(0.0, 0.0, 0.1, 1);
		g_cLightState = "밤이 되었습니다.";
		if (IsKeyUp(VK_F11))
			g_LightState = ls_SUNRISE;
		break;

	case ls_SUNRISE:
		light.Diffuse = D3DXCOLOR(0.3, 0.3, 1, 1);
		if (g_bShowFrame)
			g_BkColor = D3DXCOLOR(0.12f, 0.12f, 0.12f, 1);
		else
			g_BkColor = D3DXCOLOR(0.3, 0.3, 0.7, 1);
		g_cLightState = "힘세고 강한아침!";
		if (IsKeyUp(VK_F11))
			g_LightState = ls_NOON;
		break;

	default :
		light.Diffuse = D3DXCOLOR(1, 1, 1, 1);
		if (g_bShowFrame)
			g_BkColor = D3DXCOLOR(0.12f, 0.12f, 0.12f, 1);
		else
			g_BkColor = D3DXCOLOR(0.2, 0.5, 0.956, 1);
		g_LightState = ls_NOON;
		break;

	}

	//if(g_bSpec)
		light.Specular = D3DXCOLOR(1, 1, 1, 1);
	light.Direction = D3DXVECTOR3(0.0f, -2.0f, 3.0f);			//빛 방향.
	D3DXVec3Normalize((D3DXVECTOR3*)&light.Direction, (D3DXVECTOR3*)&light.Direction);

	g_pDevice->SetLight(0, &light);								//0번 라이트(소켓)에 설정.
	g_pDevice->LightEnable(0, TRUE);							//0번 라이트 ON. FALSE로 설정시 주변광원만 나온다.

	//---------------- 
	// 주변광 설정.
	//---------------- 
	if (g_bSpec)
		g_pDevice->SetRenderState(D3DRS_AMBIENT, D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f));		//30% 회색 : 표준 주변광원량★

	//---------------- 
	// 점광(횃불) 설정.
	//---------------- 

	D3DXMATRIX mRot, mScale, mTrans;

	D3DXMatrixIdentity(&mRot);
	D3DXMatrixIdentity(&mScale);
	D3DXMatrixTranslation(&mTrans, -0.625, 3.9, 2.4);

	g_matLightTM = mScale * mRot * mTrans * g_pHero->mTM;

	ZeroMemory(&Dotlight, sizeof(Dotlight));
	Dotlight.Type = D3DLIGHT_POINT;
	Dotlight.Diffuse = D3DXCOLOR(0.7, 0.3, 0, 1);
	Dotlight.Ambient = D3DXCOLOR(0.5, 0, 0, 1);
	Dotlight.Range = 5.0f;
	D3DXVec3TransformCoord((D3DXVECTOR3*)&Dotlight.Position, (D3DXVECTOR3*)&Dotlight.Position, &g_matLightTM);	// 점광의 위치에 
	Dotlight.Attenuation1 = 0.01;
	Dotlight.Attenuation2 = 0.05;

	g_pDevice->SetLight(1, &Dotlight);							//1번 라이트(소켓)에 설정.
	g_pDevice->LightEnable(1, g_bShowTorch);					//1번 라이트 ON. 

	g_pDevice->SetRenderState(D3DRS_LIGHTING, g_bLightSwitch);

	//-------------------------------------------------------------------------- 
	// 히어로 바닥 행렬 계산.
	//--------------------------------------------------------------------------  
	D3DXMatrixScaling(&g_pHero->bot.mScale, 2, 1, 2);
	g_pHero->bot.mRot = g_pHero->mRot;
	D3DXMatrixTranslation(&g_pHero->bot.mTrans, g_matLightTM._41, g_matLightTM._42 - 2.4, g_matLightTM._43);

	g_pHero->bot.mTM = g_pHero->bot.mScale * g_pHero->bot.mRot * g_pHero->bot.mTrans;

	//---------------- 
	// 알파관련 문구 설정.
	//---------------- 
	if (g_bAlphaB)
		g_cblendingState = "알파 블랜딩 [ON]";
	else
		g_cblendingState = "알파 블랜딩 [OFF]";

	if (g_bAlphaT)
		g_ctestingState = "알파 테스팅 [ON]";
	else
		g_ctestingState = "알파 테스팅 [OFF]";
}


// 모델 및 관련 정보 로딩, 초기화.
int DataLoading()
{ 	
	InitVisibleNormal();
	
	CameraSetup();		//카메라 설정.

	HeroInit("PyLee", D3DXVECTOR3(0, 0, 0));	 //주인공 생성.
	BoxInit(D3DXVECTOR3(0, 1, -10));

	MapInit("TriWorld", D3DXVECTOR3(0, -0.05f, 0), D3DXVECTOR2(128, 128));	//지형 생성.

	TreeInit();	// 나무

	//풍차..
	WindmillInit(D3DXVECTOR3(5, 0, -15));	
	TripleWindmillInit(D3DXVECTOR3(0, 0, -15));
	TripleWindmillInit2(D3DXVECTOR3(-5, 0, -15));

	//구체 생성.
	D3DXCreateSphere(g_pDevice, 1.0f, 8, 8, &g_pTreeMeshSphere, NULL);
	D3DXCreateSphere(g_pDevice, 1.0f, 8, 8, &g_pWingMeshSphere, NULL);
	D3DXCreateSphere(g_pDevice, 1.0f, 8, 8, &g_pHeroMeshSphere, NULL);
	D3DXCreateSphere(g_pDevice, 0.2f, 8, 9, &g_pDotLightMesh, NULL);		// 점광 표시용 구체

	//비행기 생성.
	PlaneInit(D3DXVECTOR3(0, 7, 0));
	DwarfInit(D3DXVECTOR3(10, 0, -10));

	LightsUpdate();		//조명 생성.
	UpdateSeason();

	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
//
void DataRelease()
{
	HeroRelease();	//주인공 제거.	
	BoxRelease();
	
	MapRelease();	//지형 제거
	
	TreeRelease();	//나무 제거.
	
	WindmillRelease();	//풍차 제거.★

	TripleWindmillRelease(); // 삼단 풍차 제거.
	TripleWindmillRelease2();

	SAFE_RELEASE(g_pTreeMeshSphere); //DX 메쉬 제거.(충돌구 표시용)★
	SAFE_RELEASE(g_pWingMeshSphere);
	SAFE_RELEASE(g_pHeroMeshSphere);
	SAFE_RELEASE(g_pDotLightMesh);

	ReleaseSeason();
	g_pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

}

void SceneStateUpdate(float dTime)
{
	if (IsKeyUp(VK_F4))g_bLightSwitch ^= TRUE;	//조명 ON / OFF
	
	if (IsKeyUp(VK_F6))g_bShowNormal ^= TRUE;	//노말 표시 On/Off

	if (IsKeyUp(VK_F7))g_bShowTorch ^= TRUE;	//횃불 ON / OFF
	
	if (IsKeyUp(VK_F8))g_bShowBSphere ^= TRUE;	//충돌구 표시 On/Off

	if (IsKeyUp('1'))g_pWindmill->bShowInnerLight ^= TRUE;			// 실내등 ON / OFF
	if (IsKeyUp('2'))g_pTripleWindmill2->bShowInnerLight ^= TRUE;	// 실내등 ON / OFF
	if (IsKeyUp('3'))g_pTripleWindmill->bShowInnerLight ^= TRUE;	// 실내등 ON / OFF


	if (IsKeyUp('9'))g_bAlphaB ^= TRUE;	// 알파 블랜딩 ON / OFF
	if (IsKeyUp('0'))g_bAlphaT ^= TRUE;	// 알파 테스트 ON / OFF

	if (IsKeyUp('4'))g_bSpec ^= TRUE; // 반사광 (스팩큘러) ON / OFF
}


 

/////////////////////////////////////////////////////////////////////////////// 
//
//  도움말. 
//
void ShowInfo()   
{ 
	PutFPS(0, 0); 

	static bool bShow = true;
	if(IsKeyUp(VK_F1)) bShow ^= true;
	if(!bShow) 
	{
		return;
	}

	{
		int x = 300, y = 10;			 
		D3DXCOLOR col(1, 1, 0, 1);
		DrawText(x, y, col, "■ %s", g_WindowName);  
		DrawText(x, y+=15, col, "> 풍차들의 조종 방법 ↓");
		DrawText(x, y+=15, col, "> W A S D, Q E"); 
		DrawText(x, y+=15, col, "> T F G H, R Y"); 
		DrawText(x, y += 15, col, "> I J K L, U O");
		DrawText(x, y += 15, col, "Spacular [ON / OFF] : '4' ");
	} 

	int x = 1, y = 20;
	D3DXCOLOR col(1, 1, 1, 1);
	
	SystemInfoShow(x, y, col);  //엔진-시스템도움말.출력.
	
	{   //좌측 도움말들.
		x -= 1000;
		y += 80; 
		DrawText(x, y+=14, col, "[와이어프레임] Space");
		DrawText(x, y += 14, col, "[조명 - 방향광] F4");
		DrawText(x, y += 14, col, "[알파 블랜딩] [9]");
		DrawText(x, y += 14, col, "[알파 테스팅] [0]");
		DrawText(x, y += 14, col, "[풍차 실내등] [1] [2] [3]");
		
		y += 14;
		DrawText(x, y+=28, col, "[Hero]");    
		DrawText(x, y += 14, col,"날개 부착:F5");
		DrawText(x, y += 14, col, "노말벡터:F6");
		DrawText(x, y += 14, col, "횃불:F7");
		DrawText(x, y += 14, col, "충돌구:F8");
		DrawText(x, y+=14, col, "리셋:F9");
		DrawText(x, y+=14, col, "Pos={%.2f, %.2f, %.2f}", g_pHero->vPos.x, g_pHero->vPos.y, g_pHero->vPos.z);   
		

	}

	x = 1000, y = 0;
	
	{   // 우측 도움말
		DrawText(x, y += 3, col, "[조명 상태] F11");
		DrawText(x, y += 14, col, "[계절 상태] F12");
		DrawText(x, y += 14, col, "조명 상태 = %s", g_cLightState);
		DrawText(x, y += 14, col, "계절 상태 = %s", g_pSnow->g_cSeasonState);
		DrawText(x, y += 14, col, "%s", g_cblendingState);
		DrawText(x, y += 14, col, "%s", g_ctestingState);
	}

}

void SamplingTest()
{
	for (int i = 0; i < 7; i++)
	{

		//Test #2-2: Mip-map : ★  
		g_pDevice->SetSamplerState(i, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);

		//Test #3.Anisotropic ★
	
		g_pDevice->SetSamplerState(i, D3DSAMP_MAGFILTER, D3DTEXF_ANISOTROPIC);
		g_pDevice->SetSamplerState(i, D3DSAMP_MINFILTER, D3DTEXF_ANISOTROPIC);

		//Anisotropic 배수. (x1~ x16)
		g_pDevice->SetSamplerState(i, D3DSAMP_MAXANISOTROPY, 16); 				
	
	}

}

void LightsMeshDraw(float dTime)
{
	if (g_bShowTorch)
	{
		HeroBottomDraw(dTime);		// 빛 망울 표시
		g_pDevice->SetTransform(D3DTS_WORLD, &g_matLightTM);
		g_pDotLightMesh->DrawSubset(0);
	}
}


////////////////////////////////////////////////////////////////////////////// 
//
// 장면 그리기 :  
// 
void SceneRender()
{ 
	//엔진- 시스템 갱신. 
	float dTime = GetEngineTime();
	SystemUpdate(dTime);
	
	SceneStateUpdate(dTime);	//장면 렌더링 상태(옵션) 갱신.. ★

	HeroMove(dTime);	//주인공 '이동' 
	BoxUpdate(dTime);
	
	MapUpdate(dTime);	//멥 업데이트.	


	//풍차 업데이트.
	WindmillUpdate(dTime);	
	TripleWindmillUpdate(dTime);
	TripleWindmillUpdate2(dTime);
	
	TreeUpdate(dTime);	//나무 업데이트.
						//(불타 없어지거나, 바람에 흔들리거나..등등의 상태변화..)

    PlaneUpdate(dTime); // 비행기 업데이트
	DwarfUpdate(dTime);
	
	CameraUpdate();		//카메라 업데이트.

	
	LightsUpdate();		//조명 업데이트.

	SamplingTest();
	

	// 장면 그리기 시작..
	//
	if(SUCCEEDED(g_pDevice->BeginScene()))		
	{
		g_pDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, g_BkColor, 1.0f, 0);

        PlaneDraw(dTime);
		DwarfDraw(dTime);

		//그리드 그리기..
		GridAxisDraw();				 

		//장면(Scene) 그리기..
		
	 	HeroDraw(dTime);
		MapDraw(dTime);		

		//TreeDraw(dTime);		
		BoxDraw(dTime);


		//WindmillDraw(dTime);
		//TripleWindmillDraw(dTime);
		//TripleWindmillDraw2(dTime);

		if (g_pWindmill->bShowInnerLight)
			WindMillBottomDraw(dTime);	// 빛 샘 표시
		if (g_pTripleWindmill->bShowInnerLight)
			WindMillBottomDraw1(dTime);
		if (g_pTripleWindmill2->bShowInnerLight)
			WindMillBottomDraw2(dTime);
		LightsMeshDraw(dTime);		// 점광 표시

		UpdateSeason();
		//나무 충돌구 그리기.★
		if (g_bShowBSphere)
		{
			TreeBSphereDraw(dTime);
			WingBSphereDraw(dTime);
			HeroBSphereDraw(dTime);
		}

	
		//시스템 객체 & 도움말 출력..
		ShowInfo();					 
		g_pDevice->EndScene();
	}

	g_pDevice->Present(NULL, NULL, NULL, NULL);


}


/************ end of file "Render.cpp" ******************************/
