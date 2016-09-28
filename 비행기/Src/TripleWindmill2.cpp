//
// Windmill.cpp
//
//
// 2007.01.25. Kihong Kim / mad_dog@hanmail.net
//

#include "windows.h"
#include "assert.h"
#include "Device.h"
#include "Render.h"

#include "Vertex.h"
#include "Normal.h"

#include "Map.h"
#include "Windmill.h"
#include "Hero.h"
#include "Season.h"



////////////////////////////////////////////////////////////////////////////
//
WINDMILL* g_pTripleWindmill2 = NULL;

WINDMILL_WING* g_pWindMillWing = NULL;
LPD3DXMESH  g_pWingMeshSphere = NULL;

D3DMATERIAL9 g_TriWindMTL2;
D3DMATERIAL9 g_TriWindWingMTL2;

// 풍차 몸체 : 피라미드 형태.
VERTEX g_MeshTri2Windmill_Body[] = {
	// 4방향의 벽체..
	{ D3DXVECTOR3(0, 3, 0), D3DXVECTOR3(0, 0, -1), D3DXVECTOR2(0.242f, 0.0f) },
	{ D3DXVECTOR3(1, 0, -1), D3DXVECTOR3(0, 0, -1), D3DXVECTOR2(0.498f, 1.0f) },
	{ D3DXVECTOR3(-1, 0, -1), D3DXVECTOR3(0, 0, -1), D3DXVECTOR2(0.0f, 1.0f) },

	{ D3DXVECTOR3(-1, 0, 1), D3DXVECTOR3(0, 0, 1), D3DXVECTOR2(0.0f, 1.0f) },
	{ D3DXVECTOR3(1, 0, 1), D3DXVECTOR3(0, 0, 1), D3DXVECTOR2(0.498f, 1.0f) },
	{ D3DXVECTOR3(0, 3, 0), D3DXVECTOR3(0, 0, 1), D3DXVECTOR2(0.242f, 0.0f) },

	{ D3DXVECTOR3(-1, 0, -1), D3DXVECTOR3(-1, 0, 0), D3DXVECTOR2(0.498f, 1.0f) },
	{ D3DXVECTOR3(-1, 0, 1), D3DXVECTOR3(-1, 0, 0), D3DXVECTOR2(0.0f, 1.0f) },
	{ D3DXVECTOR3(0, 3, 0), D3DXVECTOR3(-1, 0, 0), D3DXVECTOR2(0.242f, 0.0f) },

	{ D3DXVECTOR3(0, 3, 0), D3DXVECTOR3(1, 0, 0), D3DXVECTOR2(0.242f, 0.0f) },
	{ D3DXVECTOR3(1, 0, 1), D3DXVECTOR3(1, 0, 0), D3DXVECTOR2(0.0f, 1.0f) },
	{ D3DXVECTOR3(1, 0, -1), D3DXVECTOR3(1, 0, 0), D3DXVECTOR2(0.498f, 1.0f) },

	//'밑면' 은 필요 없다..
};

