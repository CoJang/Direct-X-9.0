/////////////////////////////////////////////////////////////////////////////
//                                                                         //
//  B3D/YENA : DirectX �� �̿��� �ϵ���� ���� 2D/3D ����.                 // 
//                                                                         //
//  �� �� : Kihong Kim / mad_dog@hanmail.net                               // 
//          Zero-G Tech,Inc http://www.zero-g.kr						   //	
//  �ʱ����� : 2003.12 - 2004.03.                                          //
//  ����ȯ�� : OS - Windows 2k SP4 / Visual Studio 6.0/2003/2005/2008      //
//                  DirectX 9.0b(2003, summer)                             //
//                  DirectX 9.0b(2007, November)                           //
//             H/W - AMD Athlon XP(Barton) 2500+@2300                      //    
//                   ATI Radeon 9600 Pro                                   //
//                   ABit NF7-II /w SAMSUNG DDR 512MB                      //
//                   SB Live! DE 5.1                                       //
//  �׽�Ʈ ȯ�� : CPU - AMD Athlon										   //	 
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
// Yena.h: B3Yena ���� �ֻ���/�ʼ� ���.
//
// 2003. Kihong Kim / mad_dog@hanmail.net
// 2006.08. Update.
// 2011.04.Update.
//
//////////////////////////////////////////////////////////////////////

#pragma once

#include "assert.h"

/*//Yena ���̺귯�� �߰��ϱ�.<���1> ���� ��ũ.
#include "B3Yena/BGrid.h"
#include "B3Yena/BAxis.h"
*/
//Yena ���̺귯�� �߰��ϱ�.<���2> ������Ʈ �Ӽ��� ���� ����.
//���� : B3Yena ������ ���� ������� �ʾƵ� ��, �� �ҽ��� ����� ���� �� ���⼺�� ���ŵ�.
// Project Properties > C/C++ > Additional Include Directories �� ���� ���� �߰� : ".\B3Yena"
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