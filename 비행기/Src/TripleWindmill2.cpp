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

// ǳ�� ��ü : �Ƕ�̵� ����.
VERTEX g_MeshTri2Windmill_Body[] = {
	// 4������ ��ü..
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

	//'�ظ�' �� �ʿ� ����..
};

//ǳ�� ����.
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

	//�ٴ�.  ( Face#1)
	{ D3DXVECTOR3(1.0, -1.0, 1.0), D3DXVECTOR3(0.0, 0.0, 0.0), D3DXVECTOR2(0.0, 0.0) },
	{ D3DXVECTOR3(-1.0, -1.0, 1.0), D3DXVECTOR3(0.0, 0.0, 0.0), D3DXVECTOR2(1.0, 0.0) },
	{ D3DXVECTOR3(-1.0, -1.0, -1.0), D3DXVECTOR3(0.0, 0.0, 0.0), D3DXVECTOR2(1.0, 1.0) },
	//		 ( Face#2)
	{ D3DXVECTOR3(1.0, -1.0, 1.0), D3DXVECTOR3(0.0, 0.0, 0.0), D3DXVECTOR2(0.0, 0.0) },
	{ D3DXVECTOR3(-1.0, -1.0, -1.0), D3DXVECTOR3(0.0, 0.0, 0.0), D3DXVECTOR2(1.0, 1.0) },
	{ D3DXVECTOR3(1.0, -1.0, -1.0), D3DXVECTOR3(0.0, 0.0, 0.0), D3DXVECTOR2(0.0, 1.0) },

};


LPDIRECT3DVERTEXBUFFER9	g_pVBTriWindmill_Body_2 = NULL;			//���� ���ۿ� ������.(��ü)
LPDIRECT3DVERTEXBUFFER9	g_pVBTriWindmill_Wing_2[3] = { NULL, NULL, NULL };			//���� ���ۿ� ������.(����1)
LPDIRECT3DVERTEXBUFFER9	g_pVBTriWindmill_Bottom2 = NULL;	//���� ���ۿ� ������.(�ٴ�)



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

	g_pWindMillWing->vCenterL = D3DXVECTOR3(0, 0, 0);			// �ʱ�ȭ
	g_pWindMillWing->vCenterW = D3DXVECTOR3(0, 0, 0);
	g_pWindMillWing->vNormal = D3DXVECTOR3(0, 0, 0);
	g_pWindMillWing->fRadius = 2.0f;							// �浹�� �ݰ�.��

	D3DXMatrixIdentity(&wing.mTM);			//��� ������ �ʱ�ȭ.
	D3DXMatrixIdentity(&wing.mRot);
	D3DXMatrixIdentity(&wing.mScale);
	D3DXMatrixIdentity(&wing.mTrans);
	
