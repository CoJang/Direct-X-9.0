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
// ���� ����.
// 
// ID3DXMesh : DX ���� '��' Ŭ���� ��ü (�������̽�) ��
// ��sphere,�ڽ�box,��corn,������teapot ���� �����ϸ�, 
// �����Ӽ�,FVF,VB,IB ���� ���ϱ����� �ڵ�ȭ �� �׸��� API �� �����մϴ�.
// DX ������ �����Ͻʽÿ�.
extern LPD3DXMESH g_pTreeMeshSphere;	//�� 1���� 1���� �������̽� ������ �ʿ�.��
extern LPD3DXMESH g_pWingMeshSphere;
extern LPD3DXMESH g_pHeroMeshSphere;

LPD3DXMESH g_pDotLightMesh = NULL;	// ȶ���� ��ġ ǥ�ÿ� ��

D3DXMATRIXA16 g_matLightTM;		// ��ġ �ֽ�ȭ�� ���� ���
D3DLIGHT9 Dotlight;				// ���Ɽ

BOOL g_bLightSwitch = TRUE;		// (���Ɽ)������ ���� �Ѵ� ��
BOOL g_bShowBSphere = FALSE;	// �浹��ü�� ���� �Ѵ� ��
BOOL g_bShowNormal = FALSE;		// �븻������ ���� �Ѵ� ��	
BOOL g_bShowTorch = TRUE;		// ȶ���� ���� �Ѵ� ��

BOOL g_bAlphaB = TRUE;			// ���� ���� [ON / OFF]
BOOL g_bAlphaT = TRUE;			// ���� �׽�Ʈ [ON / OFF]

BOOL g_bSpec = TRUE;			// �ݻ�(����ŧ��) [ON / OFF]
	
B3Mesh*		g_pMesh = NULL;		//��
char		g_pMeshName[256] = "N/A";
CHAR		g_pMeshPath[256] = "N/A";

enum : unsigned char	// ������ 4���� ����
{
	ls_NOON,
	ls_SUNSET,
	ls_MIDNIGHT,
	ls_SUNRISE
}
static g_LightState;	// ���¸� �����ϴ� ��

