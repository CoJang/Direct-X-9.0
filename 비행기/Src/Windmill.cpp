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

// ǳ�� ��ü : �Ƕ�̵� ����.
VERTEX g_MeshWindmill_Body[] = {
		
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

	//�ٴ�.  ( Face#1)
	{ D3DXVECTOR3(1.0, -1.0, 1.0), D3DXVECTOR3(0.0, 0.0, 0.0), D3DXVECTOR2(0.0, 0.0) },
	{ D3DXVECTOR3(-1.0, -1.0, 1.0), D3DXVECTOR3(0.0, 0.0, 0.0), D3DXVECTOR2(1.0, 0.0) },
	{ D3DXVECTOR3(-1.0, -1.0, -1.0), D3DXVECTOR3(0.0, 0.0, 0.0), D3DXVECTOR2(1.0, 1.0) },
	//		 ( Face#2)
	{ D3DXVECTOR3(1.0, -1.0, 1.0), D3DXVECTOR3(0.0, 0.0, 0.0), D3DXVECTOR2(0.0, 0.0) },
	{ D3DXVECTOR3(-1.0, -1.0, -1.0), D3DXVECTOR3(0.0, 0.0, 0.0), D3DXVECTOR2(1.0, 1.0) },
	{ D3DXVECTOR3(1.0, -1.0, -1.0), D3DXVECTOR3(0.0, 0.0, 0.0), D3DXVECTOR2(0.0, 1.0) },

};


