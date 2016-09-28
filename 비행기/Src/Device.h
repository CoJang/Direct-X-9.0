//
// Device.h : D3D 기본 헤더 파일.
//
// 2003.11.4. Kihong Kim / mad_dog@hanmail.net
// 2004.05.07. Update
// 2005.09.23. Update (.Net)
//
#pragma once
#pragma warning(disable:4996)


#include "d3d9.h"
#include "d3dx9.h"
#include "dxerr.h"
#include "stdio.h"

HRESULT	DXSetup(HWND hwnd);
void	DXRelease(); 
 
float GetEngineTime();
void  PutFPS(int x, int y);
void  DrawText( int x, int y, D3DXCOLOR col, char* msg, ...);

void SystemUpdate(float dTime);
//void SystemInfoShow(); 
void SystemInfoShow(int& x, int&y, D3DXCOLOR col);


void CameraSetup();
void CameraUpdate();



#ifndef IsKeyDown
#define IsKeyDown(key)	((GetAsyncKeyState(key)&0x8000) == 0x8000)
#define IsKeyUp(key)	((GetAsyncKeyState(key)&0x8001) == 0x8001)
#endif


#ifndef SAFE_RELEASE
#define SAFE_RELEASE(pBuff) if((pBuff)){ (pBuff)->Release(); (pBuff) = NULL; }
#define SAFE_DELETE(pBuff)	if((pBuff)){ delete (pBuff); (pBuff) = NULL; }
#define SAFE_DELARRY(pBuff) if((pBuff)){ delete [] (pBuff); (pBuff) = NULL; }
#endif


extern LPDIRECT3DDEVICE9	g_pDevice;
extern HWND g_hWnd;
extern D3DDISPLAYMODE g_Mode; 

extern BOOL g_bShowFrame;
extern D3DXCOLOR g_BkColor;

extern float g_fZfar;									//시야 최대 거리 (300m)


////////////////////////////////////////////////////////////////////////////
//
// 추가 확장 헤더들.
//
/*//Yena 라이브러리 추가하기.<방법1> 직접 링크.
#include "B3Yena/Yena.h"
*/
//Yena 라이브러리 추가하기.<방법2> 프로젝트 속성에 폴더 지정.
//장점 : B3Yena 폴더를 직접 명시하지 않아도 됨, 각 소스별 헤더의 참조 및 복잡성이 제거됨.
// Project Properties > C/C++ > Additional Include Directories 에 다음 구문 추가 : ".\B3Yena"
//   
#include "Yena.h" 


/**************** end of "Device.h" ***********************************/