#include "d3dx9.h" 
#include "assert.h"

#include "Device.h"
#include "Render.h"

#include "Season.h"

Season g_SeasonState;
SNOW* g_pSnow = new SNOW;

void UpdateSeason()
{
	switch (g_SeasonState)
	{
	case Ss_SUMMER :
		g_pSnow->g_cSeasonState = "여름";
		if (IsKeyUp(VK_F12))
			g_SeasonState = Ss_AUTUMN;
		break;

	case Ss_AUTUMN :
		g_pSnow->g_cSeasonState = "가을";
		if (IsKeyUp(VK_F12))
			g_SeasonState = Ss_WINTER;
		break;

	case Ss_WINTER :
		g_pSnow->g_cSeasonState = "겨울";
		if (IsKeyUp(VK_F12))
			g_SeasonState = Ss_SUMMER;
		break;

	default :
		g_SeasonState = Ss_SUMMER;
		break;
	}
}

void SetSummer(LPDIRECT3DTEXTURE9 pTex)
{
	// <Stage 0> 텍스쳐 * 노란색
	g_pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);
	g_pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);		//알파 블랜딩 

	g_pDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
	g_pDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_CONSTANT);
	g_pDevice->SetTextureStageState(0, D3DTSS_CONSTANT, D3DXCOLOR(1, 1, 1, 1));
	g_pDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_TEXTURE);

	g_pDevice->SetTextureStageState(0, D3DTSS_TEXCOORDINDEX, 0);
	g_pDevice->SetTexture(0, g_bShowFrame ? NULL : pTex);

	// <Stage 1> 텍스쳐 * 디퓨즈
	g_pDevice->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_MODULATE);
	g_pDevice->SetTextureStageState(1, D3DTSS_COLORARG1, D3DTA_CURRENT);
	g_pDevice->SetTextureStageState(1, D3DTSS_COLORARG2, D3DTA_DIFFUSE);

	// <Stage 2> 사용 안함
	//g_pDevice->SetTextureStageState(2, D3DTSS_COLOROP, D3DTOP_DISABLE);

}

void SetAutumn(LPDIRECT3DTEXTURE9 pTex, int num)
{
	// <Stage 0> 텍스쳐 * 노란색
	g_pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);
	g_pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);		//알파 블랜딩 

	g_pDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
	g_pDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_CONSTANT);
	if (num == 0)
		g_pDevice->SetTextureStageState(0, D3DTSS_CONSTANT, D3DXCOLOR(0.85, 0.73, 0.2, 1));
	else if (num == 1)
		g_pDevice->SetTextureStageState(0, D3DTSS_CONSTANT, D3DXCOLOR(0.7, 0.2, 0.2, 1));
	g_pDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_TEXTURE);

	g_pDevice->SetTextureStageState(0, D3DTSS_TEXCOORDINDEX, 0);
	g_pDevice->SetTexture(0, g_bShowFrame ? NULL : pTex);

	// <Stage 1> 텍스쳐 * 디퓨즈
	g_pDevice->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_MODULATE);
	g_pDevice->SetTextureStageState(1, D3DTSS_COLORARG1, D3DTA_CURRENT);
	g_pDevice->SetTextureStageState(1, D3DTSS_COLORARG2, D3DTA_DIFFUSE);

	// <Stage 2> 사용 안함.
	//g_pDevice->SetTextureStageState(2, D3DTSS_COLOROP, D3DTOP_DISABLE);

}

void SetWinter(LPDIRECT3DTEXTURE9 pTex, int num)
{
	g_pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);
	g_pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);		//알파 블랜딩 

	g_pSnow->g_TextureName[0] = "./Data/TILE_mask2.png";
	D3DXCreateTextureFromFile(g_pDevice, g_pSnow->g_TextureName[0], &g_pSnow->pTex[0]);

	g_pSnow->g_TextureName[1] = "./Data/TREE_mask2.png";
	D3DXCreateTextureFromFile(g_pDevice, g_pSnow->g_TextureName[1], &g_pSnow->pTex[1]);

	g_pSnow->g_TextureName[2] = "./Data/WM_mask3.png";
	D3DXCreateTextureFromFile(g_pDevice, g_pSnow->g_TextureName[2], &g_pSnow->pTex[2]);
	
	// <Stage 0> 텍스쳐
	g_pDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_SELECTARG1);
	g_pDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);

	g_pDevice->SetTextureStageState(0, D3DTSS_TEXCOORDINDEX, 0);
	g_pDevice->SetTexture(0, g_bShowFrame ? NULL : pTex);

	// <Stage 1> 텍스쳐 + 마스크
	g_pDevice->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_ADD);
	g_pDevice->SetTextureStageState(1, D3DTSS_COLORARG1, D3DTA_CURRENT);
	g_pDevice->SetTextureStageState(1, D3DTSS_COLORARG2, D3DTA_TEXTURE);

	g_pDevice->SetTextureStageState(1, D3DTSS_TEXCOORDINDEX, 0);
	g_pDevice->SetTexture(1, g_bShowFrame ? NULL : g_pSnow->pTex[num]);

	// <Stage 2> 텍스쳐 * 디퓨즈
	g_pDevice->SetTextureStageState(2, D3DTSS_COLOROP, D3DTOP_MODULATE);
	g_pDevice->SetTextureStageState(2, D3DTSS_COLORARG1, D3DTA_CURRENT);
	g_pDevice->SetTextureStageState(2, D3DTSS_COLORARG2, D3DTA_DIFFUSE);

	//g_pDevice->SetTextureStageState(3, D3DTSS_COLOROP, D3DTOP_DISABLE);
}
//텍스처 스테이지 설정 : 기본값으로 전환
void SetDefault()
{
	g_pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);
	g_pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);		//알파 블랜딩 

	g_pDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
	g_pDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	g_pDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);

	g_pDevice->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_DISABLE);
}

void ReleaseSeason()
{
	SAFE_DELETE(g_pSnow);
}