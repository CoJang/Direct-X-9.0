#pragma once

struct VERTEX{
	D3DXVECTOR3 vPos;
	D3DXVECTOR3 vNormal;
	D3DXVECTOR2 vUV;
	D3DXVECTOR2 vUV2;
	static const DWORD FVF = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX2;
};

struct INDEX
{
    WORD A, B, C; // [ 삼각형을 그리는데 필요한 꼭짓점 3개 ]
};