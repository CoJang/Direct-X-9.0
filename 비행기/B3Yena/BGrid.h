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
/////////////////////////////////////////////////////////////////////////////
//
// BGrid.h: 그리드 클래스 관련 헤더 파일.
//
// 2004.06. Kihong Kim / mad_dog@hanmail.net / Blue3D / Hero3D
// 2004.10. update.
// 2010.02. Update. B3Yena / Zero-G Interactive
//
/////////////////////////////////////////////////////////////////////////////
#pragma once

//#include "Device.h"
#include "B3define.h"
#include "d3dx9.h"
#include "dxerr.h"
//#include "stdio.h"
#include "assert.h"
//#include "../define.h"
//#include "../Engine/Bfont.h"
//#include "../Engine/BLog.h"
//typedef LPDIRECT3DVERTEXBUFFER9	LPVERTEXBUFFER;
//typedef LPDIRECT3DVERTEXBUFFER9	LPVBUFFER;
//typedef D3DXVECTOR3	VECTOR3;
//typedef D3DXVECTOR2		VECTOR2;
//typedef D3DXMATRIX	MATRIX;
//typedef D3DXCOLOR	COLOR;
 


 

//
// class B3Grid
//
class B3Grid
{
public:

	struct VTX_GRID {
			VECTOR3 vPos;
			DWORD	Color;
	};

	struct GRIDINFO {
		int width; 
		int height;
		float scale;
		COLOR color;
		DWORD res[20];

		GRIDINFO(int w = 100, int h = 100, float s = 1.0f, 
				COLOR c = COLOR(0.4f, 0.4f, 0.4f, 1.0f))
				:width(w), height(h), scale(s), color(c){}				
	};

	enum {
		FVF_GRID = D3DFVF_XYZ | D3DFVF_DIFFUSE,
	};
	

	

protected:

	LPDEVICE		m_pDev;
	LPVBUFFER		m_pVB;
	VTX_GRID*		m_pGrids;			//그리드 정적 버퍼.

	MATRIX			m_mTM;
	UINT			m_uLineCnt;
	
	GRIDINFO		m_Info;


protected:

	void Release();


public:

	int Init(LPDEVICE pDev, GRIDINFO* pGrid);
	
	virtual int Update(LPDEVICE pDev = NULL, GRIDINFO* pGrid  = NULL);
	virtual int Render(float dTime, float sx = 0.0f, float sy = 0.0f);


	const GRIDINFO& GetInfo() const { return m_Info; }


	B3Grid(void);
	virtual ~B3Grid(void);

};


/***************** end of file "Grid.h" ********************************/