#undef wing

	// [ ǳ�� �ٵ� ��ĺ��� �ʱ�ȭ �� Y�� 2�� ������ ]
	g_pTripleWindmill2->vPos = vPos;								//ǳ�� ���� ��ġ
	g_pTripleWindmill2->vRot = D3DXVECTOR3(0, 0, 0);				//ǳ�� ȸ�� ����.
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

	// [ ����1 ��ĺ��� �ʱ�ȭ �� 1.8�� ������ ]
	g_pTripleWindmill2->Wing[0].vPos = D3DXVECTOR3(0, 3, -1.0f);
	D3DXMatrixScaling(&g_pTripleWindmill2->Wing[0].mScale, 1.5f, 1.5f, 1.5f);

	// [ ����2 ��ĺ��� �ʱ�ȭ ]
	g_pTripleWindmill2->Wing[1].vPos = D3DXVECTOR3(0, 0, -0.5f);

	// [ ����3 ��ĺ��� �ʱ�ȭ �� 0.8�� ������ ]
	g_pTripleWindmill2->Wing[2].vPos = D3DXVECTOR3(0, 0, -0.5f);
	D3DXMatrixScaling(&g_pTripleWindmill2->Wing[2].mScale, 0.8f, 0.8f, 0.8f);

	ZeroMemory(&g_TriWindMTL2, sizeof(g_TriWindMTL2));
	g_TriWindMTL2.Diffuse = { 1, 1, 1, 1 };
	g_TriWindMTL2.Ambient = { 0.8f, 0.8f, 0.8f, 1 };


	ZeroMemory(&g_TriWindWingMTL2, sizeof(g_TriWindWingMTL2));
	g_TriWindWingMTL2.Diffuse = { 1, 1, 1, 1 };
	g_TriWindWingMTL2.Ambient = { 0.8f, 0.8f, 0.8f, 1 };
	
	// ǳ�� ��ü��. ���� ���� ����.
	if (FAILED(g_pDevice->CreateVertexBuffer(
		sizeof(g_MeshTri2Windmill_Body),	//��	
		0,
		VERTEX::FVF,					//��
		D3DPOOL_MANAGED,
		&g_pVBTriWindmill_Body_2,			//��
		NULL)))
	{
		return E_FAIL;
	}

	//���� ä���.
	VOID*	pBuff;
	if (FAILED(g_pVBTriWindmill_Body_2->Lock(0, sizeof(g_MeshTri2Windmill_Body), (void**)&pBuff, 0)))
	{
		return E_FAIL;
	}

	memcpy(pBuff, g_MeshTri2Windmill_Body, sizeof(g_MeshTri2Windmill_Body));
	g_pVBTriWindmill_Body_2->Unlock();


	//
	// ǳ�� ������ ���� ���� ����.
	//
	for (int i = 0; i < 3; i++)
	{

		if (FAILED(g_pDevice->CreateVertexBuffer(
			sizeof(g_MeshTri2Windmill_Wing),	//��	
			0,
			VERTEX::FVF,					//��
			D3DPOOL_MANAGED,
			&g_pVBTriWindmill_Wing_2[i],			//��
			NULL)))
		{
			return E_FAIL;
		}

		//���� ä���.
		if (FAILED(g_pVBTriWindmill_Wing_2[i]->Lock(0, sizeof(g_MeshTri2Windmill_Wing), (void**)&pBuff, 0)))
		{
			return E_FAIL;
		}

		memcpy(pBuff, g_MeshTri2Windmill_Wing, sizeof(g_MeshTri2Windmill_Wing));
		g_pVBTriWindmill_Wing_2[i]->Unlock();

	}

	//
	// ǳ�� �ٴڿ� ���� ���� ����.
	//
	if (FAILED(g_pDevice->CreateVertexBuffer(
		sizeof(g_MeshTriWindMillBottom2),	//��	
		0,
		VERTEX::FVF,					//��
		D3DPOOL_MANAGED,
		&g_pVBTriWindmill_Bottom2,			//��
		NULL)))
	{
		return E_FAIL;
	}

	//���� ä���.
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

	// ������� Rotate mat * Trans mat
	static D3DXMATRIX HeroMatRT;

	// �Ѿ��� ����� ��ġ
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
	// ǳ�� ��ü ��� ���.
	//--------------------------------------------------------------------------  

	// ǳ�� ��ü �̵�  
	static float mov = 10.0f;

	if (IsKeyDown('I'))		g_pTripleWindmill2->vPos.z += mov * dTime;
	if (IsKeyDown('K'))		g_pTripleWindmill2->vPos.z -= mov * dTime;
	if (IsKeyDown('L'))		g_pTripleWindmill2->vPos.x += mov * dTime;
	if (IsKeyDown('J'))		g_pTripleWindmill2->vPos.x -= mov * dTime;

	D3DXMatrixTranslation(&g_pTripleWindmill2->mTrans,
		g_pTripleWindmill2->vPos.x,
		g_pTripleWindmill2->vPos.y,
		g_pTripleWindmill2->vPos.z);		// ǳ�� ��ü �̵���� �����.	ó���� �ѹ��� ���. ��


	// ǳ�� ȸ��
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


	// 'ǳ�� ���� ��ȯ �� - TM -  ����ϱ� :  
	// 
	// BodyTM = S * R * T
	//
	//g_pWindmill->mTM = g_pWindmill->mTrans;		
	D3DXMatrixMultiply(&g_pTripleWindmill2->mTM, &g_pTripleWindmill2->mScale, &g_pTripleWindmill2->mRot);
	D3DXMatrixMultiply(&g_pTripleWindmill2->mTM, &g_pTripleWindmill2->mTM, &g_pTripleWindmill2->mTrans);


	//-------------------------------------------------------------------------- 
	// ���� ��� ���.
	//--------------------------------------------------------------------------

	//����1 �̵� ��� �����. 
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
		angle[0] += D3DX_PI * dTime / 4 * speed;				//180(��)/sec  ��, 1ȸ���� 4�� �ҿ�.
		D3DXMatrixRotationZ(&g_pTripleWindmill2->Wing[0].mRot, angle[0]);
		angle[1] += D3DX_PI * -dTime * speed;					//180(��)/sec  ��, 1ȸ���� 2�� �ҿ�.
		D3DXMatrixRotationZ(&g_pTripleWindmill2->Wing[1].mRot, angle[1]);
		angle[2] += D3DX_PI * dTime * 2 * speed;				//180(��)/sec  ��, 1ȸ���� 1�� �ҿ�.
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

	// ǳ�� ģ���� SRT��� TM��ķ� ��ġ��
	for (int i = 0; i < 3; i++)
	{
		g_pTripleWindmill2->Wing[i].mTM = g_pTripleWindmill2->Wing[i].mScale * g_pTripleWindmill2->Wing[i].mRot * g_pTripleWindmill2->Wing[i].mTrans;
	}


	{ // ǳ�� ģ���鿡�� ���� �޾��ֱ�
		// ǳ�� 1
		switch (heroFireState)
		{
		case hf_RELOAD:
			// ������� ����� ��ġ�� ����Ѵ�
			// ������ ���� ���ʿ�
			HeroMatRT = g_pHero->mRot * g_pHero->mTrans;

			// ����ο� �پ �����̵���
			g_pTripleWindmill2->Wing[0].mTM *= HeroMatRT;

			// �Ѿ��� ��� ��ġ�� �ʱ�ȭ
			BulletPos = 0;
			break;

		case hf_FIRE:{
			// �Ѿ��� ��� ��ġ�� ������Ŵ
			BulletPos += 30.0f * dTime;
			if (BulletPos > 20.f)
				heroFireState = hf_NONE;

			// ��������� ��������� �� ����ΰ� �ٶ󺸴� ������
			// (0, 0, -1) �̹Ƿ� �� ���⿡ BulletPos�� ���� ��
			D3DXVECTOR3 bulletDir = { 0, 0, -BulletPos };

			D3DXMATRIX tmpMat;
			D3DXMatrixIdentity(&tmpMat);

			// ������� ����� ��ġ�� ���� ��Ŀ��� ���� ��ĸ� �����Ѵ�.
			tmpMat[0] = HeroMatRT[0];
			tmpMat[2] = HeroMatRT[2];
			tmpMat[8] = HeroMatRT[8];
			tmpMat[10] = HeroMatRT[10];

			// �ռ� ������ ȸ�� ����� �̿��Ͽ� bulletDir���͸� ��ȯ�Ѵ�.
			// bulletDir = ����� �������
			D3DXVec3TransformCoord(&bulletDir, &bulletDir, &tmpMat);
			D3DXMatrixTranslation(&tmpMat, bulletDir.x, bulletDir.y, bulletDir.z);

			g_pTripleWindmill2->Wing[0].mTM *= HeroMatRT * tmpMat;

		}
			break;

		default:
			D3DXMatrixInverse(&g_pTripleWindmill2->Sinverse, NULL, &g_pTripleWindmill2->mScale);
			g_pTripleWindmill2->Wing[0].mTM *= g_pTripleWindmill2->Sinverse;	// [ �θ��� �����Ͽ� ������ ���� �ʱ� ���� ����� �� ]
			g_pTripleWindmill2->Wing[0].mTM *= g_pTripleWindmill2->mTM;			// [ (���� 1 -> �ٵ�) ���� ]
			break;
		}

		// ǳ�� 2
		D3DXMatrixInverse(&g_pTripleWindmill2->Wing[0].Rinverse, NULL, &g_pTripleWindmill2->Wing[0].mRot);
		D3DXMatrixInverse(&g_pTripleWindmill2->Wing[0].Sinverse, NULL, &g_pTripleWindmill2->Wing[0].mScale);
		g_pTripleWindmill2->Wing[1].mTM *= g_pTripleWindmill2->Wing[0].Sinverse;
		g_pTripleWindmill2->Wing[1].mTM *= g_pTripleWindmill2->Wing[0].Rinverse;
		g_pTripleWindmill2->Wing[1].mTM *= g_pTripleWindmill2->Wing[0].mTM;

		// ǳ�� 3
		D3DXMatrixInverse(&g_pTripleWindmill2->Wing[1].Rinverse, NULL, &g_pTripleWindmill2->Wing[1].mRot);
		D3DXMatrixInverse(&g_pTripleWindmill2->Wing[1].Sinverse, NULL, &g_pTripleWindmill2->Wing[1].mScale);
		g_pTripleWindmill2->Wing[2].mTM *= g_pTripleWindmill2->Wing[1].Rinverse;
		g_pTripleWindmill2->Wing[2].mTM *= g_pTripleWindmill2->Wing[1].mTM;

		/* ������ �浹��ü ���� */
#define  wing  (* g_pWindMillWing)

		D3DXMatrixTranslation(&wing.mTrans, wing.vPos.x, wing.vPos.y, wing.vPos.z);
		wing.mTM = wing.mScale * wing.mRot * wing.mTrans;
		g_pWindMillWing->vCenterW = g_pTripleWindmill2->Wing[0].vPos;
		D3DXVec3TransformCoord(&wing.vCenterW, &wing.vCenterL, &g_pTripleWindmill2->Wing[0].mTM);

#undef wing

	}

	//-------------------------------------------------------------------------- 
	// ǳ�� �ٴ� ��� ���.
	//--------------------------------------------------------------------------  
	D3DXMatrixScaling(&g_pTripleWindmill2->Bottom.mScale, 1.70, 1, 1.70);
	g_pTripleWindmill2->Bottom.mRot = g_pTripleWindmill2->mRot;
	D3DXMatrixTranslation(&g_pTripleWindmill2->Bottom.mTrans, g_pTripleWindmill2->vPos.x, g_pTripleWindmill2->vPos.y + 1, g_pTripleWindmill2->vPos.z);

	g_pTripleWindmill2->Bottom.mTM = g_pTripleWindmill2->Bottom.mScale * g_pTripleWindmill2->Bottom.mRot * g_pTripleWindmill2->Bottom.mTrans;
}

