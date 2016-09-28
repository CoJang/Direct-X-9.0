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

TREE* g_pTree[TREE_MAX_] = {NULL, };		// 나무 객체 포인터배열..
LPD3DXMESH  g_pTreeMeshSphere = NULL;
D3DXVECTOR3 BoundSphere = { 0, 0, 0 };
D3DXVECTOR3 BoundSphere2 = { 0, 0, 0 };

//나무 메쉬 데이터. 
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

LPDIRECT3DVERTEXBUFFER9	g_pVBTree = NULL;			//정점 버퍼용 포인터.

CHAR*	   g_TextureName[2];
LPDIRECT3DTEXTURE9 pTex[2];

////////////////////////////////////////////////////////////////////////////
//
int TreeInit() 
{
	int i;

	srand(::timeGetTime());

	// 법선벡터 정규화(할 필욘 없지만 비 정규화 값을 작성했을 때를 대비하여)
	for (i = 0; i < _countof(g_MeshTree); ++i)
		D3DXVec3Normalize(&g_MeshTree[i].vNormal, &g_MeshTree[i].vNormal);

	g_TextureName[0] = "./Data/tree01S.dds";

	if (FAILED(D3DXCreateTextureFromFile(g_pDevice, g_TextureName[0], &pTex[0])))
	{
		MessageBox(NULL, "(나무)텍스쳐 로드 실패.", "에러", MB_ICONERROR | MB_OK);
		return E_FAIL;
	}

	g_TextureName[1] = "./Data/TREE_mask2.png";

	if (FAILED(D3DXCreateTextureFromFile(g_pDevice, g_TextureName[1], &pTex[1])))
	{
		MessageBox(NULL, "(나무)텍스쳐 로드 실패.", "에러", MB_ICONERROR | MB_OK);
		return E_FAIL;
	}

	for(i=0; i<TREE_MAX_; i++)
	{	 
		g_pTree[i] = new TREE;
		assert(g_pTree[i] != NULL);  
		 
 		g_pTree[i]->vPos.x = (float)(rand()%128 - 64);		//나무 시작위치.
		g_pTree[i]->vPos.y = 0.0f;	 
		g_pTree[i]->vPos.z = (float)(rand()%128 - 64);	 
		g_pTree[i]->vUp = D3DXVECTOR3(0, 1, 0);
		g_pTree[i]->Rot_Axis = D3DXVECTOR3(0, 0, 0);
		g_pTree[i]->TreeState = TREE::ts_NONE;
		g_pTree[i]->f_Tangle = 0.0f;
		g_pTree[i]->f_Talpha = 0.3f;
		g_pTree[i]->f_TDelay = 0;

		D3DXMatrixIdentity(&g_pTree[i]->mTM);				//행렬 변수의 초기화.
		D3DXMatrixIdentity(&g_pTree[i]->mRot);
		D3DXMatrixIdentity(&g_pTree[i]->mScale);
		D3DXMatrixIdentity(&g_pTree[i]->mTrans);
		D3DXMatrixIdentity(&g_pTree[i]->temp_mTM);
		g_pTree[i]->mScale[0] *= 1.5f;
		g_pTree[i]->mScale[5] *= 3.0f;

		//충돌 정보 설정.★
		g_pTree[i]->vCenterL = D3DXVECTOR3(0, 1, 0);		//충돌구 중심점 : 나무의 중간 위치.(로컬공간)★
		g_pTree[i]->vCenterW = D3DXVECTOR3(0, 0, 0);		//중돌구 중심점 : 월드좌표★
		g_pTree[i]->fRadius = 1.1f;							//충돌구 반경.★

		ZeroMemory(&g_pTree[i]->TreeMTL, sizeof(g_pTree[i]->TreeMTL));
		g_pTree[i]->TreeMTL.Diffuse = { 1, 1, 1, 1 };
		g_pTree[i]->TreeMTL.Ambient = { 0.4f, 0.4f, 0.4f, 1 };
	}

	

	// 나무용 정점 버퍼 생성.: 나무 종류가 하나이므로, 이것을 재활용 할것이다.
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

	//버퍼 채우기.
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
		if(g_pTree[i] == NULL) continue;		//혹, 나무가 없다면 다음 요소로..

		// 이동 행렬
		D3DXMatrixTranslation(&g_pTree[i]->mTrans, g_pTree[i]->vPos.x, g_pTree[i]->vPos.y, g_pTree[i]->vPos.z );	

		//	Sphere to Sphere
		//	- 구의 두 중심 간의 거리를 계산해서 두 구의 반지름의 합보다 크면 만나지 않음.
		if (g_pWindMillWing->IsHeroFire == TRUE)
		{
			BoundSphere = g_pWindMillWing->vCenterW - tree.vCenterW;
			if ((D3DXVec3Length(&BoundSphere) < 3.1f) && (g_pTree[i]->TreeState != TREE::ts_FELLDOWN) && (g_pTree[i]->TreeState != TREE::ts_STICK))
			{
				D3DXVec3Cross(&g_pTree[i]->Rot_Axis, &g_pTree[i]->vUp, &g_pHero->vRot); // 외적
				g_pTree[i]->TreeState = TREE::ts_HIT;
			}
		}
		
		if ((g_pTree[i]->TreeState == TREE::ts_FELLDOWN || g_pTree[i]->TreeState == TREE::ts_HIT) && g_pTree[i]->TreeState != TREE::ts_STICK)
		{
			BoundSphere2 = g_pHero->vCenterW - tree.vCenterW;

			if ((D3DXVec3Length(&BoundSphere2) < 1.9f))							// 히어로와 누운 나무가 충돌했는가?
			{
				g_pHero->temp_mTM = g_pHero->mTM;								// 충돌 당시의 히어로 TM을 저장
				D3DXMatrixInverse(&g_pHero->R_mTM, NULL, &g_pHero->temp_mTM);	// 당시 TM의 역행렬을 구한다
				g_pTree[i]->temp_mTM = g_pTree[i]->mTM * g_pHero->R_mTM;		// 나무의 임시 행렬에 충돌 당시의 나무TM, 히어로TM 역행렬을 곱하여 저장한다.
				g_pTree[i]->TreeState = TREE::ts_STICK;							// 맞아서 눕고있든, 누웠든, 충돌했다면 붙어!
			}
		}


		// 조건 : '누워있지 않은' 나무가 맞았을 때
		// 실행 : 나무를 천천히 눕힘과 동시에 다 눕게되면, 상태를 '누운 나무'로 바꾼다.
		if (g_pTree[i]->TreeState == TREE::ts_HIT && g_pTree[i]->TreeState != TREE::ts_FELLDOWN && g_pTree[i]->TreeState != TREE::ts_STICK)
		{
			g_pTree[i]->f_Tangle += dTime * 1.5f; // [ dTime 뒤의 숫자 곱으로 속도를 조절. 크게하면 빠르게, 작게하면 느리게. ]

			if (g_pTree[i]->f_Tangle > D3DXToRadian(90))
			{
				g_pTree[i]->f_Tangle = D3DXToRadian(90);
				g_pTree[i]->TreeState = TREE::ts_FELLDOWN;
			}

			D3DXMatrixRotationAxis(&g_pTree[i]->mRot, &g_pTree[i]->Rot_Axis, g_pTree[i]->f_Tangle);
			g_pTree[i]->mTM = g_pTree[i]->mScale * g_pTree[i]->mRot * g_pTree[i]->mTrans;
		}

		if (g_pTree[i]->TreeState == TREE::ts_FELLDOWN)	// 넘어졌으면
		{
			g_pTree[i]->f_TDelay += dTime * 0.5;		
			
			if (g_pTree[i]->f_TDelay > 0.5)				// 일정 시간 뒤에
			{
				g_pTree[i]->f_Talpha += dTime * 0.5;	// 천천히 사라지게 함
				if (g_pTree[i]->f_Talpha > 1)
				{
					g_pTree[i]->f_Talpha = 1;
				}
			}
		}

		// 조건 : '누워있는' 또는 '눕고있는' 나무가 히어로 충돌구와 부딫힌 상태
		// 실행 : 위의 나무를 히어로에 붙힌다.
		if (g_pTree[i]->TreeState == TREE::ts_STICK)
			g_pTree[i]->mTM = g_pTree[i]->temp_mTM * g_pHero->mTM;
		

		if (g_pTree[i]->TreeState == TREE::ts_NONE)		
			g_pTree[i]->mTM = g_pTree[i]->mScale * g_pTree[i]->mRot * g_pTree[i]->mTrans;

		// 개별 나무의 충돌구, 월드 위치 산출 "월드변환" ★
		// 움직임이 없는 개체라면 매번 계산할 필요는 없겠지요... 
		// Center(world) = Center(local) * mTM
		//
		D3DXVec3TransformCoord(&tree.vCenterW, &tree.vCenterL, &tree.mTM);

	}  

