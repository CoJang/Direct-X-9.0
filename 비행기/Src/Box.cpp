#include "d3dx9.h" 
#include "assert.h"
#include "Device.h"
#include "Windmill.h"

#include "Vertex.h"
#include "Normal.h"

#include "Box.h"
#include "Season.h"

BOX* g_pBox = NULL;

VERTEX  g_MeshBox[] = {

	{ D3DXVECTOR3(-1.0, 1.0, -1.0), D3DXVECTOR3(0.0, 0.0, -1.0), D3DXVECTOR2(0.0, 0.0), D3DXVECTOR2(0.0, 0.0) },
	{ D3DXVECTOR3(1.0, 1.0, -1.0), D3DXVECTOR3(0.0, 0.0, -1.0), D3DXVECTOR2(1.0, 0.0), D3DXVECTOR2(1.0, 0.0) },
	{ D3DXVECTOR3(-1.0, -1.0, -1.0), D3DXVECTOR3(0.0, 0.0, -1.0), D3DXVECTOR2(0.0, 1.0), D3DXVECTOR2(0.0, 1.0) },
	//       ( Face#1)
	{ D3DXVECTOR3(-1.0, -1.0, -1.0), D3DXVECTOR3(0.0, 0.0, -1.0), D3DXVECTOR2(0.0, 1.0), D3DXVECTOR2(0.0, 1.0) },
	{ D3DXVECTOR3(1.0, 1.0, -1.0), D3DXVECTOR3(0.0, 0.0, -1.0), D3DXVECTOR2(1.0, 0.0), D3DXVECTOR2(1.0, 0.0) },
	{ D3DXVECTOR3(1.0, -1.0, -1.0), D3DXVECTOR3(0.0, 0.0, -1.0), D3DXVECTOR2(1.0, 1.0), D3DXVECTOR2(1.0, 1.0) },

	//�޸�.  (Face#3) :  
	{ D3DXVECTOR3(1.0, 1.0, 1.0), D3DXVECTOR3(0.0, 0.0, 1.0), D3DXVECTOR2(0.0, 0.0), D3DXVECTOR2(0.0, 0.0) },
	{ D3DXVECTOR3(-1.0, 1.0, 1.0), D3DXVECTOR3(0.0, 0.0, 1.0), D3DXVECTOR2(1.0, 0.0), D3DXVECTOR2(1.0, 0.0) },
	{ D3DXVECTOR3(-1.0, -1.0, 1.0), D3DXVECTOR3(0.0, 0.0, 1.0), D3DXVECTOR2(1.0, 1.0), D3DXVECTOR2(1.0, 1.0) }, /////////
	//		  (Face#4)
	{ D3DXVECTOR3(1.0, 1.0, 1.0), D3DXVECTOR3(0.0, 0.0, 1.0), D3DXVECTOR2(0.0, 0.0), D3DXVECTOR2(0.0, 0.0) },
	{ D3DXVECTOR3(-1.0, -1.0, 1.0), D3DXVECTOR3(0.0, 0.0, 1.0), D3DXVECTOR2(1.0, 1.0), D3DXVECTOR2(1.0, 1.0) },
	{ D3DXVECTOR3(1.0, -1.0, 1.0), D3DXVECTOR3(0.0, 0.0, 1.0), D3DXVECTOR2(0.0, 1.0), D3DXVECTOR2(0.0, 1.0) },


	// ������. (Face#5)
	{ D3DXVECTOR3(1.0, 1.0, -1.0), D3DXVECTOR3(1.0, 0.0, 0.0), D3DXVECTOR2(0.0, 0.0), D3DXVECTOR2(0.0, 0.0)},
	{ D3DXVECTOR3(1.0, 1.0, 1.0), D3DXVECTOR3(1.0, 0.0, 0.0), D3DXVECTOR2(1.0, 0.0), D3DXVECTOR2(1.0, 0.0) },
	{ D3DXVECTOR3(1.0, -1.0, -1.0), D3DXVECTOR3(1.0, 0.0, 0.0), D3DXVECTOR2(0.0, 1.0), D3DXVECTOR2(0.0, 1.0) },
	//			(Face#6)
	{ D3DXVECTOR3(1.0, -1.0, -1.0), D3DXVECTOR3(1.0, 0.0, 0.0), D3DXVECTOR2(0.0, 1.0), D3DXVECTOR2(0.0, 1.0) },
	{ D3DXVECTOR3(1.0, 1.0, 1.0), D3DXVECTOR3(1.0, 0.0, 0.0), D3DXVECTOR2(1.0, 0.0), D3DXVECTOR2(1.0, 0.0) },
	{ D3DXVECTOR3(1.0, -1.0, 1.0), D3DXVECTOR3(1.0, 0.0, 0.0), D3DXVECTOR2(1.0, 1.0), D3DXVECTOR2(1.0, 1.0) },


	// ������. (Face#7)
	{ D3DXVECTOR3(-1.0, 1.0, 1.0), D3DXVECTOR3(-1.0, 0.0, 0.0), D3DXVECTOR2(0.0, 0.0), D3DXVECTOR2(0.0, 0.0) },
	{ D3DXVECTOR3(-1.0, 1.0, -1.0), D3DXVECTOR3(-1.0, 0.0, 0.0), D3DXVECTOR2(1.0, 0.0), D3DXVECTOR2(1.0, 0.0) },
	{ D3DXVECTOR3(-1.0, -1.0, -1.0), D3DXVECTOR3(-1.0, 0.0, 0.0), D3DXVECTOR2(1.0, 1.0), D3DXVECTOR2(1.0, 1.0) },
	//			(Face#8)
	{ D3DXVECTOR3(-1.0, 1.0, 1.0), D3DXVECTOR3(-1.0, 0.0, 0.0), D3DXVECTOR2(0.0, 0.0), D3DXVECTOR2(0.0, 0.0) },
	{ D3DXVECTOR3(-1.0, -1.0, -1.0), D3DXVECTOR3(-1.0, 0.0, 0.0), D3DXVECTOR2(1.0, 1.0), D3DXVECTOR2(1.0, 1.0) },
	{ D3DXVECTOR3(-1.0, -1.0, 1.0), D3DXVECTOR3(-1.0, 0.0, 0.0), D3DXVECTOR2(0.0, 1.0), D3DXVECTOR2(0.0, 1.0) },


	//���.  ( Face#9)
	{ D3DXVECTOR3(-1.0, 1.0, 1.0), D3DXVECTOR3(0.0, 1.0, 0.0), D3DXVECTOR2(0.0, 0.0), D3DXVECTOR2(0.0, 0.0) },
	{ D3DXVECTOR3(1.0, 1.0, 1.0), D3DXVECTOR3(0.0, 1.0, 0.0), D3DXVECTOR2(1.0, 0.0), D3DXVECTOR2(1.0, 0.0) },
	{ D3DXVECTOR3(-1.0, 1.0, -1.0), D3DXVECTOR3(0.0, 1.0, 0.0), D3DXVECTOR2(0.0, 1.0), D3DXVECTOR2(0.0, 1.0) },
	//		 ( Face#10)
	{ D3DXVECTOR3(-1.0, 1.0, -1.0), D3DXVECTOR3(0.0, 1.0, 0.0), D3DXVECTOR2(0.0, 1.0), D3DXVECTOR2(0.0, 1.0) },
	{ D3DXVECTOR3(1.0, 1.0, 1.0), D3DXVECTOR3(0.0, 1.0, 0.0), D3DXVECTOR2(1.0, 0.0), D3DXVECTOR2(1.0, 0.0) },
	{ D3DXVECTOR3(1.0, 1.0, -1.0), D3DXVECTOR3(0.0, 1.0, 0.0), D3DXVECTOR2(1.0, 1.0), D3DXVECTOR2(1.0, 1.0) },


	//�Ϻ�.  ( Face#11)
	{ D3DXVECTOR3(1.0, -1.0, 1.0), D3DXVECTOR3(0.0, -1.0, 0.0), D3DXVECTOR2(0.0, 0.0), D3DXVECTOR2(0.0, 0.0) },
	{ D3DXVECTOR3(-1.0, -1.0, 1.0), D3DXVECTOR3(0.0, -1.0, 0.0), D3DXVECTOR2(1.0, 0.0), D3DXVECTOR2(1.0, 0.0) },
	{ D3DXVECTOR3(-1.0, -1.0, -1.0), D3DXVECTOR3(0.0, -1.0, 0.0), D3DXVECTOR2(1.0, 1.0), D3DXVECTOR2(1.0, 1.0) },
	//		 ( Face#12)
	{ D3DXVECTOR3(1.0, -1.0, 1.0), D3DXVECTOR3(0.0, -1.0, 0.0), D3DXVECTOR2(0.0, 0.0), D3DXVECTOR2(0.0, 0.0) },
	{ D3DXVECTOR3(-1.0, -1.0, -1.0), D3DXVECTOR3(0.0, -1.0, 0.0), D3DXVECTOR2(1.0, 1.0), D3DXVECTOR2(1.0, 1.0) },
	{ D3DXVECTOR3(1.0, -1.0, -1.0), D3DXVECTOR3(0.0, -1.0, 0.0), D3DXVECTOR2(0.0, 1.0), D3DXVECTOR2(0.0, 1.0) },

};