//풍차 날개.
VERTEX g_MeshTri2Windmill_Wing[] = {
	{ D3DXVECTOR3(-2, -0.5, 0), D3DXVECTOR3(0, 0, -1), D3DXVECTOR2(0.710f, 0.978f) },
	{ D3DXVECTOR3(-2, 0.3, 0), D3DXVECTOR3(0, 0, -1), D3DXVECTOR2(0.574f, 0.978f) },
	{ D3DXVECTOR3(0, -0.5, 0), D3DXVECTOR3(0, 0, -1), D3DXVECTOR2(0.710f, 0.472f) },

	{ D3DXVECTOR3(0, -0.5, 0), D3DXVECTOR3(0, 0, -1), D3DXVECTOR2(0.710f, 0.472f) },
	{ D3DXVECTOR3(0, 0.3, 0), D3DXVECTOR3(0, 0, -1), D3DXVECTOR2(0.574f, 0.472f) },
	{ D3DXVECTOR3(-2, 0.3, 0), D3DXVECTOR3(0, 0, -1), D3DXVECTOR2(0.574f, 0.978f) },

	{ D3DXVECTOR3(2, -0.3, 0), D3DXVECTOR3(0, 0, -1), D3DXVECTOR2(0.574f, 0.978f) },
	{ D3DXVECTOR3(2, 0.5, 0), D3DXVECTOR3(0, 0, -1), D3DXVECTOR2(0.710f, 0.978f) },
	{ D3DXVECTOR3(0, -0.3, 0), D3DXVECTOR3(0, 0, -1), D3DXVECTOR2(0.574f, 0.472f) },

	{ D3DXVECTOR3(0, -0.3, 0), D3DXVECTOR3(0, 0, -1), D3DXVECTOR2(0.574f, 0.472f) },
	{ D3DXVECTOR3(0, 0.5, 0), D3DXVECTOR3(0, 0, -1), D3DXVECTOR2(0.710f, 0.472f) },
	{ D3DXVECTOR3(2, 0.5, 0), D3DXVECTOR3(0, 0, -1), D3DXVECTOR2(0.710f, 0.978f) },

	{ D3DXVECTOR3(-0.3, -2, 0), D3DXVECTOR3(0, 0, -1), D3DXVECTOR2(0.574f, 0.978f) },
	{ D3DXVECTOR3(0.5, -2, 0), D3DXVECTOR3(0, 0, -1), D3DXVECTOR2(0.710f, 0.978f) },
	{ D3DXVECTOR3(-0.3, 0, 0), D3DXVECTOR3(0, 0, -1), D3DXVECTOR2(0.574f, 0.472f) },

	{ D3DXVECTOR3(-0.3, 0, 0), D3DXVECTOR3(0, 0, -1), D3DXVECTOR2(0.574f, 0.472f) },
	{ D3DXVECTOR3(0.5, 0, 0), D3DXVECTOR3(0, 0, -1), D3DXVECTOR2(0.710f, 0.472f) },
	{ D3DXVECTOR3(0.5, -2, 0), D3DXVECTOR3(0, 0, -1), D3DXVECTOR2(0.710f, 0.978f) },

	{ D3DXVECTOR3(-0.5, 2, 0), D3DXVECTOR3(0, 0, -1), D3DXVECTOR2(0.710f, 0.978f) },
	{ D3DXVECTOR3(0.3, 2, 0), D3DXVECTOR3(0, 0, -1), D3DXVECTOR2(0.574f, 0.978f) },
	{ D3DXVECTOR3(-0.5, 0, 0), D3DXVECTOR3(0, 0, -1), D3DXVECTOR2(0.710f, 0.472f) },

	{ D3DXVECTOR3(-0.5, 0, 0), D3DXVECTOR3(0, 0, -1), D3DXVECTOR2(0.710f, 0.472f) },
	{ D3DXVECTOR3(0.3, 0, 0), D3DXVECTOR3(0, 0, -1), D3DXVECTOR2(0.574f, 0.472f) },
	{ D3DXVECTOR3(0.3, 2, 0), D3DXVECTOR3(0, 0, -1), D3DXVECTOR2(0.574f, 0.978f) },
};

VERTEX g_MeshTriWindMillBottom2[] = {

	//바닥.  ( Face#1)
	{ D3DXVECTOR3(1.0, -1.0, 1.0), D3DXVECTOR3(0.0, 0.0, 0.0), D3DXVECTOR2(0.0, 0.0) },
	{ D3DXVECTOR3(-1.0, -1.0, 1.0), D3DXVECTOR3(0.0, 0.0, 0.0), D3DXVECTOR2(1.0, 0.0) },
	{ D3DXVECTOR3(-1.0, -1.0, -1.0), D3DXVECTOR3(0.0, 0.0, 0.0), D3DXVECTOR2(1.0, 1.0) },
	//		 ( Face#2)
	{ D3DXVECTOR3(1.0, -1.0, 1.0), D3DXVECTOR3(0.0, 0.0, 0.0), D3DXVECTOR2(0.0, 0.0) },
	{ D3DXVECTOR3(-1.0, -1.0, -1.0), D3DXVECTOR3(0.0, 0.0, 0.0), D3DXVECTOR2(1.0, 1.0) },
	{ D3DXVECTOR3(1.0, -1.0, -1.0), D3DXVECTOR3(0.0, 0.0, 0.0), D3DXVECTOR2(0.0, 1.0) },

};


LPDIRECT3DVERTEXBUFFER9	g_pVBTriWindmill_Body_2 = NULL;			//정점 버퍼용 포인터.(몸체)
LPDIRECT3DVERTEXBUFFER9	g_pVBTriWindmill_Wing_2[3] = { NULL, NULL, NULL };			//정점 버퍼용 포인터.(날개1)
LPDIRECT3DVERTEXBUFFER9	g_pVBTriWindmill_Bottom2 = NULL;	//정점 버퍼용 포인터.(바닥)