void WingBSphereDraw(float dTime)
{

	//�浹���� ���������� �ٸ��Ƿ�, ũ�� ����� �ʿ�.
	//������ �����ϸ� �Ͽ� ���.(���� ������ ����ũ��, ����..)
	D3DXMATRIX mTM, mTrans, mScale, mRot;
#define  wing  (* g_pWindMillWing)
	//������ ���� ���.
	DWORD bWire;
	g_pDevice->GetRenderState(D3DRS_FILLMODE, &bWire);
	g_pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	g_pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);


	//���庯ȯ ����..
	D3DXMatrixScaling(&mScale, wing.fRadius, wing.fRadius, wing.fRadius);
	D3DXMatrixRotationX(&mRot, D3DX_PI*0.5f);
	D3DXMatrixTranslation(&mTrans, wing.vCenterW.x, wing.vCenterW.y, wing.vCenterW.z);
	mTM = mScale * mRot * mTrans;
	g_pDevice->SetTransform(D3DTS_WORLD, &mTM);

	//������. : DXMesh �� VB, FVF ���� ���� ������ �ڵ����� ó����. ��
	g_pWingMeshSphere->DrawSubset(0);


	//������ �ɼ� ����.
	g_pDevice->SetRenderState(D3DRS_FILLMODE, bWire);
	g_pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

