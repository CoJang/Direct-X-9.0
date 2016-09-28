//
// Tree.cpp
//
//
// 2007.01.25. Kihong Kim / mad_dog@hanmail.net
//
#include "d3dx9.h" 
#include "assert.h"
#include "Device.h"
#include "Hero.h"
#include "Render.h"
#include "Windmill.h"

#include "Vertex.h"
#include "Normal.h"

#include "Tree.h"
#include "Season.h"


////////////////////////////////////////////////////////////////////////////
//

#define TREE_MAX_  3000

TREE* g_pTree[TREE_MAX_] = {NULL, };		// ���� ��ü �����͹迭..
LPD3DXMESH  g_pTreeMeshSphere = NULL;
D3DXVECTOR3 BoundSphere = { 0, 0, 0 };
D3DXVECTOR3 BoundSphere2 = { 0, 0, 0 };

//���� �޽� ������. 
VERTEX g_MeshTree[] = {

	{ D3DXVECTOR3(1, 1, 0), D3DXVECTOR3(0, 0, -1), D3DXVECTOR2(0, 0) }, //1
	{ D3DXVECTOR3(1, 0, 0), D3DXVECTOR3(0, 0, -1), D3DXVECTOR2(0, 1) }, //2 //R,G,B,A
	{ D3DXVECTOR3(0, 1, 0), D3DXVECTOR3(0, 0, -1), D3DXVECTOR2(1, 0) }, //3
	{ D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(0, 0, -1), D3DXVECTOR2(1, 1) }, //4 
	{ D3DXVECTOR3(1, 0, 0), D3DXVECTOR3(0, 0, -1), D3DXVECTOR2(0, 1) }, //2 
	{ D3DXVECTOR3(0, 1, 0), D3DXVECTOR3(0, 0, -1), D3DXVECTOR2(1, 0) }, //3
	
	{ D3DXVECTOR3(0.5, 1, 0.5), D3DXVECTOR3(-1, 0, 0), D3DXVECTOR2(0, 0) }, //1
	{ D3DXVECTOR3(0.5, 0, 0.5), D3DXVECTOR3(-1, 0, 0), D3DXVECTOR2(0, 1) }, //2 //R,G,B,A
	{ D3DXVECTOR3(0.5, 1, -0.5), D3DXVECTOR3(-1, 0, 0), D3DXVECTOR2(1, 0) }, //3
	{ D3DXVECTOR3(0.5, 0, -0.5), D3DXVECTOR3(-1, 0, 0), D3DXVECTOR2(1, 1) }, //4 
	{ D3DXVECTOR3(0.5, 0, 0.5), D3DXVECTOR3(-1, 0, 0), D3DXVECTOR2(0, 1) }, //2 
	{ D3DXVECTOR3(0.5, 1, -0.5), D3DXVECTOR3(-1, 0, 0), D3DXVECTOR2(1, 0) }, //3
	

};

LPDIRECT3DVERTEXBUFFER9	g_pVBTree = NULL;			//���� ���ۿ� ������.

CHAR*	   g_TextureName[2];
LPDIRECT3DTEXTURE9 pTex[2];

