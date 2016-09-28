#include "Plane.h"

#pragma  warning(disable:4996)
#include "stdio.h"


/////////////////////////////////////////////////////////////////////////////
// 에러 발생시
int B3Error(BOOL bMsgBox, char* msg, ...)
{
	char buff[1024]="";	 
	char errmsg[1024]="";

	va_list vl;	 
	va_start(vl, msg);
	vsprintf(buff, msg, vl);
	va_end(vl);

	sprintf(errmsg, "*[B3 Error] %s", buff);

	if(bMsgBox) MessageBox(NULL, msg, "[B3 Error]", MB_ICONERROR); 

	OutputDebugString("\n");
	OutputDebugString(buff);		 
	OutputDebugString("\n");

	return 0;		//에러 없음.
}

B3Mesh* Plane = NULL;

B3Mesh::B3Mesh()
{
	m_pMesh = NULL;
	m_pMtrls = NULL;
	m_ppTextures = NULL;
	m_MtrlCnt = 0; 
	m_pDev = NULL;
}

B3Mesh::~B3Mesh()
{
	Release();
}

/////////////////////////////////////////////////////////////////////////////
//
void B3Mesh::Release()
{
	//머티리얼 삭제.
	SAFE_DELARRY(m_pMtrls);
	
	//텍스쳐 제거.
	if(m_ppTextures)
	{
		for(DWORD i=0; i<m_MtrlCnt; i++)
		{
			SAFE_RELEASE(m_ppTextures[i]);
		}

		SAFE_DELARRY(m_ppTextures);
	}

	//메쉬 제거.
	SAFE_RELEASE(m_pMesh);
	 
}

INT PlaneInit(D3DXVECTOR3(vpos))
{
    Plane = new B3Mesh;

    //Plane->g_pMeshName = "./airplane02.x";
    Plane->g_pMeshPath = "./Data";
    Plane->speed = 3.0f;
    Plane->Radius = 10.0f;
    Plane->Degree = D3DX_PI / 4;

    Plane->vRot = D3DXVECTOR3(0, 0, 0);
    Plane->vDir = D3DXVECTOR3(0, 0, 0);
    Plane->vPos = vpos;

    D3DXMatrixIdentity(&Plane->mTM);					// 행렬의 초기화.
    D3DXMatrixIdentity(&Plane->mRot);
    D3DXMatrixIdentity(&Plane->mRRot);
    D3DXMatrixIdentity(&Plane->mScale);
    D3DXMatrixIdentity(&Plane->mTrans);

    D3DXMatrixTranslation(&Plane->mTrans, Plane->vPos.x + Plane->Radius, Plane->vPos.y, Plane->vPos.z);
    D3DXMatrixRotationZ(&Plane->mRRot, Plane->Degree);

	ZeroMemory(&Plane->Material, sizeof(Plane->Material));
	Plane->Material.Diffuse = { 1, 1, 1, 1 };
	Plane->Material.Ambient = { 0.4f, 0.4f, 0.4f, 1 };
	Plane->Material.Specular = { 1, 1, 1, 1 };
	Plane->Material.Power = 30.f;

    //디렉터리 변경.
    if (_stricmp(Plane->g_pMeshPath, "") != 0)
    {
        ::SetCurrentDirectory(Plane->g_pMeshPath);
    }

     //외부 데이터 로드.
    char MeshPath[256] = "";
    if (!LoadInitData(MeshPath, Plane->g_pMeshName))  //if (!LoadInitData(MeshPath, Plane->g_pMeshName))
    {
        MessageBox(NULL, "Data.ini 로드 실패.", "에러", MB_ICONERROR | MB_OK);
        return E_FAIL;
    }

    //.x와 텍스쳐를 불러옴
    Plane->Load(g_pDevice, Plane->g_pMeshName);

    D3DXMatrixScaling(&Plane->mScale, 1, 1, 1);

    return TRUE;
}

void PlanePropUpdate(float dTime) {
    static const float RotX = -0.11344637778f;
    static const float RotY = 0.008726644444f;

    static float angle = 0;

    D3DXMATRIX temp;

    D3DXMatrixRotationX(&Plane->mPROP, RotX);

    D3DXMatrixRotationY(&temp, RotY);
    Plane->mPROP *= temp;

    angle += 20 * dTime;
    if (angle > 2 * D3DX_PI)angle = 0;
    D3DXMatrixRotationZ(&temp, angle);
    Plane->mPROP *= temp;

    D3DXMatrixRotationY(&temp, -RotY);
    Plane->mPROP *= temp;

    D3DXMatrixRotationX(&temp, -RotX);
    Plane->mPROP *= temp;

    Plane->mPROP *= Plane->mTM;
}

void PlaneUpdate(float dTime){
    static float angle = 0.0f;

    D3DXMatrixRotationYawPitchRoll(&Plane->mRot, Plane->vRot.y, Plane->vRot.x, Plane->vRot.z);

    angle += D3DX_PI * dTime;

    D3DXMatrixRotationY(&Plane->mRot, angle);

    D3DXVec3TransformNormal(&Plane->vDir, &Plane->vDir, &Plane->mRRot);
    //Plane->vPos.x += Plane->speed * dTime;
    D3DXVec3Normalize(&Plane->vDir, &Plane->vDir);


    //D3DXMatrixTranslation(&Plane->mTrans, Plane->vPos.x, Plane->vPos.y, Plane->vPos.z);
    Plane->vPos += Plane->vDir * Plane->speed * dTime;
    Plane->mTM = Plane->mScale *Plane->mRRot * Plane->mTrans * Plane->mRot;

    PlanePropUpdate(dTime);
}

