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
// BGrid.cpp: 그리드 클래스 관련 헤더 파일.
//
// 2004.06. Kihong Kim / mad_dog@hanmail.net / Blue3D / Hero3D
// 2004.10. update.
// 2010.02. Update. B3Yena / Zero-G Interactive
//
/////////////////////////////////////////////////////////////////////////////

 
#include "BGrid.h"

B3Grid::B3Grid(void)
{
	m_pDev = NULL;
	m_pVB = NULL;
	m_pGrids =NULL;

	m_uLineCnt = 0;
}

B3Grid::~B3Grid(void)
{
	Release();
}




/////////////////////////////////////////////////////////////////////////////
//
void B3Grid::Release()
{
	SAFE_RELEASE(m_pVB);
	SAFE_DELETE(m_pGrids);	
}




/////////////////////////////////////////////////////////////////////////////
//
int B3Grid::Init(LPDEVICE pDev, GRIDINFO* pGrid)
{
	assert(pDev != NULL);
	assert(pGrid != NULL);


	m_Info = *pGrid;


	m_pDev  = pDev;

	//정적 버퍼 생성.
	int xcnt = (pGrid->width / (int)pGrid->scale) + 1;				//가로/세로별 라인 개수.
	int ycnt = (pGrid->width / (int)pGrid->scale) + 1;
	int vtxcnt = (xcnt + ycnt) * 2;									//정점개수.

	m_pGrids = new VTX_GRID[vtxcnt];
	ZeroMemory(m_pGrids, sizeof(VTX_GRID) * vtxcnt);


	//그리드 시작 위치. (기본. 원점(0,0,0))
	float hx = (pGrid->width * 0.5f);
	float hy = (pGrid->height * 0.5f);

	//float sx =  -hx;
	//float sz =  hy;
	

	//x 축 라인.
	int k=0;
	for(int i=0; i<xcnt; i++, k+=2)
	{ 
		float sx = -hx;
		float sz = hy -  i * pGrid->scale;		//아래로 내려옵니다.

		m_pGrids[k].vPos = VECTOR3(sx, 0.0f, sz );
		m_pGrids[k+1].vPos = VECTOR3(sx + pGrid->width, 0.0f,  sz);

		m_pGrids[k].Color = (DWORD)(xcnt/2 == i)?D3DXCOLOR(0, 0, 0, 1):pGrid->color;
		m_pGrids[k+1].Color = (DWORD)(xcnt/2 == i)?D3DXCOLOR(0, 0, 0, 1):pGrid->color;
	}
	 
	//z 축 라인
	//k = ;
	for(int j=0; j<ycnt; j++, k+=2)
	{ 
		float sx = -hx + j * pGrid->scale;		//오른쪽으로..
		float sz = hy;		

		m_pGrids[k].vPos = VECTOR3(sx, 0.0f, sz);
		m_pGrids[k+1].vPos = VECTOR3(sx, 0.0f,  sz - pGrid->height);

		m_pGrids[k].Color = (DWORD)(ycnt/2 == j)?D3DXCOLOR(0, 0, 0, 1):pGrid->color;
		m_pGrids[k+1].Color = (DWORD)(ycnt/2 == j)?D3DXCOLOR(0, 0, 0, 1):pGrid->color;
	}
 
	

	//정점 버퍼 구성.
 	HRESULT res = S_OK;
	int size = vtxcnt * sizeof(VTX_GRID);

	if(FAILED(res = m_pDev->CreateVertexBuffer( size, D3DUSAGE_WRITEONLY, 
												FVF_GRID, D3DPOOL_MANAGED, 
												&m_pVB, NULL)))
	{
		//B3D_Error(NO_, "B3Grid::Init() 실패. VB 생성 실패.");
		return res;
	}

	VTX_GRID* pVB = NULL;
	if(FAILED(res = m_pVB->Lock(0, size, (VOID**)&pVB, NULL)))
	{ 		
		return res;
	}
	::memcpy(pVB, m_pGrids, size);
	m_pVB->Unlock();


	//전체 라인개수.
	m_uLineCnt = vtxcnt / 2;// * 0.5f;


	//ㅇㅋ. 완료.
	//B3D_Error(NO_, "B3Grid::Init() 성공. 그리드 로딩 완료.");


	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
//
int B3Grid::Update(LPDEVICE pDev /* = NULL */, GRIDINFO* pGrid /* = NULL */)
{
	if(pDev != NULL)
		m_pDev = pDev;

	if(pGrid != NULL)
	{
		//...그리드 정보 리셋. 정점버퍼 재구성...
	}


	D3DXMatrixIdentity(&m_mTM); 

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
//
int B3Grid::Render(float dTime, float sx /* = 0::0f */, float sy /* = 0::0f */) 
{
	DWORD light;
	m_pDev->GetRenderState(D3DRS_LIGHTING,&light);
	DWORD spec;
	m_pDev->GetRenderState(D3DRS_SPECULARENABLE,&spec);

	//if(light)	
	m_pDev->SetRenderState(D3DRS_LIGHTING, FALSE);
	m_pDev->SetRenderState(D3DRS_SPECULARENABLE, FALSE);

	m_pDev->SetTexture(0, NULL);
	m_pDev->SetTexture(1, NULL);
	m_pDev->SetTransform(D3DTS_WORLD, &m_mTM);
	m_pDev->SetStreamSource(0, m_pVB, 0, sizeof(VTX_GRID)); 
	m_pDev->SetFVF(FVF_GRID);					 
	//m_pDev->SetIndices(pMesh->GetIB());
	m_pDev->DrawPrimitive(D3DPT_LINELIST, 0, m_uLineCnt);		

	
	//if(light)
	m_pDev->SetRenderState(D3DRS_LIGHTING, light);	 
	m_pDev->SetRenderState(D3DRS_SPECULARENABLE, spec);


	return TRUE;
}




/////////////////////////////////////////////////////////////////////////////
//











/***************** end of file "Grid.cpp" ********************************/













