#include "Plane.h"

#pragma  warning(disable:4996)
#include "stdio.h"

B3Mesh* Dwarf = NULL;

INT DwarfInit(D3DXVECTOR3(vpos))
{
	Dwarf = new B3Mesh;

	strcpy(Dwarf->g_pMeshName, "./Dwarf.x");
	Dwarf->g_pMeshPath = "./Data";

	Dwarf->vRot = D3DXVECTOR3(0, 0, 0);
	Dwarf->vDir = D3DXVECTOR3(0, 0, 0);
	Dwarf->vPos = vpos;

    D3DXMatrixIdentity(&Dwarf->mTM);					// 행렬의 초기화.
    D3DXMatrixIdentity(&Dwarf->mRot);
    D3DXMatrixIdentity(&Dwarf->mScale);
    D3DXMatrixIdentity(&Dwarf->mTrans);

	ZeroMemory(&Dwarf->Material, sizeof(Dwarf->Material));
	Dwarf->Material.Diffuse = { 0, 0, 0, 0 };
	Dwarf->Material.Ambient = { 1, 1, 1, 1 };
	Dwarf->Material.Specular = { 0, 0, 0, 0 };
	Dwarf->Material.Power = 30.f;


    D3DXMatrixTranslation(&Dwarf->mTrans, Dwarf->vPos.x, Dwarf->vPos.y, Dwarf->vPos.z);
	D3DXMatrixScaling(&Dwarf->mScale, 3, 3, 3);

    ////디렉터리 변경.
    //if (_stricmp(Dwarf->g_pMeshPath, "") != 0)
    //{
    //    ::SetCurrentDirectory(Dwarf->g_pMeshPath);
    //}

    //char MeshPath[256] = "";
    //if (!LoadInitData(MeshPath, Dwarf->g_pMeshName))
    //{
    //    MessageBox(NULL, "Data.ini 로드 실패.", "에러", MB_ICONERROR | MB_OK);
    //    return E_FAIL;
    //}

    //.x와 텍스쳐를 불러옴
	Dwarf->Load(g_pDevice, Dwarf->g_pMeshName);

    return TRUE;
}


void DwarfUpdate(float dTime)
{
    static float angle = 0.0f;

    D3DXMatrixRotationYawPitchRoll(&Dwarf->mRot, Dwarf->vRot.y, Dwarf->vRot.x, Dwarf->vRot.z);

    angle += D3DX_PI * dTime;

    D3DXMatrixRotationY(&Dwarf->mRot, angle);

    D3DXVec3Normalize(&Dwarf->vDir, &Dwarf->vDir);

	Dwarf->mTM = Dwarf->mScale * Dwarf->mRot * Dwarf->mTrans;

}

BOOL DwarfDraw(float dTime)
{
	if (Dwarf->m_pDev == NULL) return FALSE;

	g_pDevice->SetRenderState(D3DRS_SPECULARENABLE, TRUE);
	g_pDevice->SetRenderState(D3DRS_SPECULARMATERIALSOURCE, D3DMCS_MATERIAL);

	for (DWORD i = 0; i< Dwarf->m_MtrlCnt; i++)
	{
		g_pDevice->SetTransform(D3DTS_WORLD, &Dwarf->mTM);
		Dwarf->m_pDev->SetMaterial(&Dwarf->Material);
		Dwarf->m_pDev->SetTexture(0, Dwarf->m_ppTextures[i]);

		Dwarf->m_pMesh->DrawSubset(i);						//★
	}

	return TRUE;
}



 

/******************* end of file "B3Mesh.cpp" ******************************/