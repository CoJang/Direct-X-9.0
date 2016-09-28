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

//멥 정점 데이터.
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

LPDIRECT3DVERTEXBUFFER9	g_pVBMap = NULL;			//정점 버퍼용 포인터.





////////////////////////////////////////////////////////////////////////////
//
int MapInit(char* name, D3DXVECTOR3 vPos, D3DXVECTOR2 vSize)
{
	g_pMap = new MAP;
	assert(g_pMap != NULL);


	g_pMap->vSize = vSize; 
	strcpy(g_pMap->Name, name);

	g_pMap->vPos = vPos;							//멥 시작위치..
	
	D3DXMatrixIdentity(&g_pMap->mTM);				//행렬 변수의 초기화.
	D3DXMatrixIdentity(&g_pMap->mRot);
	D3DXMatrixIdentity(&g_pMap->mScale);
	D3DXMatrixIdentity(&g_pMap->mTrans);

	ZeroMemory(&g_MapMTL, sizeof(g_MapMTL));
	g_MapMTL.Diffuse = { 1, 1, 1, 1 };
	g_MapMTL.Ambient = { 1, 1, 1, 1 };
	

	g_pMap->g_TextureName[0] = "./Data/ground.jpg";
	if (FAILED(D3DXCreateTextureFromFile(g_pDevice, g_pMap->g_TextureName[0], &g_pMap->pTex[0])))
	{
		MessageBox(NULL, "(맵)텍스쳐 로드 실패.", "에러", MB_ICONERROR | MB_OK);
		return E_FAIL;
	}

	g_pMap->g_TextureName[1] = "./Data/TILE_mask2.png";
	D3DXCreateTextureFromFile(g_pDevice, g_pMap->g_TextureName[1], &g_pMap->pTex[1]);


	 
	//정점 버퍼 생성.
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

	//버퍼 채우기.
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

	//멥 키우기.
	D3DXMatrixScaling(&g_pMap->mScale, 
						g_pMap->vSize.x,		//멥 의 가로 사이즈.
						1, 
						g_pMap->vSize.y);		//멥 의 세로 사이즈.

	// 이동 
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
		// <Stage 0> 텍스쳐
		g_pDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_SELECTARG1);
		g_pDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
		g_pDevice->SetTexture(0, g_pMap->pTex[0]);

		// <Stage 1> 텍스쳐 + 마스크
		g_pDevice->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_ADD);
		g_pDevice->SetTextureStageState(1, D3DTSS_COLORARG1, D3DTA_CURRENT);
		g_pDevice->SetTextureStageState(1, D3DTSS_COLORARG2, D3DTA_TEXTURE);
		g_pDevice->SetTexture(1, g_pMap->pTex[1]);

		// <Stage 2> 텍스쳐 * 디퓨즈
		g_pDevice->SetTextureStageState(2, D3DTSS_COLOROP, D3DTOP_MODULATE);
		g_pDevice->SetTextureStageState(2, D3DTSS_COLORARG1, D3DTA_CURRENT);
		g_pDevice->SetTextureStageState(2, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
		break;
	}
	
	//맵 메쉬를 디바이스에 등록. 
	g_pDevice->SetMaterial(&g_MapMTL);
	g_pDevice->SetStreamSource(0, g_pVBMap, 0, sizeof(VTX_MAP));	
	g_pDevice->SetFVF(FVF_MAP);												


	//맵의 "월드 공간 위치 등록" 
 	g_pDevice->SetTransform(D3DTS_WORLD, &g_pMap->mTM);	
 	
	//맵 그리기 : 삼각형이 2개. 주의.
	g_pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	//----------------------------------------------------------------
	//텍스처 스테이지 설정 : 기본값으로 전환
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
	SAFE_RELEASE(g_pVBMap);		//멥용 정점 데이터 릴리즈... 
	SAFE_DELETE(g_pMap);		//멥 객체 제거...
}
















/****************** end of file "Map.h" ************************/
