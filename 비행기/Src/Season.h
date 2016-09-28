#pragma once

enum Season : unsigned char	// 계절의 3가지 상태
{
	Ss_SUMMER,
	Ss_AUTUMN,
	Ss_WINTER
};

extern Season g_SeasonState;

struct SNOW
{
	CHAR* g_TextureName[3];
	LPDIRECT3DTEXTURE9 pTex[3];
	char* g_cSeasonState;
};

extern SNOW* g_pSnow;

extern void UpdateSeason();
extern void ReleaseSeason();

extern void SetSummer(LPDIRECT3DTEXTURE9 pTex);

// Num에는 0 ~ 1번 까지 있다.
// 0 = Tile, 1 = Tree
extern void SetAutumn(LPDIRECT3DTEXTURE9 pTex, int num);

// Num에는 0 ~ 2번 까지 있다.
// 0 = Tile, 1 = Tree, 2 = WindMill
extern void SetWinter(LPDIRECT3DTEXTURE9 pTex, int num);

//텍스처 스테이지 설정 : 기본값으로 전환
extern void SetDefault();