#undef wing

}

/*
	4���� ��� ��
	
		   { Z�� ���� roll ȸ�� }
	[X']     [  COSroll  SINroll   0   0  ]
	[Y']   = [ -SINroll  COSroll   0   0  ]
	[Z']     [     0        0      1   0  ]
	[1 ]     [     0        0      0   1  ]

	       { Y�� ���� yaw ȸ�� }
	[X']     [  COSyaw  0   -SINyaw   0  ]
	[Y']   = [    0     1      0      0  ]
	[Z']     [  SINyaw  0    COSyaw   0  ]
	[1 ]     [    0     0      0      1  ]

		   { X�� ���� pitch ȸ�� }
	[X']     [    1      0         0      0  ]
	[Y']   = [    0   COSpitch  SINpitch  0  ]
	[Z']     [    0  -SINpitch  COSpitch  0  ]
	[1 ]     [    0      0          0     1  ]

		   { ���� ����� ���� ���� �� }
	[X']     [  ȸ������    ȸ������    ȸ������  0  ]
	[Y']   = [  ȸ������    ȸ������    ȸ������  0  ]
	[Z']     [  ȸ������    ȸ������    ȸ������  0  ]
	[1 ]     [  �̵�����x   �̵�����y   �̵�����z 1  ]

*/