#undef tree
}


void TreeBSphereDraw(float dTime)
{

	//충돌구는 오브제별로 다르므로, 크기 계산이 필요.
	//적절히 스케일링 하여 사용.(현재 나무는 동일크기, 생략..)
	D3DXMATRIX mTM, mTrans, mScale, mRot;
#define  tree  (*g_pTree[i])

	//렌더링 상태 기억.
	DWORD bWire;
	g_pDevice->GetRenderState(D3DRS_FILLMODE, &bWire);
	g_pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	g_pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);


	// 각 나무별 충돌구 그리기...
	//
	for (int i = 0; i<TREE_MAX_; i++)
	{
		if (g_pTree[i] == NULL) continue;								//혹, 나무가 없다면 다음 요소로..
		if ( g_pTree[i]->TreeState != TREE::ts_NONE) continue;			//이미 충돌된 것은 그리지 않음.★


		//월드변환 설정..
		D3DXMatrixScaling(&mScale, tree.fRadius, tree.fRadius, tree.fRadius);
		D3DXMatrixRotationX(&mRot, D3DX_PI*0.5f);
		D3DXMatrixTranslation(&mTrans, tree.vCenterW.x, tree.vCenterW.y, tree.vCenterW.z);
		mTM = mScale * mRot * mTrans;
		g_pDevice->SetTransform(D3DTS_WORLD, &mTM);

		//렌더링. : DXMesh 는 VB, FVF 등의 기하 설정이 자동으로 처리됨. ★
		g_pTreeMeshSphere->DrawSubset(0);
	}


	//렌더링 옵션 복구.
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
		// <Stage 0> 텍스쳐
		g_pDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_SELECTARG1);
		g_pDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);

		g_pDevice->SetTexture(0, g_bShowFrame ? NULL : pTex[0]);

		// <Stage 1> 텍스쳐 + 마스크
		g_pDevice->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_ADD);
		g_pDevice->SetTextureStageState(1, D3DTSS_COLORARG1, D3DTA_CURRENT);
		g_pDevice->SetTextureStageState(1, D3DTSS_COLORARG2, D3DTA_TEXTURE);

		//g_pDevice->SetTextureStageState(1, D3DTSS_TEXCOORDINDEX, 0);
		g_pDevice->SetTexture(1, g_bShowFrame ? NULL : pTex[1]);

		// <Stage 2> 텍스쳐 * 디퓨즈
		g_pDevice->SetTextureStageState(2, D3DTSS_COLOROP, D3DTOP_MODULATE);
		g_pDevice->SetTextureStageState(2, D3DTSS_COLORARG1, D3DTA_CURRENT);
		g_pDevice->SetTextureStageState(2, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
	}

	if (g_bAlphaT)
	{
		g_pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);				//★
		g_pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);			//크거나 같으면 통과.★
	}


	for(int i=0; i<TREE_MAX_; i++){
		if(g_pTree[i] == NULL) continue;								//혹, 나무가 없다면 다음 요소로..
 		g_pDevice->SetTransform(D3DTS_WORLD, &g_pTree[i]->mTM);			//나무을  "월드 공간에 놓기" 

		if (g_bAlphaT)
		g_pDevice->SetRenderState(D3DRS_ALPHAREF, (DWORD)(g_pTree[i]->f_Talpha * 255));	//★

		g_pDevice->SetMaterial(&g_pTree[i]->TreeMTL);
		g_pDevice->SetFVF(VERTEX::FVF);
		g_pDevice->SetStreamSource(0, g_pVBTree, 0, sizeof VERTEX);		//나무 메쉬를 디바이스에 등록한다. 
		g_pDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 4);				//나무 출력 : 삼각형이 2개, "LIST" 옵션 주의.

		DrawVisibleNormal(g_MeshTree, _countof(g_MeshTree));
	}

	//----------------------------------------------------------------
	//텍스처 스테이지 설정 : 기본값으로 전환
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
	SAFE_RELEASE(g_pVBTree);		//나무용 정점 데이터(Mesh) 릴리즈...


	for(int i=0; i<TREE_MAX_; i++)
	{		 
		SAFE_DELETE(g_pTree[i]);		//나무 객체 제거...
	}
}



/****************** end of file "Tree.h" ************************/