////////////////////////////////////////////////////////////////////////////
//
int TripleWindmillInit2(D3DXVECTOR3 vPos)
{
	int i;

	for (i = 0; i < _countof(g_MeshTri2Windmill_Body); ++i)
		D3DXVec3Normalize(&g_MeshTri2Windmill_Body[i].vNormal, &g_MeshTri2Windmill_Body[i].vNormal);

	for (i = 0; i < _countof(g_MeshTri2Windmill_Wing); ++i)
		D3DXVec3Normalize(&g_MeshTri2Windmill_Wing[i].vNormal, &g_MeshTri2Windmill_Wing[i].vNormal);

	g_pTripleWindmill2 = new WINDMILL;
	assert(g_pTripleWindmill2 != NULL);
	g_pTripleWindmill2->bShowInnerLight = FALSE;

	g_pWindMillWing = new WINDMILL_WING;
	heroFireState = hf_NONE;

#define  wing  (* g_pWindMillWing)
	wing.vPos = D3DXVECTOR3(0, 0, 0);

	g_pWindMillWing->vCenterL = D3DXVECTOR3(0, 0, 0);			// 초기화
	g_pWindMillWing->vCenterW = D3DXVECTOR3(0, 0, 0);
	g_pWindMillWing->vNormal = D3DXVECTOR3(0, 0, 0);
	g_pWindMillWing->fRadius = 2.0f;							// 충돌구 반경.★

	D3DXMatrixIdentity(&wing.mTM);			//행렬 변수의 초기화.
	D3DXMatrixIdentity(&wing.mRot);
	D3DXMatrixIdentity(&wing.mScale);
	D3DXMatrixIdentity(&wing.mTrans);
	
#undef wing

	// [ 풍차 바디 행렬변수 초기화 및 Y축 2배 스케일 ]
	g_pTripleWindmill2->vPos = vPos;								//풍차 시작 위치
	g_pTripleWindmill2->vRot = D3DXVECTOR3(0, 0, 0);				//풍차 회전 없음.
	D3DXMatrixIdentity(&g_pTripleWindmill2->mTM);
	D3DXMatrixIdentity(&g_pTripleWindmill2->mRot);
	D3DXMatrixIdentity(&g_pTripleWindmill2->mScale);
	D3DXMatrixIdentity(&g_pTripleWindmill2->mTrans);
	g_pTripleWindmill2->mScale[5] *= 2.0f;


	for (i = 0; i < 3; i++)
	{
		D3DXMatrixIdentity(&g_pTripleWindmill2->Wing[i].mTM);
		D3DXMatrixIdentity(&g_pTripleWindmill2->Wing[i].mRot);
		D3DXMatrixIdentity(&g_pTripleWindmill2->Wing[i].mScale);
		D3DXMatrixIdentity(&g_pTripleWindmill2->Wing[i].mTrans);
	}

	// [ 날개1 행렬변수 초기화 및 1.8배 스케일 ]
	g_pTripleWindmill2->Wing[0].vPos = D3DXVECTOR3(0, 3, -1.0f);
	D3DXMatrixScaling(&g_pTripleWindmill2->Wing[0].mScale, 1.5f, 1.5f, 1.5f);

	// [ 날개2 행렬변수 초기화 ]
	g_pTripleWindmill2->Wing[1].vPos = D3DXVECTOR3(0, 0, -0.5f);

	// [ 날개3 행렬변수 초기화 및 0.8배 스케일 ]
	g_pTripleWindmill2->Wing[2].vPos = D3DXVECTOR3(0, 0, -0.5f);
	D3DXMatrixScaling(&g_pTripleWindmill2->Wing[2].mScale, 0.8f, 0.8f, 0.8f);

	ZeroMemory(&g_TriWindMTL2, sizeof(g_TriWindMTL2));
	g_TriWindMTL2.Diffuse = { 1, 1, 1, 1 };
	g_TriWindMTL2.Ambient = { 0.8f, 0.8f, 0.8f, 1 };


	ZeroMemory(&g_TriWindWingMTL2, sizeof(g_TriWindWingMTL2));
	g_TriWindWingMTL2.Diffuse = { 1, 1, 1, 1 };
	g_TriWindWingMTL2.Ambient = { 0.8f, 0.8f, 0.8f, 1 };
	
	// 풍차 몸체용. 정점 버퍼 생성.
	if (FAILED(g_pDevice->CreateVertexBuffer(
		sizeof(g_MeshTri2Windmill_Body),	//★	
		0,
		VERTEX::FVF,					//★
		D3DPOOL_MANAGED,
		&g_pVBTriWindmill_Body_2,			//★
		NULL)))
	{
		return E_FAIL;
	}

	//버퍼 채우기.
	VOID*	pBuff;
	if (FAILED(g_pVBTriWindmill_Body_2->Lock(0, sizeof(g_MeshTri2Windmill_Body), (void**)&pBuff, 0)))
	{
		return E_FAIL;
	}

	memcpy(pBuff, g_MeshTri2Windmill_Body, sizeof(g_MeshTri2Windmill_Body));
	g_pVBTriWindmill_Body_2->Unlock();


	//
	// 풍차 날개용 정점 버퍼 생성.
	//
	for (int i = 0; i < 3; i++)
	{

		if (FAILED(g_pDevice->CreateVertexBuffer(
			sizeof(g_MeshTri2Windmill_Wing),	//★	
			0,
			VERTEX::FVF,					//★
			D3DPOOL_MANAGED,
			&g_pVBTriWindmill_Wing_2[i],			//★
			NULL)))
		{
			return E_FAIL;
		}

		//버퍼 채우기.
		if (FAILED(g_pVBTriWindmill_Wing_2[i]->Lock(0, sizeof(g_MeshTri2Windmill_Wing), (void**)&pBuff, 0)))
		{
			return E_FAIL;
		}

		memcpy(pBuff, g_MeshTri2Windmill_Wing, sizeof(g_MeshTri2Windmill_Wing));
		g_pVBTriWindmill_Wing_2[i]->Unlock();

	}

	//
	// 풍차 바닥용 정점 버퍼 생성.
	//
	if (FAILED(g_pDevice->CreateVertexBuffer(
		sizeof(g_MeshTriWindMillBottom2),	//★	
		0,
		VERTEX::FVF,					//★
		D3DPOOL_MANAGED,
		&g_pVBTriWindmill_Bottom2,			//★
		NULL)))
	{
		return E_FAIL;
	}

	//버퍼 채우기.
	if (FAILED(g_pVBTriWindmill_Bottom2->Lock(0, sizeof(g_MeshTriWindMillBottom2), (void**)&pBuff, 0)))
	{
		return E_FAIL;
	}

	memcpy(pBuff, g_MeshTriWindMillBottom2, sizeof(g_MeshTriWindMillBottom2));
	g_pVBTriWindmill_Bottom2->Unlock();


	return TRUE;
}