void WindMillBottomDraw2(float dTime)
{
	g_pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, g_bAlphaT);				// ���� �׽�Ʈ ON!
	g_pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);			// ũ�ų� ������ ���.��
	g_pDevice->SetRenderState(D3DRS_ALPHAREF, (DWORD)(0.0 * 255));

	g_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, g_bAlphaB);			// ���� ���� ON! 
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

	/* �⺻������ ��ȯ */
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
	g_pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);		//ũ�ų� ������ ���.��
	g_pDevice->SetRenderState(D3DRS_ALPHAREF, (DWORD)(alpha * 255));	

	g_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, g_bAlphaB);
	g_pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	///////////////////////// ���� �� ////////////////////////////////

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
		g_pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);		//���� ���� 
		g_pDevice->SetTexture(0, g_pWindmill->Wing->pTex[0]);
	}

	// ���� ��ü �׸���.
	g_pDevice->SetMaterial(&g_TriWindMTL2);
	g_pDevice->SetFVF(VERTEX::FVF);
	g_pDevice->SetStreamSource(0, g_pVBTriWindmill_Body_2, 0, sizeof VERTEX);	//��
	g_pDevice->SetTransform(D3DTS_WORLD, &g_pTripleWindmill2->mTM);
	g_pDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 4);
	DrawVisibleNormal(g_MeshTri2Windmill_Body, _countof(g_MeshTri2Windmill_Body));

	g_pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);					// �ٱ���

	if (g_pTripleWindmill2->bShowInnerLight)
	{
		g_pDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
		g_pDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
		g_pDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
		g_pDevice->SetTexture(0, g_pWindmill->Wing->pTex[0]);

		g_pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);
		g_pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);		//���� ���� 
	}

	if (g_SeasonState == Ss_WINTER)
	{
		// <Stage 0> �ؽ���
		g_pDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_SELECTARG1);
		g_pDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
		g_pDevice->SetTexture(0, g_pWindmill->Wing->pTex[0]);

		g_pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);
		g_pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);		//��

		// <Stage 1> �ؽ��� + ����ũ
		g_pDevice->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_ADDSIGNED);
		g_pDevice->SetTextureStageState(1, D3DTSS_COLORARG1, D3DTA_CURRENT);
		g_pDevice->SetTextureStageState(1, D3DTSS_COLORARG2, D3DTA_TEXTURE);

		g_pDevice->SetTexture(1, g_pWindmill->Wing->pTex[1]);

		// <Stage 2> �ؽ��� * ����
		g_pDevice->SetTextureStageState(2, D3DTSS_COLOROP, D3DTOP_MODULATE);
		g_pDevice->SetTextureStageState(2, D3DTSS_COLORARG1, D3DTA_CURRENT);
		g_pDevice->SetTextureStageState(2, D3DTSS_COLORARG2, D3DTA_DIFFUSE);

	}
	else if (g_SeasonState != Ss_WINTER)
	{
		g_pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);
		g_pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);		//���� ���� 
		g_pDevice->SetTexture(0, g_pWindmill->Wing->pTex[0]);
	}

	g_pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	// �ٱ� ��ü �׸���.
	g_pDevice->SetMaterial(&g_TriWindMTL2);
	g_pDevice->SetFVF(VERTEX::FVF);
	g_pDevice->SetStreamSource(0, g_pVBTriWindmill_Body_2, 0, sizeof VERTEX);	//��
	g_pDevice->SetTransform(D3DTS_WORLD, &g_pTripleWindmill2->mTM);
	g_pDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 4);
	DrawVisibleNormal(g_MeshTri2Windmill_Body, _countof(g_MeshTri2Windmill_Body));

	g_pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);


	// ���� �׸���.
	// ǳ�� ������ ����̽��� ����Ѵ�. 
	for (int i = 0; i < 3; i++)
	{
		g_pDevice->SetMaterial(&g_TriWindWingMTL2);
		g_pDevice->SetFVF(VERTEX::FVF);
		g_pDevice->SetStreamSource(0, g_pVBTriWindmill_Wing_2[i], 0, sizeof VERTEX);	//��
		g_pDevice->SetTransform(D3DTS_WORLD, &g_pTripleWindmill2->Wing[i].mTM);			//������ TM(ȸ��..) ����.��
		g_pDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 8);								//���� �׸���.	

		DrawVisibleNormal(g_MeshTri2Windmill_Wing, _countof(g_MeshTri2Windmill_Wing));
	}

	g_pDevice->SetRenderState(D3DRS_NORMALIZENORMALS, FALSE);

	//----------------------------------------------------------------
	//						 �⺻������ ��ȯ
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
	SAFE_RELEASE(g_pVBTriWindmill_Body_2);		//ǳ���� ���� ������ ������...��
	for (int i = 0; i < 3; i++)
	SAFE_RELEASE(g_pVBTriWindmill_Wing_2[i]);	//ǳ���� ���� ������ ������...��
	SAFE_RELEASE(g_pVBTriWindmill_Bottom2);

	SAFE_DELETE(g_pTripleWindmill2);				//ǳ�� ��ü ����...
	SAFE_DELETE(g_pWindMillWing);
}
















/****************** end of file "TripleWindmill.h" ************************/