//���� ���ۿ� ������.
LPDIRECT3DVERTEXBUFFER9	g_pVBox = NULL;

CHAR* TempTextureName[3];
LPDIRECT3DTEXTURE9 pTempTex[3];

////////////////////////////////////////////////////////////////////////////
//
int BoxInit(D3DXVECTOR3 vPos)
{
	g_pBox = new BOX;
	assert(g_pBox != NULL);

	g_pBox->vPos = vPos;								
	g_pBox->vDir = D3DXVECTOR3(0, 0, -1);				
	
	D3DXMatrixIdentity(&g_pBox->mTM);					
	D3DXMatrixIdentity(&g_pBox->mRot);
	D3DXMatrixIdentity(&g_pBox->mScale);
	D3DXMatrixIdentity(&g_pBox->mTrans);

	D3DXMatrixScaling(&g_pBox->mScale, 1.0f, 1.0f, 1.0f);

	for (int i = 0; i < _countof(g_MeshBox); ++i)
		D3DXVec3Normalize(&g_MeshBox[i].vNormal, &g_MeshBox[i].vNormal);

	ZeroMemory(&g_pBox->Material, sizeof(g_pBox->Material));
	g_pBox->Material.Diffuse = { 1, 1, 1, 1 };
	g_pBox->Material.Ambient = { 0.4f, 0.4f, 0.4f, 1 };
	g_pBox->Material.Specular = { 1, 1, 1, 1 };
	g_pBox->Material.Power = 800.f;
	
	g_pBox->g_TextureName = "./Data/woodbox.bmp";

	if (FAILED(D3DXCreateTextureFromFile(g_pDevice, g_pBox->g_TextureName, &g_pBox->pTex)))
	{
		MessageBox(NULL, "(�ڽ�)�ؽ��� �ε� ����.", "����", MB_ICONERROR | MB_OK);
		return E_FAIL;
	}


	TempTextureName[0] = "./Data/Grass.jpg";
	D3DXCreateTextureFromFile(g_pDevice, TempTextureName[0], &pTempTex[0]);

	TempTextureName[1] = "./Data/BOX_Mask2.bmp";
	D3DXCreateTextureFromFile(g_pDevice, TempTextureName[1], &pTempTex[1]);
	
	TempTextureName[2] = "./Data/BOX_snow_mask2.png";
	D3DXCreateTextureFromFile(g_pDevice, TempTextureName[2], &pTempTex[2]);

	//���� ���� ����.
	if(FAILED(g_pDevice->CreateVertexBuffer(
										sizeof(g_MeshBox),		
										0, 
										VERTEX::FVF,			
										D3DPOOL_MANAGED,	
										&g_pVBox,			
										NULL)))
	{
		return E_FAIL;
	}

	//���� ä���.
	VOID*	pBuff;
 	if(FAILED(g_pVBox->Lock(0, sizeof(g_MeshBox), (void**)&pBuff, 0 )))
	{
		return E_FAIL;
	}
	memcpy(pBuff, g_MeshBox, sizeof(g_MeshBox));
	g_pVBox->Unlock();

	return TRUE;
}


