//
// Tree.h
//
//
// 2007.01.25. Kihong Kim / mad_dog@hanmail.net
//

#pragma once



//
//  ���� ����ü.
//
struct TREE
{  	
	enum : unsigned char
	{
		ts_NONE,		// ��һ���
		ts_HIT,			// �¾��� ��
		ts_FELLDOWN,	// �������� ��
		ts_STICK		// ����ο� �پ��� ��!
	}TreeState;			// �� ���µ��� �����ϴ� ��

	D3DXVECTOR3 vPos;					// ���� ��ǥ.
	D3DMATERIAL9 TreeMTL;				// ���� ����

	D3DXVECTOR3 vUp, vDir, Rot_Axis;	// ���� ������ ��溤�� vUp, ���⺤�� vDir, ��溤�� ���� �߻�ü �߻���� Rot_Axis
	D3DXVECTOR3 vCenterL;				// �浹�˻�� �߽� ��ǥ.(Local)��
	D3DXVECTOR3 vCenterW;				// �浹�˻�� �߽� ��ǥ.(World)��
	float		fRadius;				// �浹�� �ݰ�.��
	float		f_Tangle;				// ������ ȸ����
	float		f_Talpha;				// ������ ���İ�
	float		f_TDelay;				// ������ Ÿ�̸�

	D3DXMATRIX mTM, temp_mTM;						// ���� ���� ��ȯ ���.
	D3DXMATRIX mScale, mRot, mTrans;

};




// ���� ���� ���� �Լ�.
//
INT TreeInit();
void TreeUpdate(float dTime);
void TreeDraw(float dTime);
void TreeRelease();

void TreeBSphereDraw(float dTime);	//��
#define TREE_MAX_  3000				//��
extern TREE* g_pTree[TREE_MAX_];	//�� 

/****************** end of file "Tree.h" ************************/