// ���� ó���� ���� GPU / ������ ���� ����.
void LightsUpdate()
{

	//---------------- 
	// ���� ���� 
	//---------------- 
	D3DLIGHT9 light;											// �� ����ü. 
	ZeroMemory(&light, sizeof(light));
	light.Type = D3DLIGHT_DIRECTIONAL;							//ǥ�� '�¾籤'.

	switch (g_LightState)
	{
	case ls_NOON : 
		light.Diffuse = D3DXCOLOR(1, 1, 1, 1);
		if (g_bShowFrame) 
			g_BkColor = D3DXCOLOR(0.12f, 0.12f, 0.12f, 1);
		else
			g_BkColor = D3DXCOLOR(0.2, 0.5, 0.956, 1);
		g_cLightState = "����";
		if (IsKeyUp(VK_F11))
			g_LightState = ls_SUNSET;
		break;

	case ls_SUNSET:
		light.Diffuse = D3DXCOLOR(1, 0.65, 0.282, 1);
		if (g_bShowFrame)
			g_BkColor = D3DXCOLOR(0.12f, 0.12f, 0.12f, 1);
		else
			g_BkColor = D3DXCOLOR(1, 0.6, 0.2, 1);
		g_cLightState = "������... ����..";
		if (IsKeyUp(VK_F11))
			g_LightState = ls_MIDNIGHT;
		break;

	case ls_MIDNIGHT:
		light.Diffuse = D3DXCOLOR(0, 0, 0.005, 1);
		if (g_bShowFrame)
			g_BkColor = D3DXCOLOR(0.12f, 0.12f, 0.12f, 1);
		else
			g_BkColor = D3DXCOLOR(0.0, 0.0, 0.1, 1);
		g_cLightState = "���� �Ǿ����ϴ�.";
		if (IsKeyUp(VK_F11))
			g_LightState = ls_SUNRISE;
		break;

	case ls_SUNRISE:
		light.Diffuse = D3DXCOLOR(0.3, 0.3, 1, 1);
		if (g_bShowFrame)
			g_BkColor = D3DXCOLOR(0.12f, 0.12f, 0.12f, 1);
		else
			g_BkColor = D3DXCOLOR(0.3, 0.3, 0.7, 1);
		g_cLightState = "������ ���Ѿ�ħ!";
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
	light.Direction = D3DXVECTOR3(0.0f, -2.0f, 3.0f);			//�� ����.
	D3DXVec3Normalize((D3DXVECTOR3*)&light.Direction, (D3DXVECTOR3*)&light.Direction);

	g_pDevice->SetLight(0, &light);								//0�� ����Ʈ(����)�� ����.
	g_pDevice->LightEnable(0, TRUE);							//0�� ����Ʈ ON. FALSE�� ������ �ֺ������� ���´�.

	//---------------- 
	// �ֺ��� ����.
	//---------------- 
	if (g_bSpec)
		g_pDevice->SetRenderState(D3DRS_AMBIENT, D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f));		//30% ȸ�� : ǥ�� �ֺ���������

	//---------------- 
	// ����(ȶ��) ����.
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
	D3DXVec3TransformCoord((D3DXVECTOR3*)&Dotlight.Position, (D3DXVECTOR3*)&Dotlight.Position, &g_matLightTM);	// ������ ��ġ�� 
	Dotlight.Attenuation1 = 0.01;
	Dotlight.Attenuation2 = 0.05;

	g_pDevice->SetLight(1, &Dotlight);							//1�� ����Ʈ(����)�� ����.
	g_pDevice->LightEnable(1, g_bShowTorch);					//1�� ����Ʈ ON. 

	g_pDevice->SetRenderState(D3DRS_LIGHTING, g_bLightSwitch);

	//-------------------------------------------------------------------------- 
	// ����� �ٴ� ��� ���.
	//--------------------------------------------------------------------------  
	D3DXMatrixScaling(&g_pHero->bot.mScale, 2, 1, 2);
	g_pHero->bot.mRot = g_pHero->mRot;
	D3DXMatrixTranslation(&g_pHero->bot.mTrans, g_matLightTM._41, g_matLightTM._42 - 2.4, g_matLightTM._43);

	g_pHero->bot.mTM = g_pHero->bot.mScale * g_pHero->bot.mRot * g_pHero->bot.mTrans;

	//---------------- 
	// ���İ��� ���� ����.
	//---------------- 
	if (g_bAlphaB)
		g_cblendingState = "���� ���� [ON]";
	else
		g_cblendingState = "���� ���� [OFF]";

	if (g_bAlphaT)
		g_ctestingState = "���� �׽��� [ON]";
	else
		g_ctestingState = "���� �׽��� [OFF]";
}


