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
/////////////////////////////////////////////////////////////////////////////
//
// BGrid.cpp: �׸��� Ŭ���� ���� ��� ����.
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

	//���� ���� ����.
	int xcnt = (pGrid->width / (int)pGrid->scale) + 1;				//����/���κ� ���� ����.
	int ycnt = (pGrid->width / (int)pGrid->scale) + 1;
	int vtxcnt = (xcnt + ycnt) * 2;									//��������.

	m_pGrids = new VTX_GRID[vtxcnt];
	ZeroMemory(m_pGrids, sizeof(VTX_GRID) * vtxcnt);


	//�׸��� ���� ��ġ. (�⺻. ����(0,0,0))
	float hx = (pGrid->width * 0.5f);
	float hy = (pGrid->height * 0.5f);

	//float sx =  -hx;
	//float sz =  hy;
	

	//x �� ����.
	int k=0;
	for(int i=0; i<xcnt; i++, k+=2)
	{ 
		float sx = -hx;
		float sz = hy -  i * pGrid->scale;		//�Ʒ��� �����ɴϴ�.

		m_pGrids[k].vPos = VECTOR3(sx, 0.0f, sz );
		m_pGrids[k+1].vPos = VECTOR3(sx + pGrid->width, 0.0f,  sz);

		m_pGrids[k].Color = (DWORD)(xcnt/2 == i)?D3DXCOLOR(0, 0, 0, 1):pGrid->color;
		m_pGrids[k+1].Color = (DWORD)(xcnt/2 == i)?D3DXCOLOR(0, 0, 0, 1):pGrid->color;
	}
	 
	//z �� ����
	//k = ;
	for(int j=0; j<ycnt; j++, k+=2)
	{ 
		float sx = -hx + j * pGrid->scale;		//����������..
		float sz = hy;		

		m_pGrids[k].vPos = VECTOR3(sx, 0.0f, sz);
		m_pGrids[k+1].vPos = VECTOR3(sx, 0.0f,  sz - pGrid->height);

		m_pGrids[k].Color = (DWORD)(ycnt/2 == j)?D3DXCOLOR(0, 0, 0, 1):pGrid->color;
		m_pGrids[k+1].Color = (DWORD)(ycnt/2 == j)?D3DXCOLOR(0, 0, 0, 1):pGrid->color;
	}
 
	

	//���� ���� ����.
 	HRESULT res = S_OK;
	int size = vtxcnt * sizeof(VTX_GRID);

	if(FAILED(res = m_pDev->CreateVertexBuffer( size, D3DUSAGE_WRITEONLY, 
												FVF_GRID, D3DPOOL_MANAGED, 
												&m_pVB, NULL)))
	{
		//B3D_Error(NO_, "B3Grid::Init() ����. VB ���� ����.");
		return res;
	}

	VTX_GRID* pVB = NULL;
	if(FAILED(res = m_pVB->Lock(0, size, (VOID**)&pVB, NULL)))
	{ 		
		return res;
	}
	::memcpy(pVB, m_pGrids, size);
	m_pVB->Unlock();


	//��ü ���ΰ���.
	m_uLineCnt = vtxcnt / 2;// * 0.5f;


	//����. �Ϸ�.
	//B3D_Error(NO_, "B3Grid::Init() ����. �׸��� �ε� �Ϸ�.");


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
		//...�׸��� ���� ����. �������� �籸��...
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