////////////////////////////////////////////////////////////////////////////
//
int TreeInit() 
{
	int i;

	srand(::timeGetTime());

	// �������� ����ȭ(�� �ʿ� ������ �� ����ȭ ���� �ۼ����� ���� ����Ͽ�)
	for (i = 0; i < _countof(g_MeshTree); ++i)
		D3DXVec3Normalize(&g_MeshTree[i].vNormal, &g_MeshTree[i].vNormal);

	g_TextureName[0] = "./Data/tree01S.dds";

	if (FAILED(D3DXCreateTextureFromFile(g_pDevice, g_TextureName[0], &pTex[0])))
	{
		MessageBox(NULL, "(����)�ؽ��� �ε� ����.", "����", MB_ICONERROR | MB_OK);
		return E_FAIL;
	}

	g_TextureName[1] = "./Data/TREE_mask2.png";

	if (FAILED(D3DXCreateTextureFromFile(g_pDevice, g_TextureName[1], &pTex[1])))
	{
		MessageBox(NULL, "(����)�ؽ��� �ε� ����.", "����", MB_ICONERROR | MB_OK);
		return E_FAIL;
	}

	for(i=0; i<TREE_MAX_; i++)
	{	 
		g_pTree[i] = new TREE;
		assert(g_pTree[i] != NULL);  
		 
 		g_pTree[i]->vPos.x = (float)(rand()%128 - 64);		//���� ������ġ.
		g_pTree[i]->vPos.y = 0.0f;	 
		g_pTree[i]->vPos.z = (float)(rand()%128 - 64);	 
		g_pTree[i]->vUp = D3DXVECTOR3(0, 1, 0);
		g_pTree[i]->Rot_Axis = D3DXVECTOR3(0, 0, 0);
		g_pTree[i]->TreeState = TREE::ts_NONE;
		g_pTree[i]->f_Tangle = 0.0f;
		g_pTree[i]->f_Talpha = 0.3f;
		g_pTree[i]->f_TDelay = 0;

		D3DXMatrixIdentity(&g_pTree[i]->mTM);				//��� ������ �ʱ�ȭ.
		D3DXMatrixIdentity(&g_pTree[i]->mRot);
		D3DXMatrixIdentity(&g_pTree[i]->mScale);
		D3DXMatrixIdentity(&g_pTree[i]->mTrans);
		D3DXMatrixIdentity(&g_pTree[i]->temp_mTM);
		g_pTree[i]->mScale[0] *= 1.5f;
		g_pTree[i]->mScale[5] *= 3.0f;

		//�浹 ���� ����.��
		g_pTree[i]->vCenterL = D3DXVECTOR3(0, 1, 0);		//�浹�� �߽��� : ������ �߰� ��ġ.(���ð���)��
		g_pTree[i]->vCenterW = D3DXVECTOR3(0, 0, 0);		//�ߵ��� �߽��� : ������ǥ��
		g_pTree[i]->fRadius = 1.1f;							//�浹�� �ݰ�.��

		ZeroMemory(&g_pTree[i]->TreeMTL, sizeof(g_pTree[i]->TreeMTL));
		g_pTree[i]->TreeMTL.Diffuse = { 1, 1, 1, 1 };
		g_pTree[i]->TreeMTL.Ambient = { 0.4f, 0.4f, 0.4f, 1 };
	}

	

	// ������ ���� ���� ����.: ���� ������ �ϳ��̹Ƿ�, �̰��� ��Ȱ�� �Ұ��̴�.
	if(FAILED(g_pDevice->CreateVertexBuffer(
										sizeof(g_MeshTree),		
										0, 
										VERTEX::FVF,			
										D3DPOOL_MANAGED,	
										&g_pVBTree,			
										NULL)))
	{
		return E_FAIL;
	}

	//���� ä���.
	VOID*	pBuff;
 	if(FAILED(g_pVBTree->Lock(0, sizeof(g_MeshTree), (void**)&pBuff, 0 )))
	{
		return E_FAIL;
	} 
	memcpy(pBuff, g_MeshTree, sizeof(g_MeshTree));
	g_pVBTree->Unlock();
 

	return TRUE;

}


