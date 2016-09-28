//
// Map.cpp
//
//
// 2007.01.25. Kihong Kim / mad_dog@hanmail.net
//
//
#include "d3dx9.h" 
#include "assert.h"
#include "Device.h"

#include "Windmill.h"
#include "Map.h"
#include "Vertex.h"
#include "Season.h"

////////////////////////////////////////////////////////////////////////////
//
MAP* g_pMap = NULL;
D3DMATERIAL9 g_MapMTL;

//�� ���� ������.
struct VTX_MAP
{
	D3DXVECTOR3		vPos;
	D3DXVECTOR3		vNormal;
	D3DXVECTOR2		vUV;
};
#define FVF_MAP (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1)


VTX_MAP  g_MeshMap[] = {

	{ D3DXVECTOR3(-0.5f, 0, 0.5f), D3DXVECTOR3(0, 1, 0), D3DXVECTOR2(0, 0)},  //R,G,B,A
	{ D3DXVECTOR3(0.5f, 0, 0.5f), D3DXVECTOR3(0, 1, 0), D3DXVECTOR2(8, 8) },
	{ D3DXVECTOR3(-0.5f, 0, -0.5f), D3DXVECTOR3(0, 1, 0), D3DXVECTOR2(0, 8) },
	{ D3DXVECTOR3(0.5f, 0, -0.5f), D3DXVECTOR3(0, 1, 0), D3DXVECTOR2(8, 0) },

};

LPDIRECT3DVERTEXBUFFER9	g_pVBMap = NULL;			//���� ���ۿ� ������.





////////////////////////////////////////////////////////////////////////////
//
int MapInit(char* name, D3DXVECTOR3 vPos, D3DXVECTOR2 vSize)
{
	g_pMap = new MAP;
	assert(g_pMap != NULL);


	g_pMap->vSize = vSize; 
	strcpy(g_pMap->Name, name);

	g_pMap->vPos = vPos;							//�� ������ġ..
	
	D3DXMatrixIdentity(&g_pMap->mTM);				//��� ������ �ʱ�ȭ.
	D3DXMatrixIdentity(&g_pMap->mRot);
	D3DXMatrixIdentity(&g_pMap->mScale);
	D3DXMatrixIdentity(&g_pMap->mTrans);

	ZeroMemory(&g_MapMTL, sizeof(g_MapMTL));
	g_MapMTL.Diffuse = { 1, 1, 1, 1 };
	g_MapMTL.Ambient = { 1, 1, 1, 1 };
	

	g_pMap->g_TextureName[0] = "./Data/ground.jpg";
	if (FAILED(D3DXCreateTextureFromFile(g_pDevice, g_pMap->g_TextureName[0], &g_pMap->pTex[0])))
	{
		MessageBox(NULL, "(��)�ؽ��� �ε� ����.", "����", MB_ICONERROR | MB_OK);
		return E_FAIL;
	}

	g_pMap->g_TextureName[1] = "./Data/TILE_mask2.png";
	D3DXCreateTextureFromFile(g_pDevice, g_pMap->g_TextureName[1], &g_pMap->pTex[1]);


	 
	//���� ���� ����.
	if(FAILED(g_pDevice->CreateVertexBuffer(
										sizeof(g_MeshMap),		
										0, 
										FVF_MAP,			
										D3DPOOL_MANAGED,	
										&g_pVBMap,			
										NULL)))
	{
		return E_FAIL;
	}

	//���� ä���.
	VOID*	pBuff;
 	if(FAILED(g_pVBMap->Lock(0, sizeof(g_MeshMap), (void**)&pBuff, 0 )))
	{
		return E_FAIL;
	}

	memcpy(pBuff, g_MeshMap, sizeof(g_MeshMap));
	g_pVBMap->Unlock();


	return TRUE;

}




////////////////////////////////////////////////////////////////////////////
//
void MapUpdate(float dTime)
{ 	 

	//�� Ű���.
	D3DXMatrixScaling(&g_pMap->mScale, 
						g_pMap->vSize.x,		//�� �� ���� ������.
						1, 
						g_pMap->vSize.y);		//�� �� ���� ������.

	// �̵� 
	D3DXMatrixTranslation(&g_pMap->mTrans, g_pMap->vPos.x, g_pMap->vPos.y, g_pMap->vPos.z );	
	
	D3DXMatrixMultiply(&g_pMap->mTM, &g_pMap->mScale, &g_pMap->mRot);		 
  	D3DXMatrixMultiply(&g_pMap->mTM, &g_pMap->mTM, &g_pMap->mTrans);		 
  
}



////////////////////////////////////////////////////////////////////////////
//
void MapDraw(float dTime)
{
	switch (g_SeasonState)
	{
	case Ss_SUMMER:
		SetSummer(g_pMap->pTex[0]);
		break;
	case Ss_AUTUMN:
		SetAutumn(g_pMap->pTex[0], 0);
		break;
	case Ss_WINTER:
		// <Stage 0> �ؽ���
		g_pDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_SELECTARG1);
		g_pDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
		g_pDevice->SetTexture(0, g_pMap->pTex[0]);

		// <Stage 1> �ؽ��� + ����ũ
		g_pDevice->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_ADD);
		g_pDevice->SetTextureStageState(1, D3DTSS_COLORARG1, D3DTA_CURRENT);
		g_pDevice->SetTextureStageState(1, D3DTSS_COLORARG2, D3DTA_TEXTURE);
		g_pDevice->SetTexture(1, g_pMap->pTex[1]);

		// <Stage 2> �ؽ��� * ��ǻ��
		g_pDevice->SetTextureStageState(2, D3DTSS_COLOROP, D3DTOP_MODULATE);
		g_pDevice->SetTextureStageState(2, D3DTSS_COLORARG1, D3DTA_CURRENT);
		g_pDevice->SetTextureStageState(2, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
		break;
	}
	
	//�� �޽��� ����̽��� ���. 
	g_pDevice->SetMaterial(&g_MapMTL);
	g_pDevice->SetStreamSource(0, g_pVBMap, 0, sizeof(VTX_MAP));	
	g_pDevice->SetFVF(FVF_MAP);												


	//���� "���� ���� ��ġ ���" 
 	g_pDevice->SetTransform(D3DTS_WORLD, &g_pMap->mTM);	
 	
	//�� �׸��� : �ﰢ���� 2��. ����.
	g_pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	//----------------------------------------------------------------
	//�ؽ�ó �������� ���� : �⺻������ ��ȯ
	g_pDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
	g_pDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	g_pDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);

	g_pDevice->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_DISABLE);
	//----------------------------------------------------------------


}










////////////////////////////////////////////////////////////////////////////
//
void MapRelease()
{	
	SAFE_RELEASE(g_pVBMap);		//��� ���� ������ ������... 
	SAFE_DELETE(g_pMap);		//�� ��ü ����...
}
















/****************** end of file "Map.h" ************************/