////////////////////////////////////////////////////////////////////////////
//
void TripleWindmillUpdate2(float dTime)
{

	// 히어로의 Rotate mat * Trans mat
	static D3DXMATRIX HeroMatRT;

	// 총알의 상대적 위치
	static float BulletPos = 0;

	D3DXMATRIX RotateWing;
	D3DXMatrixIdentity(&RotateWing);

	if (heroFireState == hf_NONE)
		g_pWindMillWing->IsHeroFire = FALSE;

	if (IsKeyUp('C') && heroFireState == hf_NONE)
	{
		heroFireState = hf_RELOAD;
		g_pWindMillWing->IsHeroFire = FALSE;
	}

	if (IsKeyUp('V') && heroFireState == hf_RELOAD)
	{
		heroFireState = hf_FIRE;
		g_pWindMillWing->IsHeroFire = TRUE;
		g_pHero->vRot = g_pHero->vDir;
	}



	//-------------------------------------------------------------------------- 
	// 풍차 몸체 행렬 계산.
	//--------------------------------------------------------------------------  

	// 풍차 몸체 이동  
	static float mov = 10.0f;

	if (IsKeyDown('I'))		g_pTripleWindmill2->vPos.z += mov * dTime;
	if (IsKeyDown('K'))		g_pTripleWindmill2->vPos.z -= mov * dTime;
	if (IsKeyDown('L'))		g_pTripleWindmill2->vPos.x += mov * dTime;
	if (IsKeyDown('J'))		g_pTripleWindmill2->vPos.x -= mov * dTime;

	D3DXMatrixTranslation(&g_pTripleWindmill2->mTrans,
		g_pTripleWindmill2->vPos.x,
		g_pTripleWindmill2->vPos.y,
		g_pTripleWindmill2->vPos.z);		// 풍차 몸체 이동행렬 만들기.	처음에 한번만 계산. ★


	// 풍차 회전
	//
	static float WM_angle = 0.0f;

	if (IsKeyDown('U'))
	{
		WM_angle += D3DX_PI * dTime;
	}
	if (IsKeyDown('O'))
	{
		WM_angle -= D3DX_PI * dTime;
	}

	D3DXMatrixRotationY(&g_pTripleWindmill2->mRot, WM_angle);


	// '풍차 최종 변환 값 - TM -  계산하기 :  
	// 
	// BodyTM = S * R * T
	//
	//g_pWindmill->mTM = g_pWindmill->mTrans;		
	D3DXMatrixMultiply(&g_pTripleWindmill2->mTM, &g_pTripleWindmill2->mScale, &g_pTripleWindmill2->mRot);
	D3DXMatrixMultiply(&g_pTripleWindmill2->mTM, &g_pTripleWindmill2->mTM, &g_pTripleWindmill2->mTrans);


	//-------------------------------------------------------------------------- 
	// 날개 행렬 계산.
	//--------------------------------------------------------------------------

	//날개1 이동 행렬 만들기. 
	for (int i = 0; i < 3; i++)
	{
		D3DXMatrixTranslation(&g_pTripleWindmill2->Wing[i].mTrans, g_pTripleWindmill2->Wing[i].vPos.x, g_pTripleWindmill2->Wing[i].vPos.y, g_pTripleWindmill2->Wing[i].vPos.z);
	}

	static float angle[3] = { 0.0f, 0.0f, 0.0f };
	static float speed = 1;

	if (g_SeasonState == Ss_WINTER)
	{
		speed -= dTime * 0.5;
		if (speed <= 0) speed = 0;
		angle[0] += D3DX_PI * dTime / 4 * speed;				//180(도)/sec  즉, 1회전에 4초 소요.
		D3DXMatrixRotationZ(&g_pTripleWindmill2->Wing[0].mRot, angle[0]);
		angle[1] += D3DX_PI * -dTime * speed;					//180(도)/sec  즉, 1회전에 2초 소요.
		D3DXMatrixRotationZ(&g_pTripleWindmill2->Wing[1].mRot, angle[1]);
		angle[2] += D3DX_PI * dTime * 2 * speed;				//180(도)/sec  즉, 1회전에 1초 소요.
		D3DXMatrixRotationZ(&g_pTripleWindmill2->Wing[2].mRot, angle[2]);
	}
	else if (g_SeasonState != Ss_WINTER)
	{
		if (speed < 1) speed += dTime * 0.5;
		else if (speed >= 1) speed = 1;
		angle[0] += D3DX_PI * dTime / 4 * speed;				
		D3DXMatrixRotationZ(&g_pTripleWindmill2->Wing[0].mRot, angle[0]);
		angle[1] += D3DX_PI * -dTime * speed;					
		D3DXMatrixRotationZ(&g_pTripleWindmill2->Wing[1].mRot, angle[1]);
		angle[2] += D3DX_PI * dTime * 2 * speed;				
		D3DXMatrixRotationZ(&g_pTripleWindmill2->Wing[2].mRot, angle[2]);
	}

	// 풍차 친구들 SRT행렬 TM행렬로 합치기
	for (int i = 0; i < 3; i++)
	{
		g_pTripleWindmill2->Wing[i].mTM = g_pTripleWindmill2->Wing[i].mScale * g_pTripleWindmill2->Wing[i].mRot * g_pTripleWindmill2->Wing[i].mTrans;
	}


	{ // 풍차 친구들에게 엄마 달아주기
		// 풍차 1
		switch (heroFireState)
		{
		case hf_RELOAD:
			// 히어로의 방향과 위치를 기억한다
			// 스케일 값은 노필요
			HeroMatRT = g_pHero->mRot * g_pHero->mTrans;

			// 히어로에 붙어서 움직이도록
			g_pTripleWindmill2->Wing[0].mTM *= HeroMatRT;

			// 총알의 상대 위치를 초기화
			BulletPos = 0;
			break;

		case hf_FIRE:{
			// 총알의 상대 위치를 증가시킴
			BulletPos += 30.0f * dTime;
			if (BulletPos > 20.f)
				heroFireState = hf_NONE;

			// 월드행렬이 단위행렬일 때 히어로가 바라보는 방향은
			// (0, 0, -1) 이므로 이 방향에 BulletPos를 곱한 값
			D3DXVECTOR3 bulletDir = { 0, 0, -BulletPos };

			D3DXMATRIX tmpMat;
			D3DXMatrixIdentity(&tmpMat);

			// 히어로의 방향과 위치를 곱한 행렬에서 방향 행렬만 추출한다.
			tmpMat[0] = HeroMatRT[0];
			tmpMat[2] = HeroMatRT[2];
			tmpMat[8] = HeroMatRT[8];
			tmpMat[10] = HeroMatRT[10];

			// 앞서 추출한 회전 행렬을 이용하여 bulletDir벡터를 변환한다.
			// bulletDir = 히어로 진행방향
			D3DXVec3TransformCoord(&bulletDir, &bulletDir, &tmpMat);
			D3DXMatrixTranslation(&tmpMat, bulletDir.x, bulletDir.y, bulletDir.z);

			g_pTripleWindmill2->Wing[0].mTM *= HeroMatRT * tmpMat;

		}
			break;

		default:
			D3DXMatrixInverse(&g_pTripleWindmill2->Sinverse, NULL, &g_pTripleWindmill2->mScale);
			g_pTripleWindmill2->Wing[0].mTM *= g_pTripleWindmill2->Sinverse;	// [ 부모의 스케일에 영향을 받지 않기 위한 역행렬 곱 ]
			g_pTripleWindmill2->Wing[0].mTM *= g_pTripleWindmill2->mTM;			// [ (날개 1 -> 바디) 부착 ]
			break;
		}

		// 풍차 2
		D3DXMatrixInverse(&g_pTripleWindmill2->Wing[0].Rinverse, NULL, &g_pTripleWindmill2->Wing[0].mRot);
		D3DXMatrixInverse(&g_pTripleWindmill2->Wing[0].Sinverse, NULL, &g_pTripleWindmill2->Wing[0].mScale);
		g_pTripleWindmill2->Wing[1].mTM *= g_pTripleWindmill2->Wing[0].Sinverse;
		g_pTripleWindmill2->Wing[1].mTM *= g_pTripleWindmill2->Wing[0].Rinverse;
		g_pTripleWindmill2->Wing[1].mTM *= g_pTripleWindmill2->Wing[0].mTM;

		// 풍차 3
		D3DXMatrixInverse(&g_pTripleWindmill2->Wing[1].Rinverse, NULL, &g_pTripleWindmill2->Wing[1].mRot);
		D3DXMatrixInverse(&g_pTripleWindmill2->Wing[1].Sinverse, NULL, &g_pTripleWindmill2->Wing[1].mScale);
		g_pTripleWindmill2->Wing[2].mTM *= g_pTripleWindmill2->Wing[1].Rinverse;
		g_pTripleWindmill2->Wing[2].mTM *= g_pTripleWindmill2->Wing[1].mTM;

		/* 날개에 충돌구체 부착 */
#define  wing  (* g_pWindMillWing)

		D3DXMatrixTranslation(&wing.mTrans, wing.vPos.x, wing.vPos.y, wing.vPos.z);
		wing.mTM = wing.mScale * wing.mRot * wing.mTrans;
		g_pWindMillWing->vCenterW = g_pTripleWindmill2->Wing[0].vPos;
		D3DXVec3TransformCoord(&wing.vCenterW, &wing.vCenterL, &g_pTripleWindmill2->Wing[0].mTM);

#undef wing

	}

	//-------------------------------------------------------------------------- 
	// 풍차 바닥 행렬 계산.
	//--------------------------------------------------------------------------  
	D3DXMatrixScaling(&g_pTripleWindmill2->Bottom.mScale, 1.70, 1, 1.70);
	g_pTripleWindmill2->Bottom.mRot = g_pTripleWindmill2->mRot;
	D3DXMatrixTranslation(&g_pTripleWindmill2->Bottom.mTrans, g_pTripleWindmill2->vPos.x, g_pTripleWindmill2->vPos.y + 1, g_pTripleWindmill2->vPos.z);

	g_pTripleWindmill2->Bottom.mTM = g_pTripleWindmill2->Bottom.mScale * g_pTripleWindmill2->Bottom.mRot * g_pTripleWindmill2->Bottom.mTrans;
}

