/////////////////////////////////////////////////////////////////////////////
//                                                                         //
//  B3D/YENA : DirectX 를 이용한 하드웨어 가속 2D/3D 엔진.                 // 
//                                                                         //
//  제 작 : Kihong Kim / mad_dog@hanmail.net                               // 
//          Zero-G Tech,Inc http://www.zero-g.kr						   //	
//  초기제작 : 2003.12 - 2004.03.                                          //
//  개발환경 : OS - Windows 2k SP4 / Visual Studio 6.0/2003/2005/2008      //
//                  DirectX 9.0b(2003, summer)                             //
//                  DirectX 9.0b(2007, November)                           //
//             H/W - AMD Athlon XP(Barton) 2500+@2300                      //    
//                   ATI Radeon 9600 Pro                                   //
//                   ABit NF7-II /w SAMSUNG DDR 512MB                      //
//                   SB Live! DE 5.1                                       //
//  테스트 환경 : CPU - AMD Athlon										   //	 
//                      AMD Athlonx64 w/q4                                 // 
//                      Intel Pentium III/IV & Celeron                     //
//                      Core2 w/Quad                                       //
//                VGA - ATI Radeon 9xxx Series                             //
//                          Radeon 1xxx Series                             //
//                          Radeon HD 3/4/5/6 Series                       //
//                      nVidia GeForce 2 MX/Ti Series.                     //  
//                             GeForce 3 Ti Series.                        //
//                             GeForce 4 MX/Ti Series.                     //
//                             GeForce FX Series.                          //
//                             GeForce 5/6/7/8/9xxx Series.                //
//                             GeForce 2/4xx GTS Series.                   //
//                             GeForce 2Way-SLI / 3Way-SLI		   	       //
//                OS - Windows 98 / 2K / XP / VISTA / Win7 x32:x64         //
//                                                                         //
/////////////////////////////////////////////////////////////////////////////
//
// B3define.h: interface for the CB3Mesh class.
//
// 2003. Kihong Kim / mad_dog@hanmail.net
// 2006.08. Update.
// 2011.04.Update.
//
//////////////////////////////////////////////////////////////////////

#pragma once

#include "d3d9.h"
#include "d3dx9.h"

#ifndef LPDEVICE
typedef LPDIRECT3DDEVICE9	LPDEVICE;
#endif

#ifndef LPVBUFFER
typedef LPDIRECT3DVERTEXBUFFER9	LPVBUFFER;
typedef LPDIRECT3DVERTEXBUFFER9	LPVERTEXBUFFER;
#endif


typedef D3DXVECTOR3		VECTOR3;
typedef D3DXVECTOR2		VECTOR2;
typedef D3DXCOLOR		COLOR;

typedef D3DXMATRIX		MATRIX;

typedef LPD3DXMESH		LPMESH;

typedef D3DMATERIAL9	MTRL;
typedef D3DMATERIAL9*	LPMTRL;
typedef D3DXMATERIAL	XMTRL;
typedef D3DXMATERIAL*	LPXMTRL;

typedef LPD3DXBUFFER	LPBUFF;

#ifndef LPTEXTURE
typedef LPDIRECT3DTEXTURE9	LPTEXTURE;
#endif

typedef LPD3DXFONT		LPDXFONT;


#ifndef SAFE_RELEASE
#define SAFE_RELEASE(pBuff) if((pBuff)){ (pBuff)->Release(); (pBuff) = NULL; }
#define SAFE_DELETE(pBuff)	if((pBuff)){ delete (pBuff); (pBuff) = NULL; }
#define SAFE_DELARRY(pBuff) if((pBuff)){ delete [] (pBuff); (pBuff) = NULL; }
#endif


#ifndef IsKeyDown
#define IsKeyDown(key)	((GetAsyncKeyState(key)&0x8000) == 0x8000)
#define IsKeyUp(key)	((GetAsyncKeyState(key)&0x8001) == 0x8001)
#endif
 

#ifndef YES_
#define YES_ 1
#define NO_ 0
#endif
 




 
/****************** end of file "B3Mesh.h" *******************************/