LPDIRECT3DVERTEXBUFFER9	g_pVBWindmill_Body = NULL;		//���� ���ۿ� ������.(��ü)
LPDIRECT3DVERTEXBUFFER9	g_pVBWindmill_Wing = NULL;		//���� ���ۿ� ������.(����)
LPDIRECT3DVERTEXBUFFER9	g_pVBWindmill_Bottom = NULL;	//���� ���ۿ� ������.(�ٴ�)





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

	g_pWindmill->vPos = vPos;								//ǳ�� ���� ��ġ
	g_pWindmill->vRot = D3DXVECTOR3(0, 0, 0);				//ǳ�� ȸ�� ����.

	g_pWindmill->Bottom.vPos = vPos;								//ǳ�� ���� ��ġ
	g_pWindmill->Bottom.vRot = D3DXVECTOR3(0, 0, 0);				//ǳ�� ȸ�� ����.

	D3DXMatrixIdentity(&g_pWindmill->mTM);					// ���� ��� ������ �ʱ�ȭ.
	D3DXMatrixIdentity(&g_pWindmill->mRot);
	D3DXMatrixIdentity(&g_pWindmill->mScale);
	D3DXMatrixIdentity(&g_pWindmill->mTrans);

	D3DXMatrixIdentity(&g_pWindmill->Wing[0].mTM);			// ���� ��� ������ �ʱ�ȭ.
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
		MessageBox(NULL, "(�⺻ǳ��_����)�ؽ��� �ε� ����.", "����", MB_ICONERROR | MB_OK);
		return E_FAIL;
	}

	g_pWindmill->Wing->g_TextureName[1] = "./Data/WM_mask3.png";
	D3DXCreateTextureFromFile(g_pDevice, g_pWindmill->Wing->g_TextureName[1], &g_pWindmill->Wing->pTex[1]);

	g_pWindmill->Bottom.g_TextureName = "./Data/Lit.dds";
	D3DXCreateTextureFromFile(g_pDevice, g_pWindmill->Bottom.g_TextureName, &g_pWindmill->Bottom.pTex);

	// 
	// ǳ�� ��ü��. ���� ���� ����.
	//
	if(FAILED(g_pDevice->CreateVertexBuffer(
										sizeof(g_MeshWindmill_Body),	//��	
										0, 
										VERTEX::FVF,					//��
										D3DPOOL_MANAGED,	
										&g_pVBWindmill_Body,			//��
										NULL)))
	{
		return E_FAIL;
	}

	//���� ä���.
	VOID*	pBuff;
 	if(FAILED(g_pVBWindmill_Body->Lock(0, sizeof(g_MeshWindmill_Body), (void**)&pBuff, 0 )))
	{
		return E_FAIL;
	}

	memcpy(pBuff, g_MeshWindmill_Body, sizeof(g_MeshWindmill_Body));
	g_pVBWindmill_Body->Unlock();

	
	//
	// ǳ�� ������ ���� ���� ����.
	//
	if(FAILED(g_pDevice->CreateVertexBuffer(
										sizeof(g_MeshWindmill_Wing),	//��	
										0, 
										VERTEX::FVF,					//��
										D3DPOOL_MANAGED,	
										&g_pVBWindmill_Wing,			//��
										NULL)))
	{
		return E_FAIL;
	}

	//���� ä���.
  	if(FAILED(g_pVBWindmill_Wing->Lock(0, sizeof(g_MeshWindmill_Wing), (void**)&pBuff, 0 )))
	{
		return E_FAIL;
	}

	memcpy(pBuff, g_MeshWindmill_Wing, sizeof(g_MeshWindmill_Wing));
	g_pVBWindmill_Wing->Unlock();

	//
	// ǳ�� �ٴڿ� ���� ���� ����.
	//
	if (FAILED(g_pDevice->CreateVertexBuffer(
		sizeof(g_MeshWindMillBottom),	//��	
		0,
		VERTEX::FVF,					//��
		D3DPOOL_MANAGED,
		&g_pVBWindmill_Bottom,			//��
		NULL)))
	{
		return E_FAIL;
	}

	//���� ä���.
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
	// ǳ�� ��ü ��� ���.
	//--------------------------------------------------------------------------  

	// ǳ�� ��ü �̵�  
	static float mov = 10.0f;

	if (IsKeyDown('W'))		g_pWindmill->vPos.z += mov * dTime;
	if (IsKeyDown('S'))		g_pWindmill->vPos.z -= mov * dTime;
	if (IsKeyDown('D'))		g_pWindmill->vPos.x += mov * dTime;
	if (IsKeyDown('A'))		g_pWindmill->vPos.x -= mov * dTime;

	D3DXMatrixTranslation(&g_pWindmill->mTrans,
							g_pWindmill->vPos.x,
							g_pWindmill->vPos.y,
							g_pWindmill->vPos.z);		// ǳ�� ��ü �̵���� �����.	ó���� �ѹ��� ���. ��

	// ǳ�� ȸ��
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


	// 'ǳ�� ���� ��ȯ �� - TM -  ����ϱ� :  
	// 
	// BodyTM = S * R * T
 	//
	//g_pWindmill->mTM = g_pWindmill->mTrans;		
	D3DXMatrixMultiply(&g_pWindmill->mTM, &g_pWindmill->mScale, &g_pWindmill->mRot);
  	D3DXMatrixMultiply(&g_pWindmill->mTM, &g_pWindmill->mTM, &g_pWindmill->mTrans);	 


	//-------------------------------------------------------------------------- 
	// ���� ��� ���.
	//-------------------------------------------------------------------------- 
	// ���� ȸ�� �� ���. : ȸ�� ��� ����. 

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

	// ���� �̵� ��� �����. 
	D3DXMatrixTranslation(&g_pWindmill->Wing[0].mTrans,
							g_pWindmill->Wing[0].vPos.x,
							g_pWindmill->Wing[0].vPos.y,
							g_pWindmill->Wing[0].vPos.z);

	// D3DXMatrixInverse(&���� ���, NULL[�Ǻ���], &������� ���� �Լ�)

	// F5������ ���� ���� ��ġ�̵� �� ȸ����ȯ 						

	if (isHeroSelect == TRUE)
	{
		D3DXMatrixRotationX(&RotateWing, D3DXToRadian(90));		// ������ ����������� ������ ���� ���� ȸ������� ���� X������ 90�� ȸ������ �ִ´�.
		g_pWindmill->Wing[0].mRot *= RotateWing;						// ���� X�� ���� 90�� ȸ���ϴ� ȸ������� "����"�� ȸ����Ŀ� �����ش�.
		//(����� ���� �����ǥ. (0, 5, 0))
		g_pWindmill->Wing[0].vPos = D3DXVECTOR3(0, 5, 0);

	}
	else if (isHeroSelect == FALSE)
	{
		//(��ü���� �����ǥ. (0, 2, -1))
		g_pWindmill->Wing[0].vPos = D3DXVECTOR3(0, 2, -1.0f);
	}

	// ǳ�� ���� ���� TM
	// wingTM = S * R * T

	D3DXMatrixMultiply(&g_pWindmill->Wing[0].mTM, &g_pWindmill->Wing[0].mScale, &g_pWindmill->Wing[0].mRot);
	D3DXMatrixMultiply(&g_pWindmill->Wing[0].mTM, &g_pWindmill->Wing[0].mTM, &g_pWindmill->Wing[0].mTrans);		 


	//-------------------------------------------------------------------------- 
	// ǳ�� ������ �ٵ� ���̱�.��
	//-------------------------------------------------------------------------- 
	// wingLastTM = wingTM * BodyTM
	//
	if (isHeroSelect == TRUE)		// ��� ON�̸� ����� ����� ���Ͽ� ���δ�
		D3DXMatrixMultiply(&g_pWindmill->Wing[0].mTM, &g_pWindmill->Wing[0].mTM, &g_pHero->mTM);		
	if (isHeroSelect == FALSE)		// ��� OFF�̸� ǳ��[�ٵ�] ����� ���Ͽ� ���δ�
		D3DXMatrixMultiply(&g_pWindmill->Wing[0].mTM, &g_pWindmill->Wing[0].mTM, &g_pWindmill->mTM);

	//-------------------------------------------------------------------------- 
	// ǳ�� �ٴ� ��� ���.
	//--------------------------------------------------------------------------  
	D3DXMatrixScaling(&g_pWindmill->Bottom.mScale, 1.70, 1, 1.70);
	g_pWindmill->Bottom.mRot = g_pWindmill->mRot;
	D3DXMatrixTranslation(&g_pWindmill->Bottom.mTrans, g_pWindmill->vPos.x, g_pWindmill->vPos.y + 1, g_pWindmill->vPos.z);

	g_pWindmill->Bottom.mTM = g_pWindmill->Bottom.mScale * g_pWindmill->Bottom.mRot * g_pWindmill->Bottom.mTrans;
}