void WingBSphereDraw(float dTime)
{

	//충돌구는 오브제별로 다르므로, 크기 계산이 필요.
	//적절히 스케일링 하여 사용.(현재 나무는 동일크기, 생략..)
	D3DXMATRIX mTM, mTrans, mScale, mRot;
#define  wing  (* g_pWindMillWing)
	//렌더링 상태 기억.
	DWORD bWire;
	g_pDevice->GetRenderState(D3DRS_FILLMODE, &bWire);
	g_pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	g_pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);


	//월드변환 설정..
	D3DXMatrixScaling(&mScale, wing.fRadius, wing.fRadius, wing.fRadius);
	D3DXMatrixRotationX(&mRot, D3DX_PI*0.5f);
	D3DXMatrixTranslation(&mTrans, wing.vCenterW.x, wing.vCenterW.y, wing.vCenterW.z);
	mTM = mScale * mRot * mTrans;
	g_pDevice->SetTransform(D3DTS_WORLD, &mTM);

	//렌더링. : DXMesh 는 VB, FVF 등의 기하 설정이 자동으로 처리됨. ★
	g_pWingMeshSphere->DrawSubset(0);


	//렌더링 옵션 복구.
	g_pDevice->SetRenderState(D3DRS_FILLMODE, bWire);
	g_pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

