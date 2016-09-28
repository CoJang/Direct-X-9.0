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
// BAxis.cpp: 그리드 클래스 관련 헤더 파일.
//
// 2004.06. Kihong Kim / mad_dog@hanmail.net / Blue3D / Hero3D
// 2004.10. update.
//
/////////////////////////////////////////////////////////////////////////////


//#include "../B3XMeshViwer 10 (+Optimize+Mem@Fix) 20080312/src/Camera.h"
#pragma warning(disable:4996)
#include "B3define.h"
#include "assert.h"
#include "stdio.h"
#include "BAxis.h"


#define VIEWPORT_SCALE_  0.2f //1.0f //0.1f



B3Axis::B3Axis(void)
{
	m_pDev = NULL;
	m_pVB = NULL;
	m_pVtxs =NULL;

	m_bUseViewPort = YES_;
	 
}

B3Axis::~B3Axis(void)
{
	Release();
}




/////////////////////////////////////////////////////////////////////////////
//
void B3Axis::Release()
{
	SAFE_RELEASE(m_pVB);
	SAFE_DELETE(m_pVtxs);	
}




/////////////////////////////////////////////////////////////////////////////
//
int B3Axis::Init(LPDEVICE pDev, _AXISINFO* pAi, DWORD width, DWORD height)
{
	//assert(pDev != NULL);
	assert(pAi != NULL); 


	

	//라인 3개 + 글자 출력 좌표 3개.
	m_pVtxs = new VTX_AXIS[6+3];
	m_pVtxs[0].vPos = VECTOR3(0, 0, 0);		//x 축. 라인.
	m_pVtxs[1].vPos = VECTOR3(pAi->length, 0, 0);
	m_pVtxs[0].Color = COLOR(1, 0, 0, 1);
	m_pVtxs[1].Color = COLOR(1, 0, 0, 1);
	 
	m_pVtxs[2].vPos = VECTOR3(0, 0, 0);		//y 축. 라인.
	m_pVtxs[3].vPos = VECTOR3(0, pAi->length, 0);
	m_pVtxs[2].Color = COLOR(0, 1, 0, 1);
	m_pVtxs[3].Color = COLOR(0, 1, 0, 1);

	m_pVtxs[4].vPos = VECTOR3(0, 0, 0);		//z 축. 라인.
	m_pVtxs[5].vPos = VECTOR3(0, 0, pAi->length);
	m_pVtxs[4].Color = COLOR(0, 0.3f, 1, 1);
	m_pVtxs[5].Color = COLOR(0, 0.3f, 1, 1);


	m_pVtxs[6].vPos = VECTOR3(pAi->length+0.1f, 0, 0);
	m_pVtxs[7].vPos = VECTOR3(0, pAi->length+0.1f, 0);
	m_pVtxs[8].vPos = VECTOR3(0, 0, pAi->length+0.1f);
	m_pVtxs[6].Color = COLOR(1, 0, 0, 1);
	m_pVtxs[7].Color = COLOR(0, 1, 0, 1);
	m_pVtxs[8].Color = COLOR(0, 0.3f, 1, 1);
	 

 	
/*
	//정점 버퍼 구성.
 	HRESULT res = S_OK;
	int size = vtxcnt * sizeof(VTX_AXIS);

	if(FAILED(res = m_pDev->CreateVertexBuffer( size, D3DUSAGE_WRITEONLY, 
												FVF_GRID, D3DPOOL_MANAGED, 
												&m_pVB, NULL)))
	{
		B3D_Error(NO_, "B3Axis::Init() 실패. VB 생성 실패.");
		return res;
	}

	VTX_AXIS* pVB = NULL;
	if(FAILED(res = m_pVB->Lock(0, size, (VOID**)&pVB, NULL)))
	{ 		
		return res;
	}
	::memcpy(pVB, m_pAxis, size);
	m_pVB->Unlock();


	//전체 라인개수.
	m_uLineCnt = vtxcnt / 2;// * 0.5f;

*/

	m_ViewPort.X = 0;
	m_ViewPort.Y = (DWORD)(height * VIEWPORT_SCALE_);
	m_ViewPort.Width = (DWORD)(width  * VIEWPORT_SCALE_);
	m_ViewPort.Height = (DWORD)(height * VIEWPORT_SCALE_); 
	m_ViewPort.MinZ = 0.0f;
	m_ViewPort.MaxZ = 1.0f; 



	//ㅇㅋ. 완료.
	//B3D_Error(NO_, "B3Axis::Init() 성공. 축선 구성 완료.");


	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
//
// 카메라 공간에 정렬하여 축 선 보여주기.
// 
int B3Axis::Update(LPDEVICE pDev, 
				  //CCamera* pCam,						
				  VECTOR3 vCamEye,
				  VECTOR3 vCamNView,
				  DWORD width /* = 0 */, DWORD height /* = 0 */
				  ) 
{
	if(pDev != NULL)
		m_pDev = pDev;
   
	D3DXMatrixIdentity(&m_mTM); 	 

	if(width != 0)
	{ 
		m_ViewPort.X = 0;
		m_ViewPort.Y = (DWORD)(height - (height * VIEWPORT_SCALE_));
		m_ViewPort.Width = (DWORD)(width  * VIEWPORT_SCALE_);
		m_ViewPort.Height = (DWORD)(height * VIEWPORT_SCALE_); 
		m_ViewPort.MinZ = 0.0f;
		m_ViewPort.MaxZ = 1.0f; 
	}
	
	m_bUseViewPort  = YES_;

  /*if(width != 0)			//뷰포트 미적용시...
	{
		m_ViewPort.X = 0;
		m_ViewPort.Y = 0;
		m_ViewPort.Width =  width;
		m_ViewPort.Height =  height;
		m_ViewPort.MinZ = 0.0f;
		m_ViewPort.MaxZ = 1.0f; 
	}
 */
 



	// 글차 출력용 좌표 계산....
	MATRIX mProj;	m_pDev->GetTransform(D3DTS_PROJECTION, &mProj);
	MATRIX mVP; 							 
	D3DXMatrixIdentity(&mVP);


	mVP._11 = m_ViewPort.Width * 0.5f;				//width * VIEWPORT_SCALE_ / 2.0f;
	mVP._22 = -(m_ViewPort.Height * 0.5f);			//-(height * VIEWPORT_SCALE_ / 2.0f);
	mVP._41 = m_ViewPort.Width * 0.5f;				//width * VIEWPORT_SCALE_ / 2.0f;
	mVP._42 = height - m_ViewPort.Height * 0.5f;	//1 - height * VIEWPORT_SCALE_ / 2.0f;*/

	MATRIX mTM;			D3DXMatrixIdentity(&mTM);
	MATRIX mView;		m_pDev->GetTransform(D3DTS_VIEW, &mView);	 
	 
	
	//항상 카메라 '앞' 에 있어야 합니다..
	//VECTOR3 vPos = pCam->GetEye() + pCam->GetNView()*10.0f; 
	VECTOR3 vPos = vCamEye + vCamNView*10.0f; 
	mTM._41 = vPos.x; 
	mTM._42 = vPos.y;
	mTM._43 = vPos.z;

 
	//축 - 라인도 이동/스케일을 제외.
	m_mTM  =  mTM;
 	


	//글자 출력위치 최종 계산.
	mTM = mTM *  mView * mProj * mVP; 
 
	for(int i=6, k=0; i<9; i++ , k++)
		D3DXVec3TransformCoord(&m_vTextPos[k], &m_pVtxs[i].vPos, &mTM);
 	

	return TRUE;
}













/////////////////////////////////////////////////////////////////////////////
//
// 월드 좌표 공간에 정렬하여 축 선 보여주기.
//
int B3Axis::Update(LPDEVICE pDev, 
				  VECTOR3 vPos,			//고정될 위치 값. (목표물의..)
				  DWORD width /* = 0 */, DWORD height /* = 0 */
				  ) 
{
	if(pDev != NULL)
		m_pDev = pDev;

	D3DXMatrixIdentity(&m_mTM); 	 

	
	/*if(width != 0)
	{ 
		m_ViewPort.X = 0;
		m_ViewPort.Y = (DWORD)(height - (height * VIEWPORT_SCALE_));
		m_ViewPort.Width = (DWORD)(width  * VIEWPORT_SCALE_);
		m_ViewPort.Height = (DWORD)(height * VIEWPORT_SCALE_); 
		m_ViewPort.MinZ = 0.0f;
		m_ViewPort.MaxZ = 1.0f; 
	}*/

	//뷰포트 미적용시...사용.
	if(width != 0)
	{
		m_ViewPort.X = 0;
		m_ViewPort.Y = 0;
		m_ViewPort.Width =  width;
		m_ViewPort.Height =  height;
		m_ViewPort.MinZ = 0.0f;
		m_ViewPort.MaxZ = 1.0f; 
	}
	 
	m_bUseViewPort = NO_;


	// 글차 출력용 좌표 계산....
	MATRIX mProj;	m_pDev->GetTransform(D3DTS_PROJECTION, &mProj);		//직교투영으로 처리.
	
//	MATRIX mInvProj;
//	D3DXMatrixInverse(&mInvProj, NULL, &mProj);
/*	MATRIX mProj;	
	D3DXMatrixOrthoLH(&mProj, width, height, 1.0f, 1000.0f); 
	m_mOrthoProj = mProj;

	MATRIX mScale;
	D3DXMatrixScaling(&mScale, 10.0f, 10.0f, 10.0f);
*/
	MATRIX mVP; 							 
	D3DXMatrixIdentity(&mVP);


	mVP._11 = m_ViewPort.Width * 0.5f;				//width * VIEWPORT_SCALE_ / 2.0f;
	mVP._22 = -(m_ViewPort.Height * 0.5f);			//-(height * VIEWPORT_SCALE_ / 2.0f);
	mVP._41 = m_ViewPort.Width * 0.5f;				//width * VIEWPORT_SCALE_ / 2.0f;
	mVP._42 = height - m_ViewPort.Height * 0.5f;	//1 - height * VIEWPORT_SCALE_ / 2.0f;*/
	//mVP._42 = m_ViewPort.Height * 0.5f;	//1 - height * VIEWPORT_SCALE_ / 2.0f;*/

	MATRIX mTM;			D3DXMatrixIdentity(&mTM);
	MATRIX mView;		m_pDev->GetTransform(D3DTS_VIEW, &mView);	 

//	MATRIX mInvView;
//	D3DXMatrixInverse(&mInvView, NULL, &mView);

	//항상 카메라 '앞' 에 있어야 합니다..
	//VECTOR3 vPos = pCam->GetEye() + pCam->GetNView()*10.0f; 
	mTM._41 = vPos.x; 
	mTM._42 = vPos.y;
	mTM._43 = vPos.z;

	//mTM *= mScale;

//	mTM._11 = mInvView._11; 
//	mTM._22 = mInvView._22; 
//	mTM._33 = mInvView._33; 
/*	mTM._11 = mInvProj._11; 
	mTM._22 = mInvProj._22; 
	mTM._33 = mInvProj._33; 
*/

	//축 - 라인 행렬. 
	m_mTM  =  mTM;



	//글자 출력위치 최종 계산.
	mTM = mTM *  mView * mProj * mVP; 

	for(int i=6, k=0; i<9; i++ , k++)
		D3DXVec3TransformCoord(&m_vTextPos[k], &m_pVtxs[i].vPos, &mTM);




	return TRUE;
}









///////////////////////////////////////////////////////////////////////////////
//
// DrawText
//
void B3DrawText(LPDXFONT pFont, int x, int y, D3DXCOLOR col, char* msg, ...) 
{
	char buff[256];
	va_list vl;
	va_start(vl, msg); 
	vsprintf(buff, msg, vl);
	va_end(vl);

	RECT rc = { x, y, 0, 0};
	pFont->DrawText(NULL, buff, strlen(buff), &rc, DT_NOCLIP, col);
}




D3DVIEWPORT9 oldvp;


/////////////////////////////////////////////////////////////////////////////
//
int B3Axis::Render(LPDEVICE pDev, 
				 // B3Font* pFont,  
				  LPDXFONT pFont,
				  DWORD width, DWORD height
				  )
{
	m_pDev = pDev;

	 
	m_pDev->SetTransform(D3DTS_WORLD, &m_mTM);
	
	//if(!m_bUseViewPort) 
	//{
		
	//}
	DWORD bLight;
	m_pDev->GetRenderState(D3DRS_LIGHTING, &bLight);
	m_pDev->SetRenderState(D3DRS_LIGHTING, FALSE);
	m_pDev->SetRenderState(D3DRS_ZENABLE, FALSE);

//	m_pDev->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_SELECTARG1);	 
//	m_pDev->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_DIFFUSE);	 
	
	//m_pDev->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);	 
//	m_pDev->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_DISABLE);


	//글자 출력.
	/*if(pFont != NULL)
	{ 	 
		pFont->DrawText((int)m_vTextPos[0].x, (int)m_vTextPos[0].y, "X", m_pVtxs[6].Color);
		pFont->DrawText((int)m_vTextPos[1].x, (int)m_vTextPos[1].y, "Y", m_pVtxs[7].Color);
		pFont->DrawText((int)m_vTextPos[2].x, (int)m_vTextPos[2].y, "Z", m_pVtxs[8].Color);
	}*/

	B3DrawText(pFont, (int)m_vTextPos[0].x, (int)m_vTextPos[0].y, m_pVtxs[6].Color, "X");
	B3DrawText(pFont, (int)m_vTextPos[1].x, (int)m_vTextPos[1].y, m_pVtxs[7].Color, "Y");
	B3DrawText(pFont, (int)m_vTextPos[2].x, (int)m_vTextPos[2].y, m_pVtxs[8].Color, "Z");

	
	

	MATRIX mOldProj;
	if(m_bUseViewPort)
	{		
		m_pDev->GetViewport(&oldvp);
		m_pDev->SetViewport(&m_ViewPort);
	}
/*	else
	{
		m_pDev->GetTransform(D3DTS_PROJECTION, &mOldProj);
		m_pDev->SetTransform(D3DTS_PROJECTION, &m_mOrthoProj);
	}
*/
	
	
	//m_pDev->SetStreamSource(0, m_pVB, 0, sizeof(VTX_AXIS)); 
	m_pDev->SetTexture(0, NULL);
	m_pDev->SetTexture(1, NULL);
	m_pDev->SetTexture(2, NULL);
	m_pDev->SetFVF(FVF_AXIS);					 
	//m_pDev->SetIndices(pMesh->GetIB());
	//m_pDev->DrawPrimitive(D3DPT_LINELIST, 0, m_uLineCnt);		

	m_pDev->DrawPrimitiveUP(D3DPT_LINELIST, 3, m_pVtxs, sizeof(VTX_AXIS)); 

	m_pDev->SetRenderState(D3DRS_LIGHTING, bLight); //TRUE);
	m_pDev->SetRenderState(D3DRS_ZENABLE, TRUE);


	if(m_bUseViewPort)
	{
		m_pDev->SetViewport(&oldvp);
	}
/*	else		
	{
		m_pDev->SetTransform(D3DTS_PROJECTION, &mOldProj);
	}
*/
	return TRUE;
}




/////////////////////////////////////////////////////////////////////////////
//











/***************** end of file "Axis.cpp" ********************************/