// �� �� ���� ���� �ε�, �ʱ�ȭ.
int DataLoading()
{ 	
	InitVisibleNormal();
	
	CameraSetup();		//ī�޶� ����.

	HeroInit("PyLee", D3DXVECTOR3(0, 0, 0));	 //���ΰ� ����.
	BoxInit(D3DXVECTOR3(0, 1, -10));

	MapInit("TriWorld", D3DXVECTOR3(0, -0.05f, 0), D3DXVECTOR2(128, 128));	//���� ����.

	TreeInit();	// ����

	//ǳ��..
	WindmillInit(D3DXVECTOR3(5, 0, -15));	
	TripleWindmillInit(D3DXVECTOR3(0, 0, -15));
	TripleWindmillInit2(D3DXVECTOR3(-5, 0, -15));

	//��ü ����.
	D3DXCreateSphere(g_pDevice, 1.0f, 8, 8, &g_pTreeMeshSphere, NULL);
	D3DXCreateSphere(g_pDevice, 1.0f, 8, 8, &g_pWingMeshSphere, NULL);
	D3DXCreateSphere(g_pDevice, 1.0f, 8, 8, &g_pHeroMeshSphere, NULL);
	D3DXCreateSphere(g_pDevice, 0.2f, 8, 9, &g_pDotLightMesh, NULL);		// ���� ǥ�ÿ� ��ü

	//����� ����.
	PlaneInit(D3DXVECTOR3(0, 7, 0));
	DwarfInit(D3DXVECTOR3(10, 0, -10));

	LightsUpdate();		//���� ����.
	UpdateSeason();

	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
//
void DataRelease()
{
	HeroRelease();	//���ΰ� ����.	
	BoxRelease();
	
	MapRelease();	//���� ����
	
	TreeRelease();	//���� ����.
	
	WindmillRelease();	//ǳ�� ����.��

	TripleWindmillRelease(); // ��� ǳ�� ����.
	TripleWindmillRelease2();

	SAFE_RELEASE(g_pTreeMeshSphere); //DX �޽� ����.(�浹�� ǥ�ÿ�)��
	SAFE_RELEASE(g_pWingMeshSphere);
	SAFE_RELEASE(g_pHeroMeshSphere);
	SAFE_RELEASE(g_pDotLightMesh);

	ReleaseSeason();
	g_pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

}

void SceneStateUpdate(float dTime)
{
	if (IsKeyUp(VK_F4))g_bLightSwitch ^= TRUE;	//���� ON / OFF
	
	if (IsKeyUp(VK_F6))g_bShowNormal ^= TRUE;	//�븻 ǥ�� On/Off

	if (IsKeyUp(VK_F7))g_bShowTorch ^= TRUE;	//ȶ�� ON / OFF
	
	if (IsKeyUp(VK_F8))g_bShowBSphere ^= TRUE;	//�浹�� ǥ�� On/Off

	if (IsKeyUp('1'))g_pWindmill->bShowInnerLight ^= TRUE;			// �ǳ��� ON / OFF
	if (IsKeyUp('2'))g_pTripleWindmill2->bShowInnerLight ^= TRUE;	// �ǳ��� ON / OFF
	if (IsKeyUp('3'))g_pTripleWindmill->bShowInnerLight ^= TRUE;	// �ǳ��� ON / OFF


	if (IsKeyUp('9'))g_bAlphaB ^= TRUE;	// ���� ���� ON / OFF
	if (IsKeyUp('0'))g_bAlphaT ^= TRUE;	// ���� �׽�Ʈ ON / OFF

	if (IsKeyUp('4'))g_bSpec ^= TRUE; // �ݻ籤 (����ŧ��) ON / OFF
}


 

/////////////////////////////////////////////////////////////////////////////// 
//
//  ����. 
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
		DrawText(x, y, col, "�� %s", g_WindowName);  
		DrawText(x, y+=15, col, "> ǳ������ ���� ��� ��");
		DrawText(x, y+=15, col, "> W A S D, Q E"); 
		DrawText(x, y+=15, col, "> T F G H, R Y"); 
		DrawText(x, y += 15, col, "> I J K L, U O");
		DrawText(x, y += 15, col, "Spacular [ON / OFF] : '4' ");
	} 

	int x = 1, y = 20;
	D3DXCOLOR col(1, 1, 1, 1);
	
	SystemInfoShow(x, y, col);  //����-�ý��۵���.���.
	
	{   //���� ���򸻵�.
		x -= 1000;
		y += 80; 
		DrawText(x, y+=14, col, "[���̾�������] Space");
		DrawText(x, y += 14, col, "[���� - ���Ɽ] F4");
		DrawText(x, y += 14, col, "[���� ����] [9]");
		DrawText(x, y += 14, col, "[���� �׽���] [0]");
		DrawText(x, y += 14, col, "[ǳ�� �ǳ���] [1] [2] [3]");
		
		y += 14;
		DrawText(x, y+=28, col, "[Hero]");    
		DrawText(x, y += 14, col,"���� ����:F5");
		DrawText(x, y += 14, col, "�븻����:F6");
		DrawText(x, y += 14, col, "ȶ��:F7");
		DrawText(x, y += 14, col, "�浹��:F8");
		DrawText(x, y+=14, col, "����:F9");
		DrawText(x, y+=14, col, "Pos={%.2f, %.2f, %.2f}", g_pHero->vPos.x, g_pHero->vPos.y, g_pHero->vPos.z);   
		

	}

	x = 1000, y = 0;
	
	{   // ���� ����
		DrawText(x, y += 3, col, "[���� ����] F11");
		DrawText(x, y += 14, col, "[���� ����] F12");
		DrawText(x, y += 14, col, "���� ���� = %s", g_cLightState);
		DrawText(x, y += 14, col, "���� ���� = %s", g_pSnow->g_cSeasonState);
		DrawText(x, y += 14, col, "%s", g_cblendingState);
		DrawText(x, y += 14, col, "%s", g_ctestingState);
	}

}