////////////////////////////////////////////////////////////////////////////
//
void TreeUpdate(float dTime)
{ 	
#define  tree  (*g_pTree[i])
	
	for(int i=0; i<TREE_MAX_; i++)
	{
		if(g_pTree[i] == NULL) continue;		//Ȥ, ������ ���ٸ� ���� ��ҷ�..

		// �̵� ���
		D3DXMatrixTranslation(&g_pTree[i]->mTrans, g_pTree[i]->vPos.x, g_pTree[i]->vPos.y, g_pTree[i]->vPos.z );	

		//	Sphere to Sphere
		//	- ���� �� �߽� ���� �Ÿ��� ����ؼ� �� ���� �������� �պ��� ũ�� ������ ����.
		if (g_pWindMillWing->IsHeroFire == TRUE)
		{
			BoundSphere = g_pWindMillWing->vCenterW - tree.vCenterW;
			if ((D3DXVec3Length(&BoundSphere) < 3.1f) && (g_pTree[i]->TreeState != TREE::ts_FELLDOWN) && (g_pTree[i]->TreeState != TREE::ts_STICK))
			{
				D3DXVec3Cross(&g_pTree[i]->Rot_Axis, &g_pTree[i]->vUp, &g_pHero->vRot); // ����
				g_pTree[i]->TreeState = TREE::ts_HIT;
			}
		}
		
		if ((g_pTree[i]->TreeState == TREE::ts_FELLDOWN || g_pTree[i]->TreeState == TREE::ts_HIT) && g_pTree[i]->TreeState != TREE::ts_STICK)
		{
			BoundSphere2 = g_pHero->vCenterW - tree.vCenterW;

			if ((D3DXVec3Length(&BoundSphere2) < 1.9f))							// ����ο� ���� ������ �浹�ߴ°�?
			{
				g_pHero->temp_mTM = g_pHero->mTM;								// �浹 ����� ����� TM�� ����
				D3DXMatrixInverse(&g_pHero->R_mTM, NULL, &g_pHero->temp_mTM);	// ��� TM�� ������� ���Ѵ�
				g_pTree[i]->temp_mTM = g_pTree[i]->mTM * g_pHero->R_mTM;		// ������ �ӽ� ��Ŀ� �浹 ����� ����TM, �����TM ������� ���Ͽ� �����Ѵ�.
				g_pTree[i]->TreeState = TREE::ts_STICK;							// �¾Ƽ� �����ֵ�, ������, �浹�ߴٸ� �پ�!
			}
		}


		// ���� : '�������� ����' ������ �¾��� ��
		// ���� : ������ õõ�� ������ ���ÿ� �� ���ԵǸ�, ���¸� '���� ����'�� �ٲ۴�.
		if (g_pTree[i]->TreeState == TREE::ts_HIT && g_pTree[i]->TreeState != TREE::ts_FELLDOWN && g_pTree[i]->TreeState != TREE::ts_STICK)
		{
			g_pTree[i]->f_Tangle += dTime * 1.5f; // [ dTime ���� ���� ������ �ӵ��� ����. ũ���ϸ� ������, �۰��ϸ� ������. ]

			if (g_pTree[i]->f_Tangle > D3DXToRadian(90))
			{
				g_pTree[i]->f_Tangle = D3DXToRadian(90);
				g_pTree[i]->TreeState = TREE::ts_FELLDOWN;
			}

			D3DXMatrixRotationAxis(&g_pTree[i]->mRot, &g_pTree[i]->Rot_Axis, g_pTree[i]->f_Tangle);
			g_pTree[i]->mTM = g_pTree[i]->mScale * g_pTree[i]->mRot * g_pTree[i]->mTrans;
		}

		if (g_pTree[i]->TreeState == TREE::ts_FELLDOWN)	// �Ѿ�������
		{
			g_pTree[i]->f_TDelay += dTime * 0.5;		
			
			if (g_pTree[i]->f_TDelay > 0.5)				// ���� �ð� �ڿ�
			{
				g_pTree[i]->f_Talpha += dTime * 0.5;	// õõ�� ������� ��
				if (g_pTree[i]->f_Talpha > 1)
				{
					g_pTree[i]->f_Talpha = 1;
				}
			}
		}

		// ���� : '�����ִ�' �Ǵ� '�����ִ�' ������ ����� �浹���� �΋H�� ����
		// ���� : ���� ������ ����ο� ������.
		if (g_pTree[i]->TreeState == TREE::ts_STICK)
			g_pTree[i]->mTM = g_pTree[i]->temp_mTM * g_pHero->mTM;
		

		if (g_pTree[i]->TreeState == TREE::ts_NONE)		
			g_pTree[i]->mTM = g_pTree[i]->mScale * g_pTree[i]->mRot * g_pTree[i]->mTrans;

		// ���� ������ �浹��, ���� ��ġ ���� "���庯ȯ" ��
		// �������� ���� ��ü��� �Ź� ����� �ʿ�� ��������... 
		// Center(world) = Center(local) * mTM
		//
		D3DXVec3TransformCoord(&tree.vCenterW, &tree.vCenterL, &tree.mTM);

	}  

#undef tree
}


