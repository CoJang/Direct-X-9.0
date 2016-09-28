//
// Tree.h
//
//
// 2007.01.25. Kihong Kim / mad_dog@hanmail.net
//

#pragma once



//
//  나무 구조체.
//
struct TREE
{  	
	enum : unsigned char
	{
		ts_NONE,		// 평소상태
		ts_HIT,			// 맞았을 때
		ts_FELLDOWN,	// 쓰러졌을 때
		ts_STICK		// 히어로에 붙었을 때!
	}TreeState;			// 위 상태들을 저장하는 곳

	D3DXVECTOR3 vPos;					// 월드 좌표.
	D3DMATERIAL9 TreeMTL;				// 나무 재질

	D3DXVECTOR3 vUp, vDir, Rot_Axis;	// 나무 각자의 상방벡터 vUp, 방향벡터 vDir, 상방벡터 외적 발사체 발사방향 Rot_Axis
	D3DXVECTOR3 vCenterL;				// 충돌검사용 중심 좌표.(Local)★
	D3DXVECTOR3 vCenterW;				// 충돌검사용 중심 좌표.(World)★
	float		fRadius;				// 충돌구 반경.★
	float		f_Tangle;				// 나무의 회전각
	float		f_Talpha;				// 나무의 알파값
	float		f_TDelay;				// 나무의 타이머

	D3DXMATRIX mTM, temp_mTM;						// 최종 월드 변환 행렬.
	D3DXMATRIX mScale, mRot, mTrans;

};




// 나무 관련 전역 함수.
//
INT TreeInit();
void TreeUpdate(float dTime);
void TreeDraw(float dTime);
void TreeRelease();

void TreeBSphereDraw(float dTime);	//★
#define TREE_MAX_  3000				//★
extern TREE* g_pTree[TREE_MAX_];	//★ 

/****************** end of file "Tree.h" ************************/