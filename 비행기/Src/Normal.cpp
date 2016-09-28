#include "d3dx9.h" 
#include "assert.h"

#include"Device.h"
#include"Render.h"

#include"Normal.h"
#include"Vertex.h"

#define NORMAL_COLOR 0xffff0000
#define NORMAL_LENGTH 1.f

struct NORMAL_VISIBLE{
	D3DXVECTOR3 vBegin;
	DWORD color0;

	D3DXVECTOR3 vEnd;
	DWORD color1;

	static const DWORD FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE;
}static normalTable[1024];

void InitVisibleNormal(){
	for (size_t i = 0; i < _countof(normalTable); ++i){
		normalTable[i].color0 = normalTable[i].color1 = NORMAL_COLOR;
	}
}
void DrawVisibleNormal(VERTEX* verts, size_t count){
	if (!g_bShowNormal)return;

	g_pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	g_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
	DWORD oldLightState;
	g_pDevice->GetRenderState(D3DRS_LIGHTING, &oldLightState);

	D3DXMATRIXA16 mTemp;
	g_pDevice->GetTransform(D3DTS_WORLD, &mTemp);

	mTemp._11 = 1 / D3DXVec3Length(&D3DXVECTOR3(mTemp._11, mTemp._12, mTemp._13));
	mTemp._22 = 1 / D3DXVec3Length(&D3DXVECTOR3(mTemp._21, mTemp._22, mTemp._23));
	mTemp._33 = 1 / D3DXVec3Length(&D3DXVECTOR3(mTemp._31, mTemp._32, mTemp._33));

	for (size_t i = 0; i < count; ++i){
		normalTable[i].vBegin = verts[i].vPos;
		normalTable[i].vEnd =
			verts[i].vPos +
			D3DXVECTOR3(
				verts[i].vNormal.x * mTemp._11,
				verts[i].vNormal.y * mTemp._22,
				verts[i].vNormal.z * mTemp._33
			) *
			NORMAL_LENGTH;
	}

	g_pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	g_pDevice->SetFVF(NORMAL_VISIBLE::FVF);
	g_pDevice->DrawPrimitiveUP(D3DPT_LINELIST, count, normalTable, sizeof NORMAL_VISIBLE / 2);

	g_pDevice->SetRenderState(D3DRS_LIGHTING, oldLightState);
	g_pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	g_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
}