void TreeBSphereDraw(float dTime)
{

	//�浹���� ���������� �ٸ��Ƿ�, ũ�� ����� �ʿ�.
	//������ �����ϸ� �Ͽ� ���.(���� ������ ����ũ��, ����..)
	D3DXMATRIX mTM, mTrans, mScale, mRot;
#define  tree  (*g_pTree[i])

	//������ ���� ���.
	DWORD bWire;
	g_pDevice->GetRenderState(D3DRS_FILLMODE, &bWire);
	g_pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	g_pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);


	// �� ������ �浹�� �׸���...
	//
	for (int i = 0; i<TREE_MAX_; i++)
	{
		if (g_pTree[i] == NULL) continue;								//Ȥ, ������ ���ٸ� ���� ��ҷ�..
		if ( g_pTree[i]->TreeState != TREE::ts_NONE) continue;			//�̹� �浹�� ���� �׸��� ����.��


		//���庯ȯ ����..
		D3DXMatrixScaling(&mScale, tree.fRadius, tree.fRadius, tree.fRadius);
		D3DXMatrixRotationX(&mRot, D3DX_PI*0.5f);
		D3DXMatrixTranslation(&mTrans, tree.vCenterW.x, tree.vCenterW.y, tree.vCenterW.z);
		mTM = mScale * mRot * mTrans;
		g_pDevice->SetTransform(D3DTS_WORLD, &mTM);

		//������. : DXMesh �� VB, FVF ���� ���� ������ �ڵ����� ó����. ��
		g_pTreeMeshSphere->DrawSubset(0);
	}


	//������ �ɼ� ����.
	g_pDevice->SetRenderState(D3DRS_FILLMODE, bWire);
	g_pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

}



////////////////////////////////////////////////////////////////////////////
//
void TreeDraw(float dTime)
{
	if (g_bAlphaB)
	{
		g_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
		g_pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		g_pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	}


	if (g_SeasonState == Ss_SUMMER)
		SetSummer(pTex[0]);

	else if (g_SeasonState == Ss_AUTUMN)
		SetAutumn(pTex[0], 1);

	else if (g_SeasonState == Ss_WINTER)
	{
		// <Stage 0> �ؽ���
		g_pDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_SELECTARG1);
		g_pDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);

		g_pDevice->SetTexture(0, g_bShowFrame ? NULL : pTex[0]);

		// <Stage 1> �ؽ��� + ����ũ
		g_pDevice->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_ADD);
		g_pDevice->SetTextureStageState(1, D3DTSS_COLORARG1, D3DTA_CURRENT);
		g_pDevice->SetTextureStageState(1, D3DTSS_COLORARG2, D3DTA_TEXTURE);

		//g_pDevice->SetTextureStageState(1, D3DTSS_TEXCOORDINDEX, 0);
		g_pDevice->SetTexture(1, g_bShowFrame ? NULL : pTex[1]);

		// <Stage 2> �ؽ��� * ��ǻ��
		g_pDevice->SetTextureStageState(2, D3DTSS_COLOROP, D3DTOP_MODULATE);
		g_pDevice->SetTextureStageState(2, D3DTSS_COLORARG1, D3DTA_CURRENT);
		g_pDevice->SetTextureStageState(2, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
	}

	if (g_bAlphaT)
	{
		g_pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);				//��
		g_pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);			//ũ�ų� ������ ���.��
	}


	for(int i=0; i<TREE_MAX_; i++){
		if(g_pTree[i] == NULL) continue;								//Ȥ, ������ ���ٸ� ���� ��ҷ�..
 		g_pDevice->SetTransform(D3DTS_WORLD, &g_pTree[i]->mTM);			//������  "���� ������ ����" 

		if (g_bAlphaT)
		g_pDevice->SetRenderState(D3DRS_ALPHAREF, (DWORD)(g_pTree[i]->f_Talpha * 255));	//��

		g_pDevice->SetMaterial(&g_pTree[i]->TreeMTL);
		g_pDevice->SetFVF(VERTEX::FVF);
		g_pDevice->SetStreamSource(0, g_pVBTree, 0, sizeof VERTEX);		//���� �޽��� ����̽��� ����Ѵ�. 
		g_pDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 4);				//���� ��� : �ﰢ���� 2��, "LIST" �ɼ� ����.

		DrawVisibleNormal(g_MeshTree, _countof(g_MeshTree));
	}

	//----------------------------------------------------------------
	//�ؽ�ó �������� ���� : �⺻������ ��ȯ
	g_pDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
	g_pDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	g_pDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);

	g_pDevice->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_DISABLE);
	g_pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	g_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
	//----------------------------------------------------------------
	
}





////////////////////////////////////////////////////////////////////////////
//
void TreeRelease()
{	
	SAFE_RELEASE(g_pVBTree);		//������ ���� ������(Mesh) ������...


	for(int i=0; i<TREE_MAX_; i++)
	{		 
		SAFE_DELETE(g_pTree[i]);		//���� ��ü ����...
	}
}



/****************** end of file "Tree.h" ************************/