void WindMillBottomDraw(float dTime)
{
	g_pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, g_bAlphaT);		// ���� �׽�Ʈ ON / OFF!
	g_pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);			// ũ�ų� ������ ���.��
	g_pDevice->SetRenderState(D3DRS_ALPHAREF, (DWORD)(0.0 * 255));
	
	g_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, g_bAlphaB);			// ���� ���� ON! 
	g_pDevice->SetRenderState(D3DRS_SRCBLEND, D3DRS_BLENDFACTOR);			// ���
	g_pDevice->SetRenderState(D3DRS_BLENDFACTOR, D3DXCOLOR(0.25, 0.25, 0.25, 0.25));
	g_pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);				// ����ũ

	///////////////////////// ���� �� ////////////////////////////////

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
void WindmillDraw(float dTime)
{ 
	float alpha = 0.49f;

	if (g_bAlphaT)
	{
		g_pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
		g_pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);			//ũ�ų� ������ ���.��
		g_pDevice->SetRenderState(D3DRS_ALPHAREF, (DWORD)(alpha * 255));
	}

	if (g_bAlphaB)
	{
		g_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);			//���� ���� ON! 
		g_pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		// ���� ��� ���� : "���� ����" ����...��
		g_pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	}

	///////////////////////////////////// �� �ʸ�//////////////////////////////////////////////// 
	

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
		g_pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);		//���� ���� 
		g_pDevice->SetTexture(0, g_pWindmill->Wing->pTex[0]);
	}

	// ���� ��ü �׸���.
	g_pDevice->SetMaterial(&g_Windmill_MTL);
	g_pDevice->SetFVF(VERTEX::FVF);
	g_pDevice->SetStreamSource(0, g_pVBWindmill_Body, 0, sizeof VERTEX);	//��
  	g_pDevice->SetTransform(D3DTS_WORLD, &g_pWindmill->mTM);	
  	g_pDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 4);		
	DrawVisibleNormal(g_MeshWindmill_Body, _countof(g_MeshWindmill_Body));

	///////////////////////////////////// �� �ʸ�//////////////////////////////////////////////// 


	///////////////////////////////////// // �ٱ� �ʸ�///////////////////////////////////////////
	g_pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);					 

	if (g_pWindmill->bShowInnerLight)
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
	g_pDevice->SetMaterial(&g_Windmill_MTL);
	g_pDevice->SetFVF(VERTEX::FVF);
	g_pDevice->SetStreamSource(0, g_pVBWindmill_Body, 0, sizeof VERTEX);	//��
	g_pDevice->SetTransform(D3DTS_WORLD, &g_pWindmill->mTM);
	g_pDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 4);
	DrawVisibleNormal(g_MeshWindmill_Body, _countof(g_MeshWindmill_Body));

	g_pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);	// �ø� ��� OFF 

	///////////////////////////////////// // �ٱ� �ʸ�///////////////////////////////////////////

	// ���� �׸���.
	g_pDevice->SetMaterial(&g_WindmillWing_MTL);
	g_pDevice->SetFVF(VERTEX::FVF);
	g_pDevice->SetStreamSource(0, g_pVBWindmill_Wing, 0, sizeof VERTEX);	//��
	g_pDevice->SetTransform(D3DTS_WORLD, &g_pWindmill->Wing[0].mTM);		//������ TM(ȸ��..) ����.��
	g_pDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 8);						//���� �׸���.		
	DrawVisibleNormal(g_MeshWindmill_Wing, _countof(g_MeshWindmill_Wing));
 
	//----------------------------------------------------------------
	//�ؽ�ó �������� ���� : �⺻������ ��ȯ
	g_pDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
	g_pDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	g_pDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);

	g_pDevice->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_DISABLE);

	g_pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);	// ���� �׽�Ʈ OFF
	g_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);	// ���� ���� OFF
	//----------------------------------------------------------------
}










////////////////////////////////////////////////////////////////////////////
//
void WindmillRelease()
{	
	SAFE_RELEASE(g_pVBWindmill_Body);		//ǳ���� ���� ������ ������...��
	SAFE_RELEASE(g_pVBWindmill_Wing);		//ǳ���� ���� ������ ������...��
	SAFE_RELEASE(g_pVBWindmill_Bottom);

	SAFE_DELETE(g_pWindmill);			//ǳ�� ��ü ����...
}
















/****************** end of file "Windmill.h" ************************/