BOOL PlaneDraw(float dTime)
{    
	if (Plane->m_pDev == NULL) return FALSE;

	g_pDevice->SetRenderState(D3DRS_SPECULARENABLE, TRUE);
	g_pDevice->SetRenderState(D3DRS_SPECULARMATERIALSOURCE, D3DMCS_MATERIAL);

	for (DWORD i = 0; i < Plane->m_MtrlCnt; i++)
	{
		if (i == 5)
			continue;
		g_pDevice->SetTransform(D3DTS_WORLD, &Plane->mTM);
		Plane->m_pDev->SetMaterial(&Plane->m_pMtrls[i]);
		Plane->m_pDev->SetTexture(0, Plane->m_ppTextures[i]);

		Plane->m_pMesh->DrawSubset(i);						//★
	}

	g_pDevice->SetTransform(D3DTS_WORLD, &Plane->mPROP);

	Plane->m_pDev->SetMaterial(&Plane->m_pMtrls[5]);
	Plane->m_pDev->SetTexture(0, Plane->m_ppTextures[5]);
	Plane->m_pMesh->DrawSubset(5);

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
//
// 메쉬 로드.
//
BOOL B3Mesh::Load(LPDEVICE pDev, LPCTSTR filename)
{
  
	// DX 메소드들로 부터 필요한 정보를 '획득' 하기 위한 (임시) 포인터. (보기 참조)	 
	// (보기) 정점정보, 재질(+텍스처 파일명), 속성, 인접정보, Effect 정보 등..
	//
	LPD3DXBUFFER	pMtrlBuffer = NULL;
	

	// 모델, 메쉬 로딩..
	//
	HRESULT hr = D3DXLoadMeshFromX(filename, D3DXMESH_MANAGED, pDev,
								NULL, &pMtrlBuffer, NULL, &m_MtrlCnt,	//X Mesh 가 가지고 있는 특정 정보 획득..
								&m_pMesh								//성공시 X 메쉬 개체 리턴.★
								);
	if(FAILED(hr))
	{ 
		B3Error(NO_, "[Error] B3Model::Load() 실패.. : Error=%s \n File=%s",
			DXGetErrorString(hr), filename);
		return FALSE;
	}

	 
	// 재질 및 텍스쳐 정보 저장용 버퍼 확보.
	//
	D3DXMATERIAL* mtrls = (D3DXMATERIAL*)pMtrlBuffer->GetBufferPointer();

	m_pMtrls = new D3DMATERIAL9[m_MtrlCnt];			//재질(DX9) 
	if(m_pMtrls == NULL) return FALSE;
	::ZeroMemory(m_pMtrls, sizeof(D3DMATERIAL9)*m_MtrlCnt); 

 	m_ppTextures = new LPTEXTURE[m_MtrlCnt];		//텍스처 (재질당 1개씩. 물론 2개 이상 사용되는 경우도 있음)
	if(m_ppTextures == NULL) return FALSE;
	::ZeroMemory(m_ppTextures, sizeof(LPTEXTURE)*m_MtrlCnt);
	 

	// 재질 및 텍스쳐 정보 구성 
	//
	for(DWORD i=0; i<m_MtrlCnt; i++)
	{
		//재질 정보 복사 및 교정.
		m_pMtrls[i] = mtrls[i].MatD3D;
		if(m_pMtrls[i].Diffuse.a <= 0.0f)				//재질의 alpha 성분이 0이하면 곤란...오류로 가정.
			m_pMtrls[i].Diffuse.a = 1.0f;				//1.0으로 고정시킴
		m_pMtrls[i].Ambient = m_pMtrls[i].Diffuse;		//Ambient 성분 교정.
		m_pMtrls[i].Specular = D3DXCOLOR(1, 1, 1, 1);
		m_pMtrls[i].Power = 10.f;

		//텍스쳐 로드 (있다면..)
		if(	mtrls[i].pTextureFilename != NULL ) 
		{
			hr = D3DXCreateTextureFromFile(pDev, mtrls[i].pTextureFilename,
											&m_ppTextures[i]);
			if(FAILED(hr))
			{
				B3Error( NO_, "[Error] B3Material::Create():LoadTexture 실패: Error=%s \n File=%s",
				DXGetErrorString(hr), mtrls[i].pTextureFilename); 
			}
		}
	}


	//디바이스 백업.
	m_pDev = pDev;

	//임시 버퍼 삭제.
	SAFE_RELEASE(pMtrlBuffer);

	return TRUE;

}//end of B3Mesh::Load()


// 외부파일에서 데이터 로드하기. 
bool LoadInitData(char* pPath, char* pMeshName)
{
	FILE* fp = fopen("data.ini", "rt");

	if (fp == NULL) return false;

	char token[256] = "";
	char line[256] = "";
	char fullname[256] = "";

	while (1)
	{
		if (feof(fp)) break;

		strcpy(token, "");		//토큰지우기.

								//한줄 읽기.
		fgets(line, 256, fp);	//라인의 '공백'때문에 fscanf 는 쓸수 없다..
		sscanf(line, "%s", token);

		//주석 검사.  
		if (_strnicmp(token, "//", 2) == 0) continue;

		//메쉬 이름 로드.
		//if(_strnicmp(token, "File", 4) == 0)
		//	   sscanf(line, "%s", pMeshName);  
		sscanf(line, "%s", fullname);
	}
	fclose(fp);

	//'path' & 'filename' 분리하기.
	char* p = strrchr(fullname, '/');

	if (p == NULL)
		p = strrchr(fullname, '\\');

	UINT n = (UINT)(p - fullname);		// ex) "../data/airplane/hero.x"
	strncpy(pPath, fullname, n);		//Path 얻기.  "../data/airplane"
	strcpy(pMeshName, p + 1);			//name 만얻기."hero.x"

	return true;
}