#undef wing

}

/*
	4차원 행렬 中
	
		   { Z축 기준 roll 회전 }
	[X']     [  COSroll  SINroll   0   0  ]
	[Y']   = [ -SINroll  COSroll   0   0  ]
	[Z']     [     0        0      1   0  ]
	[1 ]     [     0        0      0   1  ]

	       { Y축 기준 yaw 회전 }
	[X']     [  COSyaw  0   -SINyaw   0  ]
	[Y']   = [    0     1      0      0  ]
	[Z']     [  SINyaw  0    COSyaw   0  ]
	[1 ]     [    0     0      0      1  ]

		   { X축 기준 pitch 회전 }
	[X']     [    1      0         0      0  ]
	[Y']   = [    0   COSpitch  SINpitch  0  ]
	[Z']     [    0  -SINpitch  COSpitch  0  ]
	[1 ]     [    0      0          0     1  ]

		   { 여러 행렬을 합쳐 넣을 때 }
	[X']     [  회전영향    회전영향    회전영향  0  ]
	[Y']   = [  회전영향    회전영향    회전영향  0  ]
	[Z']     [  회전영향    회전영향    회전영향  0  ]
	[1 ]     [  이동영향x   이동영향y   이동영향z 1  ]

*/

void WindMillBottomDraw2(float dTime)
{
	g_pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, g_bAlphaT);				// 알파 테스트 ON!
	g_pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);			// 크거나 같으면 통과.★
	g_pDevice->SetRenderState(D3DRS_ALPHAREF, (DWORD)(0.0 * 255));

	g_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, g_bAlphaB);			// 알파 블렌딩 ON! 
	g_pDevice->SetRenderState(D3DRS_SRCBLEND, D3DRS_BLENDFACTOR);
	g_pDevice->SetRenderState(D3DRS_BLENDFACTOR, D3DXCOLOR(0.25, 0.25, 0.25, 0.25));
	g_pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	g_pDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_SELECTARG1);
	g_pDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	g_pDevice->SetTexture(0, g_pWindmill->Bottom.pTex);

	g_pDevice->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_MODULATE);
	g_pDevice->SetTextureStageState(1, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	g_pDevice->SetTextureStageState(1, D3DTSS_COLORARG2, D3DTA_CURRENT);
	g_pDevice->SetTexture(1, g_pMap->pTex[0]);

	g_pDevice->SetTextureStageState(2, D3DTSS_COLOROP, D3DTOP_DISABLE);

	g_pDevice->SetFVF(VERTEX::FVF);
	g_pDevice->SetStreamSource(0, g_pVBTriWindmill_Bottom2, 0, sizeof VERTEX);
	g_pDevice->SetTransform(D3DTS_WORLD, &g_pTripleWindmill2->Bottom.mTM);
	g_pDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 2);

	/* 기본값으로 전환 */
	g_pDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
	g_pDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	g_pDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);

	g_pDevice->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_DISABLE);

	g_pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	g_pDevice->SetTexture(0, NULL);

}