////////////////////////////////////////////////////////////////////////////
//
void BoxUpdate(float dTime)
{
	D3DXVec3Normalize(&g_pBox->vDir, &g_pBox->vDir);
	D3DXMatrixTranslation(&g_pBox->mTrans, g_pBox->vPos.x, g_pBox->vPos.y, g_pBox->vPos.z);	

	g_pBox->mTM = g_pBox->mScale * g_pBox->mRot * g_pBox->mTrans;
}


////////////////////////////////////////////////////////////////////////////
//
void BoxDraw(float dTime)
{ 
	switch (g_SeasonState)
	{
	case Ss_SUMMER:

		// <Stage 0> ����ũ ����
		g_pDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_SUBTRACT);
		g_pDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_CONSTANT);
		g_pDevice->SetTextureStageState(0, D3DTSS_CONSTANT, D3DXCOLOR(1, 1, 1, 1));
		g_pDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_TEXTURE);

		g_pDevice->SetTextureStageState(0, D3DTSS_TEXCOORDINDEX, 0);
		g_pDevice->SetTexture(0, pTempTex[1]);			// ����ũ

		// <Stage 1> ����ũ ���� * ���� ����
		g_pDevice->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_MODULATE);
		g_pDevice->SetTextureStageState(1, D3DTSS_COLORARG1, D3DTA_CURRENT);
		g_pDevice->SetTextureStageState(1, D3DTSS_COLORARG2, D3DTA_TEXTURE);

		g_pDevice->SetTextureStageState(1, D3DTSS_TEXCOORDINDEX, 0);
		g_pDevice->SetTexture(1, g_bShowFrame ? NULL : g_pBox->pTex);			// ���� ����

		g_pDevice->SetTextureStageState(1, D3DTSS_RESULTARG, D3DTA_TEMP);	// Temp�� ����

		// <Stage 2> Ǯ CURRENT�� ����
		g_pDevice->SetTextureStageState(2, D3DTSS_COLOROP, D3DTOP_SELECTARG1);
		g_pDevice->SetTextureStageState(2, D3DTSS_COLORARG1, D3DTA_TEXTURE);

		g_pDevice->SetTextureStageState(2, D3DTSS_RESULTARG, D3DTA_CURRENT);	// �ٽ� Temp -> CURRENT
		g_pDevice->SetTextureStageState(2, D3DTSS_TEXCOORDINDEX, 0);
		g_pDevice->SetTexture(2, pTempTex[0]);			// Ǯ

		// <Stage 3> ����ũ * Ǯ
		g_pDevice->SetTextureStageState(3, D3DTSS_COLOROP, D3DTOP_MODULATE);
		g_pDevice->SetTextureStageState(3, D3DTSS_COLORARG1, D3DTA_TEXTURE);
		g_pDevice->SetTextureStageState(3, D3DTSS_COLORARG2, D3DTA_CURRENT);

		g_pDevice->SetTextureStageState(3, D3DTSS_TEXCOORDINDEX, 0);
		g_pDevice->SetTexture(3, pTempTex[1]);			// ����ũ

		// <Stage 4> (����ũ ���� * ���� ����) + (����ũ * Ǯ)
		g_pDevice->SetTextureStageState(4, D3DTSS_COLOROP, D3DTOP_ADD);
		g_pDevice->SetTextureStageState(4, D3DTSS_COLORARG1, D3DTA_CURRENT);
		g_pDevice->SetTextureStageState(4, D3DTSS_COLORARG2, D3DTA_TEMP);

		// <Stage 5> [(����ũ ���� * ���� ����) + (����ũ * Ǯ) * ����] 
		g_pDevice->SetTextureStageState(5, D3DTSS_COLOROP, D3DTOP_MODULATE);
		g_pDevice->SetTextureStageState(5, D3DTSS_COLORARG1, D3DTA_CURRENT);
		g_pDevice->SetTextureStageState(5, D3DTSS_COLORARG2, D3DTA_DIFFUSE);

		// <Stage 6> ��� ����.
		g_pDevice->SetTextureStageState(6, D3DTSS_COLOROP, D3DTOP_DISABLE);
		break;
	case Ss_AUTUMN:
		// <Stage 0> ����ũ ����
		g_pDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_SUBTRACT);
		g_pDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_CONSTANT);
		g_pDevice->SetTextureStageState(0, D3DTSS_CONSTANT, D3DXCOLOR(1, 1, 1, 1));
		g_pDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_TEXTURE);

		g_pDevice->SetTextureStageState(0, D3DTSS_TEXCOORDINDEX, 0);
		g_pDevice->SetTexture(0, pTempTex[1]);			// ����ũ

		// <Stage 1> ����ũ ���� * ���� ����
		g_pDevice->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_MODULATE);
		g_pDevice->SetTextureStageState(1, D3DTSS_COLORARG1, D3DTA_CURRENT);
		g_pDevice->SetTextureStageState(1, D3DTSS_COLORARG2, D3DTA_TEXTURE);

		g_pDevice->SetTextureStageState(1, D3DTSS_TEXCOORDINDEX, 0);
		g_pDevice->SetTexture(1, g_bShowFrame ? NULL : g_pBox->pTex);			// ���� ����

		g_pDevice->SetTextureStageState(1, D3DTSS_RESULTARG, D3DTA_TEMP);	// Temp�� ����

		// <Stage 2> Ǯ CURRENT�� ����
		g_pDevice->SetTextureStageState(2, D3DTSS_COLOROP, D3DTOP_MODULATE);
		g_pDevice->SetTextureStageState(2, D3DTSS_COLORARG1, D3DTA_CONSTANT);
		g_pDevice->SetTextureStageState(2, D3DTSS_CONSTANT, D3DXCOLOR(1, 0.73, 0, 1));
		g_pDevice->SetTextureStageState(2, D3DTSS_COLORARG2, D3DTA_TEXTURE);

		g_pDevice->SetTextureStageState(2, D3DTSS_RESULTARG, D3DTA_CURRENT);	// �ٽ� Temp -> CURRENT
		g_pDevice->SetTextureStageState(2, D3DTSS_TEXCOORDINDEX, 0);
		g_pDevice->SetTexture(2, pTempTex[0]);			// Ǯ

		// <Stage 3> ����ũ * Ǯ
		g_pDevice->SetTextureStageState(3, D3DTSS_COLOROP, D3DTOP_MODULATE);
		g_pDevice->SetTextureStageState(3, D3DTSS_COLORARG1, D3DTA_TEXTURE);
		g_pDevice->SetTextureStageState(3, D3DTSS_COLORARG2, D3DTA_CURRENT);

		g_pDevice->SetTextureStageState(3, D3DTSS_TEXCOORDINDEX, 0);
		g_pDevice->SetTexture(3, pTempTex[1]);			// ����ũ

		// <Stage 4> (����ũ ���� * ���� ����) + (����ũ * Ǯ)
		g_pDevice->SetTextureStageState(4, D3DTSS_COLOROP, D3DTOP_ADD);
		g_pDevice->SetTextureStageState(4, D3DTSS_COLORARG1, D3DTA_CURRENT);
		g_pDevice->SetTextureStageState(4, D3DTSS_COLORARG2, D3DTA_TEMP);

		// <Stage 5> [(����ũ ���� * ���� ����) + (����ũ * Ǯ) * ����] 
		g_pDevice->SetTextureStageState(5, D3DTSS_COLOROP, D3DTOP_MODULATE);
		g_pDevice->SetTextureStageState(5, D3DTSS_COLORARG1, D3DTA_CURRENT);
		g_pDevice->SetTextureStageState(5, D3DTSS_COLORARG2, D3DTA_DIFFUSE);

		// <Stage 6> ��� ����.
		g_pDevice->SetTextureStageState(6, D3DTSS_COLOROP, D3DTOP_DISABLE);
		break;
		
	case Ss_WINTER:
		// <Stage 0> ����ũ ����
		g_pDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_SUBTRACT);
		g_pDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_CONSTANT);
		g_pDevice->SetTextureStageState(0, D3DTSS_CONSTANT, D3DXCOLOR(1, 1, 1, 1));
		g_pDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_TEXTURE);

		g_pDevice->SetTextureStageState(0, D3DTSS_TEXCOORDINDEX, 0);
		g_pDevice->SetTexture(0, pTempTex[1]);			// ����ũ

		// <Stage 1> ����ũ ���� * ���� ����
		g_pDevice->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_MODULATE);
		g_pDevice->SetTextureStageState(1, D3DTSS_COLORARG1, D3DTA_CURRENT);
		g_pDevice->SetTextureStageState(1, D3DTSS_COLORARG2, D3DTA_TEXTURE);

		//g_pDevice->SetTextureStageState(1, D3DTSS_TEXCOORDINDEX, 0);
		g_pDevice->SetTexture(1, g_bShowFrame ? NULL : g_pBox->pTex);			// ���� ����

		g_pDevice->SetTextureStageState(1, D3DTSS_RESULTARG, D3DTA_TEMP);	// Temp�� ����

		// <Stage 2> Ǯ CURRENT�� ����
		g_pDevice->SetTextureStageState(2, D3DTSS_COLOROP, D3DTOP_MODULATE);
		g_pDevice->SetTextureStageState(2, D3DTSS_COLORARG1, D3DTA_CONSTANT);
		g_pDevice->SetTextureStageState(2, D3DTSS_CONSTANT, D3DXCOLOR(1, 0.73, 0, 1));
		g_pDevice->SetTextureStageState(2, D3DTSS_COLORARG2, D3DTA_TEXTURE);

		g_pDevice->SetTextureStageState(2, D3DTSS_RESULTARG, D3DTA_CURRENT);	// �ٽ� Temp -> CURRENT
		g_pDevice->SetTextureStageState(2, D3DTSS_TEXCOORDINDEX, 0);
		g_pDevice->SetTexture(2, pTempTex[0]);			// Ǯ

		// <Stage 3> ����ũ * Ǯ
		g_pDevice->SetTextureStageState(3, D3DTSS_COLOROP, D3DTOP_MODULATE);
		g_pDevice->SetTextureStageState(3, D3DTSS_COLORARG1, D3DTA_TEXTURE);
		g_pDevice->SetTextureStageState(3, D3DTSS_COLORARG2, D3DTA_CURRENT);

		g_pDevice->SetTextureStageState(3, D3DTSS_TEXCOORDINDEX, 0);
		g_pDevice->SetTexture(3, pTempTex[1]);			// ����ũ

		// <Stage 4> (����ũ ���� * ���� ����) + (����ũ * Ǯ)
		g_pDevice->SetTextureStageState(4, D3DTSS_COLOROP, D3DTOP_ADD);
		g_pDevice->SetTextureStageState(4, D3DTSS_COLORARG1, D3DTA_CURRENT);
		g_pDevice->SetTextureStageState(4, D3DTSS_COLORARG2, D3DTA_TEMP);

		// <Stage 5> �� ����ũ * [(����ũ ���� * ���� ����) + (����ũ * Ǯ)]
		g_pDevice->SetTextureStageState(5, D3DTSS_COLOROP, D3DTOP_ADD);
		g_pDevice->SetTextureStageState(5, D3DTSS_COLORARG1, D3DTA_TEXTURE);
		g_pDevice->SetTextureStageState(5, D3DTSS_COLORARG2, D3DTA_CURRENT);

		g_pDevice->SetTextureStageState(5, D3DTSS_TEXCOORDINDEX, 1);
		g_pDevice->SetTexture(5, g_bShowFrame ? NULL : pTempTex[2]);	// �� ����ũ

		// <Stage 6> {�� ����ũ * [(����ũ ���� * ���� ����) + (����ũ * Ǯ)]} * ����
		g_pDevice->SetTextureStageState(6, D3DTSS_COLOROP, D3DTOP_MODULATE);
		g_pDevice->SetTextureStageState(6, D3DTSS_COLORARG1, D3DTA_CURRENT);
		g_pDevice->SetTextureStageState(6, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
		 
		//<Stage 7> ��� ����
		g_pDevice->SetTextureStageState(7, D3DTSS_COLOROP, D3DTOP_DISABLE);
		break;
	}
	

	///////////////////////////////////////////////////////////////////////
	g_pDevice->SetFVF(VERTEX::FVF);				
	g_pDevice->SetStreamSource(0, g_pVBox, 0, sizeof(VERTEX)); 
	g_pDevice->SetTransform(D3DTS_WORLD, &g_pBox->mTM);	
	
	g_pDevice->SetMaterial(&g_pBox->Material);
	g_pDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 12); 
	
	DrawVisibleNormal(g_MeshBox, _countof(g_MeshBox));


	//----------------------------------------------------------------
	//�ؽ�ó �������� ���� : �⺻������ ��ȯ
	g_pDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);		
	g_pDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);		
	g_pDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);		 

	g_pDevice->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_DISABLE);			// 1�̻� �Ƚ��.

	//----------------------------------------------------------------
}


///////////////////////////////////////////////////////////////////////////
//
void BoxRelease()
{	
	SAFE_RELEASE(g_pVBox);
	SAFE_DELETE(g_pBox);	
}



/****************** end of file "Box.h" ************************/
