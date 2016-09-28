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
// BAxis.h: 그리드 클래스 관련 헤더 파일.
//
// 2004.06. Kihong Kim / mad_dog@hanmail.net / Blue3D / Hero3D
// 2004.10. update.
//
/////////////////////////////////////////////////////////////////////////////
#pragma once

//#include "../engine/include/b3x.h"
//#include "b3define.h"
//#include "assert.h"
//#include "../define.h"
//#include "../Engine/Bfont.h"
//#include "../Engine/BLog.h"




//
// class B3Axis
//
class B3Axis
{
public:

	struct VTX_AXIS {
			VECTOR3 vPos;
			DWORD	Color;
	};

	struct _AXISINFO {
		//int width; 
		//int height;
		float length;		//각 막대의 길이.
		float scale;
		//COLOR color;
		DWORD res[20];

		_AXISINFO(float len = 1.0f, float s = 1.0f ):length(len), scale(s){} 
	};

	enum {
		FVF_AXIS = D3DFVF_XYZ | D3DFVF_DIFFUSE,
	};	 
	 
	

protected:

	LPDEVICE		m_pDev;
	LPVBUFFER		m_pVB;
	VTX_AXIS*		m_pVtxs;			//변환본.
	VECTOR3			m_vTextPos[3]; 

	MATRIX			m_mTM;				//카메라의 역행로 처리...
	//UINT			m_uLineCnt;
	D3DVIEWPORT9	m_ViewPort;
	BOOL			m_bUseViewPort;
	MATRIX			m_mOrthoProj;

protected:

	void Release();


public:

	int Init(LPDEVICE pDev, _AXISINFO* pAi, DWORD width, DWORD height);
	
	 
	//int B3Axis::Update(LPDEVICE pDev, CCamera* pCam, DWORD width /* = 0 */, DWORD height /* = 0 */);		//카메라에 고정하기.
	//카메라에 고정하기.
	virtual int Update(LPDEVICE pDev, VECTOR3 vCamEye, VECTOR3 vCamNView, 
					  DWORD width  = 0 , DWORD height  = 0);		
	//위치에 고정하기.
	virtual int Update(LPDEVICE pDev, VECTOR3 vPos, DWORD width  = 0 , DWORD height  = 0 );		
	 
	virtual int Render(LPDEVICE pDev, 
						//B3Font* pFont,  
						LPDXFONT pFont,
						DWORD width, DWORD heigh );

	B3Axis(void);
	virtual ~B3Axis(void);

};


/***************** end of file "Axis.h" ********************************/
