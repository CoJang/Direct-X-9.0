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
// Yena.h: B3Yena 엔진 최상위/필수 헤더.
//
// 2003. Kihong Kim / mad_dog@hanmail.net
// 2006.08. Update.
// 2011.04.Update.
//
//////////////////////////////////////////////////////////////////////

#pragma once

#include "assert.h"

/*//Yena 라이브러리 추가하기.<방법1> 직접 링크.
#include "B3Yena/BGrid.h"
#include "B3Yena/BAxis.h"
*/
//Yena 라이브러리 추가하기.<방법2> 프로젝트 속성에 폴더 지정.
//장점 : B3Yena 폴더를 직접 명시하지 않아도 됨, 각 소스별 헤더의 참조 및 복잡성이 제거됨.
// Project Properties > C/C++ > Additional Include Directories 에 다음 구문 추가 : ".\B3Yena"
//   
#include "BGrid.h"
#include "BAxis.h"

extern B3Grid* g_pGrid;
extern B3Axis* g_pAxis;

void GridAxisCreate();
void GridAxisRelease();
void GridAxisUpdate(float dTime);
void GridAxisDraw();



 
/****************** end of file "Yena.h" *******************************/