void SamplingTest()
{
	for (int i = 0; i < 7; i++)
	{

		//Test #2-2: Mip-map : ��  
		g_pDevice->SetSamplerState(i, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);

		//Test #3.Anisotropic ��
	
		g_pDevice->SetSamplerState(i, D3DSAMP_MAGFILTER, D3DTEXF_ANISOTROPIC);
		g_pDevice->SetSamplerState(i, D3DSAMP_MINFILTER, D3DTEXF_ANISOTROPIC);

		//Anisotropic ���. (x1~ x16)
		g_pDevice->SetSamplerState(i, D3DSAMP_MAXANISOTROPY, 16); 				
	
	}

}

void LightsMeshDraw(float dTime)
{
	if (g_bShowTorch)
	{
		HeroBottomDraw(dTime);		// �� ���� ǥ��
		g_pDevice->SetTransform(D3DTS_WORLD, &g_matLightTM);
		g_pDotLightMesh->DrawSubset(0);
	}
}


////////////////////////////////////////////////////////////////////////////// 
//
// ��� �׸��� :  
// 
void SceneRender()
{ 
	//����- �ý��� ����. 
	float dTime = GetEngineTime();
	SystemUpdate(dTime);
	
	SceneStateUpdate(dTime);	//��� ������ ����(�ɼ�) ����.. ��

	HeroMove(dTime);	//���ΰ� '�̵�' 
	BoxUpdate(dTime);
	
	MapUpdate(dTime);	//�� ������Ʈ.	


	//ǳ�� ������Ʈ.
	WindmillUpdate(dTime);	
	TripleWindmillUpdate(dTime);
	TripleWindmillUpdate2(dTime);
	
	TreeUpdate(dTime);	//���� ������Ʈ.
						//(��Ÿ �������ų�, �ٶ��� ��鸮�ų�..����� ���º�ȭ..)

    PlaneUpdate(dTime); // ����� ������Ʈ
	DwarfUpdate(dTime);
	
	CameraUpdate();		//ī�޶� ������Ʈ.

	
	LightsUpdate();		//���� ������Ʈ.

	SamplingTest();
	

	// ��� �׸��� ����..
	//
	if(SUCCEEDED(g_pDevice->BeginScene()))		
	{
		g_pDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, g_BkColor, 1.0f, 0);

        PlaneDraw(dTime);
		DwarfDraw(dTime);

		//�׸��� �׸���..
		GridAxisDraw();				 

		//���(Scene) �׸���..
		
	 	HeroDraw(dTime);
		MapDraw(dTime);		

		//TreeDraw(dTime);		
		BoxDraw(dTime);


		//WindmillDraw(dTime);
		//TripleWindmillDraw(dTime);
		//TripleWindmillDraw2(dTime);

		if (g_pWindmill->bShowInnerLight)
			WindMillBottomDraw(dTime);	// �� �� ǥ��
		if (g_pTripleWindmill->bShowInnerLight)
			WindMillBottomDraw1(dTime);
		if (g_pTripleWindmill2->bShowInnerLight)
			WindMillBottomDraw2(dTime);
		LightsMeshDraw(dTime);		// ���� ǥ��

		UpdateSeason();
		//���� �浹�� �׸���.��
		if (g_bShowBSphere)
		{
			TreeBSphereDraw(dTime);
			WingBSphereDraw(dTime);
			HeroBSphereDraw(dTime);
		}

	
		//�ý��� ��ü & ���� ���..
		ShowInfo();					 
		g_pDevice->EndScene();
	}

	g_pDevice->Present(NULL, NULL, NULL, NULL);


}


/************ end of file "Render.cpp" ******************************/