////////////////////////////////////////////////////////////////////
void TripleWindmillDraw2(float dTime)
{
	g_pDevice->SetRenderState(D3DRS_NORMALIZENORMALS, TRUE);

	float alpha = 0.49f;

	g_pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, g_bAlphaT);			
	g_pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);		//크거나 같으면 통과.★
	g_pDevice->SetRenderState(D3DRS_ALPHAREF, (DWORD)(alpha * 255));	

	g_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, g_bAlphaB);
	g_pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	///////////////////////// 알파 존 ////////////////////////////////

	g_pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);

	if (g_pTripleWindmill2->bShowInnerLight)
	{
		g_pDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_SELECTARG1);
		g_pDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
		g_pDevice->SetTexture(0, g_pWindmill->Wing->pTex[0]);

		g_pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);
		g_pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	}
	else
	{
		g_pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);
		g_pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);		//알파 블랜딩 
		g_pDevice->SetTexture(0, g_pWindmill->Wing->pTex[0]);
	}

	// 안쪽 몸체 그리기.
	g_pDevice->SetMaterial(&g_TriWindMTL2);
	g_pDevice->SetFVF(VERTEX::FVF);
	g_pDevice->SetStreamSource(0, g_pVBTriWindmill_Body_2, 0, sizeof VERTEX);	//★
	g_pDevice->SetTransform(D3DTS_WORLD, &g_pTripleWindmill2->mTM);
	g_pDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 4);
	DrawVisibleNormal(g_MeshTri2Windmill_Body, _countof(g_MeshTri2Windmill_Body));

	g_pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);					// 바깥면

	if (g_pTripleWindmill2->bShowInnerLight)
	{
		g_pDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
		g_pDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
		g_pDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
		g_pDevice->SetTexture(0, g_pWindmill->Wing->pTex[0]);

		g_pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);
		g_pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);		//알파 블랜딩 
	}

	if (g_SeasonState == Ss_WINTER)
	{
		// <Stage 0> 텍스쳐
		g_pDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_SELECTARG1);
		g_pDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
		g_pDevice->SetTexture(0, g_pWindmill->Wing->pTex[0]);

		g_pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);
		g_pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);		//★

		// <Stage 1> 텍스쳐 + 마스크
		g_pDevice->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_ADDSIGNED);
		g_pDevice->SetTextureStageState(1, D3DTSS_COLORARG1, D3DTA_CURRENT);
		g_pDevice->SetTextureStageState(1, D3DTSS_COLORARG2, D3DTA_TEXTURE);

		g_pDevice->SetTexture(1, g_pWindmill->Wing->pTex[1]);

		// <Stage 2> 텍스쳐 * 조명
		g_pDevice->SetTextureStageState(2, D3DTSS_COLOROP, D3DTOP_MODULATE);
		g_pDevice->SetTextureStageState(2, D3DTSS_COLORARG1, D3DTA_CURRENT);
		g_pDevice->SetTextureStageState(2, D3DTSS_COLORARG2, D3DTA_DIFFUSE);

	}
	else if (g_SeasonState != Ss_WINTER)
	{
		g_pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);
		g_pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);		//알파 블랜딩 
		g_pDevice->SetTexture(0, g_pWindmill->Wing->pTex[0]);
	}

	g_pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	// 바깥 몸체 그리기.
	g_pDevice->SetMaterial(&g_TriWindMTL2);
	g_pDevice->SetFVF(VERTEX::FVF);
	g_pDevice->SetStreamSource(0, g_pVBTriWindmill_Body_2, 0, sizeof VERTEX);	//★
	g_pDevice->SetTransform(D3DTS_WORLD, &g_pTripleWindmill2->mTM);
	g_pDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 4);
	DrawVisibleNormal(g_MeshTri2Windmill_Body, _countof(g_MeshTri2Windmill_Body));

	g_pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);


	// 날개 그리기.
	// 풍차 날개를 디바이스에 등록한다. 
	for (int i = 0; i < 3; i++)
	{
		g_pDevice->SetMaterial(&g_TriWindWingMTL2);
		g_pDevice->SetFVF(VERTEX::FVF);
		g_pDevice->SetStreamSource(0, g_pVBTriWindmill_Wing_2[i], 0, sizeof VERTEX);	//★
		g_pDevice->SetTransform(D3DTS_WORLD, &g_pTripleWindmill2->Wing[i].mTM);			//날개의 TM(회전..) 설정.★
		g_pDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 8);								//날개 그리기.	

		DrawVisibleNormal(g_MeshTri2Windmill_Wing, _countof(g_MeshTri2Windmill_Wing));
	}

	g_pDevice->SetRenderState(D3DRS_NORMALIZENORMALS, FALSE);

	//----------------------------------------------------------------
	//						 기본값으로 전환
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
void TripleWindmillRelease2()
{
	SAFE_RELEASE(g_pVBTriWindmill_Body_2);		//풍차용 정점 데이터 릴리즈...★
	for (int i = 0; i < 3; i++)
	SAFE_RELEASE(g_pVBTriWindmill_Wing_2[i]);	//풍차용 정점 데이터 릴리즈...★
	SAFE_RELEASE(g_pVBTriWindmill_Bottom2);

	SAFE_DELETE(g_pTripleWindmill2);				//풍차 객체 제거...
	SAFE_DELETE(g_pWindMillWing);
}
















/****************** end of file "TripleWindmill.h" ************************/
