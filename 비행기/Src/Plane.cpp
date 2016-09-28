#include "Plane.h"

#pragma  warning(disable:4996)
#include "stdio.h"


/////////////////////////////////////////////////////////////////////////////
// ���� �߻���
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

	return 0;		//���� ����.
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
	//��Ƽ���� ����.
	SAFE_DELARRY(m_pMtrls);
	
	//�ؽ��� ����.
	if(m_ppTextures)
	{
		for(DWORD i=0; i<m_MtrlCnt; i++)
		{
			SAFE_RELEASE(m_ppTextures[i]);
		}

		SAFE_DELARRY(m_ppTextures);
	}

	//�޽� ����.
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

    D3DXMatrixIdentity(&Plane->mTM);					// ����� �ʱ�ȭ.
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

    //���͸� ����.
    if (_stricmp(Plane->g_pMeshPath, "") != 0)
    {
        ::SetCurrentDirectory(Plane->g_pMeshPath);
    }

     //�ܺ� ������ �ε�.
    char MeshPath[256] = "";
    if (!LoadInitData(MeshPath, Plane->g_pMeshName))  //if (!LoadInitData(MeshPath, Plane->g_pMeshName))
    {
        MessageBox(NULL, "Data.ini �ε� ����.", "����", MB_ICONERROR | MB_OK);
        return E_FAIL;
    }

    //.x�� �ؽ��ĸ� �ҷ���
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

		Plane->m_pMesh->DrawSubset(i);						//��
	}

	g_pDevice->SetTransform(D3DTS_WORLD, &Plane->mPROP);

	Plane->m_pDev->SetMaterial(&Plane->m_pMtrls[5]);
	Plane->m_pDev->SetTexture(0, Plane->m_ppTextures[5]);
	Plane->m_pMesh->DrawSubset(5);

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
//
// �޽� �ε�.
//
BOOL B3Mesh::Load(LPDEVICE pDev, LPCTSTR filename)
{
  
	// DX �޼ҵ��� ���� �ʿ��� ������ 'ȹ��' �ϱ� ���� (�ӽ�) ������. (���� ����)	 
	// (����) ��������, ����(+�ؽ�ó ���ϸ�), �Ӽ�, ��������, Effect ���� ��..
	//
	LPD3DXBUFFER	pMtrlBuffer = NULL;
	

	// ��, �޽� �ε�..
	//
	HRESULT hr = D3DXLoadMeshFromX(filename, D3DXMESH_MANAGED, pDev,
								NULL, &pMtrlBuffer, NULL, &m_MtrlCnt,	//X Mesh �� ������ �ִ� Ư�� ���� ȹ��..
								&m_pMesh								//������ X �޽� ��ü ����.��
								);
	if(FAILED(hr))
	{ 
		B3Error(NO_, "[Error] B3Model::Load() ����.. : Error=%s \n File=%s",
			DXGetErrorString(hr), filename);
		return FALSE;
	}

	 
	// ���� �� �ؽ��� ���� ����� ���� Ȯ��.
	//
	D3DXMATERIAL* mtrls = (D3DXMATERIAL*)pMtrlBuffer->GetBufferPointer();

	m_pMtrls = new D3DMATERIAL9[m_MtrlCnt];			//����(DX9) 
	if(m_pMtrls == NULL) return FALSE;
	::ZeroMemory(m_pMtrls, sizeof(D3DMATERIAL9)*m_MtrlCnt); 

 	m_ppTextures = new LPTEXTURE[m_MtrlCnt];		//�ؽ�ó (������ 1����. ���� 2�� �̻� ���Ǵ� ��쵵 ����)
	if(m_ppTextures == NULL) return FALSE;
	::ZeroMemory(m_ppTextures, sizeof(LPTEXTURE)*m_MtrlCnt);
	 

	// ���� �� �ؽ��� ���� ���� 
	//
	for(DWORD i=0; i<m_MtrlCnt; i++)
	{
		//���� ���� ���� �� ����.
		m_pMtrls[i] = mtrls[i].MatD3D;
		if(m_pMtrls[i].Diffuse.a <= 0.0f)				//������ alpha ������ 0���ϸ� ���...������ ����.
			m_pMtrls[i].Diffuse.a = 1.0f;				//1.0���� ������Ŵ
		m_pMtrls[i].Ambient = m_pMtrls[i].Diffuse;		//Ambient ���� ����.
		m_pMtrls[i].Specular = D3DXCOLOR(1, 1, 1, 1);
		m_pMtrls[i].Power = 10.f;

		//�ؽ��� �ε� (�ִٸ�..)
		if(	mtrls[i].pTextureFilename != NULL ) 
		{
			hr = D3DXCreateTextureFromFile(pDev, mtrls[i].pTextureFilename,
											&m_ppTextures[i]);
			if(FAILED(hr))
			{
				B3Error( NO_, "[Error] B3Material::Create():LoadTexture ����: Error=%s \n File=%s",
				DXGetErrorString(hr), mtrls[i].pTextureFilename); 
			}
		}
	}


	//����̽� ���.
	m_pDev = pDev;

	//�ӽ� ���� ����.
	SAFE_RELEASE(pMtrlBuffer);

	return TRUE;

}//end of B3Mesh::Load()


// �ܺ����Ͽ��� ������ �ε��ϱ�. 
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

		strcpy(token, "");		//��ū�����.

								//���� �б�.
		fgets(line, 256, fp);	//������ '����'������ fscanf �� ���� ����..
		sscanf(line, "%s", token);

		//�ּ� �˻�.  
		if (_strnicmp(token, "//", 2) == 0) continue;

		//�޽� �̸� �ε�.
		//if(_strnicmp(token, "File", 4) == 0)
		//	   sscanf(line, "%s", pMeshName);  
		sscanf(line, "%s", fullname);
	}
	fclose(fp);

	//'path' & 'filename' �и��ϱ�.
	char* p = strrchr(fullname, '/');

	if (p == NULL)
		p = strrchr(fullname, '\\');

	UINT n = (UINT)(p - fullname);		// ex) "../data/airplane/hero.x"
	strncpy(pPath, fullname, n);		//Path ���.  "../data/airplane"
	strcpy(pMeshName, p + 1);			//name �����."hero.x"

	return true;
}