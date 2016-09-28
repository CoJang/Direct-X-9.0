//
// Render.h
//
// 2003.11.4. Kihong Kim / mad_dog@hanmail.net
// 2005.05.06. Update.

#pragma once
extern BOOL g_bShowNormal;
extern BOOL g_bAlphaB;
extern BOOL g_bAlphaT;

int		DataLoading();
void	DataRelease();

void	SceneRender();	
bool	LoadInitData(char* pPath, char* pMeshName);  // 외부파일에서 데이터 로드하기. 

extern LPDIRECT3DDEVICE9		g_pDevice;
/**************** end of "Render.h" ***********************************/