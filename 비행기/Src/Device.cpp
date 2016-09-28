//
// Device.cpp : 기본 D3D 객체 및 디바이스 설정/제거 소스.
//
// 2003.11.4. Kihong Kim / mad_dog@hanmail.net
// 2004.05.07. Update
// 2005.09.23. Update (.Net)
//
//
#include "windows.h"
#include "mmsystem.h"

#include "Device.h"
#include "Hero.h"		

//////////////////////////////////////////////////////////////////////////////
//
// 전역 변수.
//

// D3D 관련 개체 인터페이스 포인터.
LPDIRECT3D9				g_pD3D = NULL;
LPDIRECT3DDEVICE9		g_pDevice = NULL;


// 화면 모드 설정 전역 변수.  
D3DDISPLAYMODE g_Mode = { 1200, 700, 0, D3DFMT_A8R8G8B8 }; 

// 폰트. 2004.10.21. 
LPD3DXFONT	g_pFont;

// AA, AF
DWORD		g_dwAA = 0;		//<-- DeviceSetup 에서 설정함..★
DWORD		g_dwAF = 0;
BOOL		g_bSWVP = FALSE;

//그리드 & 시각축
B3Grid*		g_pGrid = NULL;
BOOL		g_bShowGrid = YES_;
B3Axis*		g_pAxis = NULL;
BOOL		g_bShowAxis = YES_;
SIZE		g_Screen = { 0, 0 };
void GridAxisCreate();
void GridAxisRelease();
void GridAxisUpdate();


//와이어프레임 판정.
BOOL g_bShowFrame = FALSE;

//배경색.
D3DXCOLOR g_ColBlue(0, 0.12f, 0.35f, 1);			
D3DXCOLOR g_ColGray(0.20f, 0.20f, 0.20f, 1);		
D3DXCOLOR g_ColDGray(0.12f, 0.12f, 0.12f, 1);		
D3DXCOLOR g_BkColor(0,0,0,1);						



//
//  카메라 : View -Project 행렬 계산 및 설정.
//
D3DXVECTOR3		g_vEye(0.0f, 10.0f, -30.0f);			//카메라 위치. 
D3DXVECTOR3		g_vLookAt(0.0f, 0.0f, 0.0f);		//바라보는 곳.위치.
D3DXVECTOR3		g_vUp(0.0f, 1.0f, 0.0f);			//카메라 상방 벡터.

float g_fFOV   = D3DXToRadian(45);						//기본 FOV 앵글.
float g_fAspect =  g_Mode.Width/(float)g_Mode.Height;	//가로:세로 비율
float g_fZnear = 1.0f;									//시야 최소 거리 (1.0m) 
float g_fZfar = 300.0f;									//시야 최대 거리 (300m) 




/////////////////////////////////////////////////////////////////////////////
//
// DX 및 관련 객체 초기화.
//
HRESULT DXSetup(HWND hwnd)
{

 	// D3D 객체를 생성
	//
	if(NULL == (g_pD3D = Direct3DCreate9(D3D_SDK_VERSION)))
		return E_FAIL;

	//---------------------------------------------------
	// AA 옵션 체크 (HW 지원 필수!) ★
	//---------------------------------------------------
	D3DFORMAT  BackFormat = D3DFMT_A8R8G8B8;
	D3DFORMAT  StencilFormat = D3DFMT_D24X8;
	D3DMULTISAMPLE_TYPE MultiType = D3DMULTISAMPLE_8_SAMPLES;	//AA=x8 ★
	//D3DMULTISAMPLE_TYPE MultiType = D3DMULTISAMPLE_4_SAMPLES;	//AA=x4 ★
	//D3DMULTISAMPLE_TYPE MultiType = D3DMULTISAMPLE_2_SAMPLES;	//AA=x2 ★
	//D3DMULTISAMPLE_TYPE MultiType = D3DMULTISAMPLE_NONE;		//AA=0 (없음) ★
	DWORD Quality = 1;
	char msg[256];

	if (MultiType > D3DMULTISAMPLE_NONE)
	{
		sprintf(msg, "[YENA] HW AA 지원여부를 테스트합니다. \n MultiSample = x%d", MultiType);
		MessageBox(NULL, msg, "AA Check", MB_OK | MB_ICONWARNING);

		HRESULT res1 = g_pD3D->CheckDeviceMultiSampleType(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, BackFormat, TRUE, MultiType, &Quality);		//백버퍼 체크.
		HRESULT res2 = g_pD3D->CheckDeviceMultiSampleType(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, StencilFormat, TRUE, MultiType, &Quality);			//스텐실 체크.
		if (FAILED(res1) || FAILED(res2))
		{
			sprintf(msg, "[FAILED] 테스트 실패 : HW AA 지원 불가 \n MultiSample = x%d  Qualtiy = %d", MultiType, Quality - 1);
			MessageBox(NULL, msg, "AA Check", MB_OK | MB_ICONERROR);
			return E_FAIL;
		}

		sprintf(msg, "[OK] 테스트 성공 : HW AA 를 지원합니다.\n MultiSample = x%d  Qualtiy = %d", MultiType, Quality - 1);
		MessageBox(NULL, msg, "FSAA Check", MB_OK | MB_ICONINFORMATION);
	}

	//---------------------------------------------------
	// AA & AF 옵션 테스트...★
	//---------------------------------------------------
	//DWORD		g_dwAA = 8,	g_dwAF = 16;
	//DWORD		g_dwAA = 4,	g_dwAF = 8;
	//DWORD		g_dwAA = 0,	g_dwAF = 0;
	g_dwAA = MultiType;
	g_dwAF = 16;
	//g_dwAF = 8;
	//g_dwAF = 0;
 

	// 디스플레이 정보 구성 : 	 
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));

	d3dpp.Windowed = TRUE;								
	d3dpp.BackBufferWidth = g_Mode.Width;				//해상도 결정.(백버퍼 크기)
	d3dpp.BackBufferHeight = g_Mode.Height;
	d3dpp.BackBufferFormat = g_Mode.Format;				//백버퍼 색상규격 (A8R8G8B8) 창모드에서는 생략 가능 
	d3dpp.BackBufferCount = 1;							//백버퍼 개수. (현재는 1개)

	d3dpp.SwapEffect  = D3DSWAPEFFECT_DISCARD;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;		//버퍼 갱신율.
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;	

	d3dpp.EnableAutoDepthStencil = TRUE;				//z버퍼용 셋팅.
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24X8;		//Back Buffer Format.	
	 

	// D3D 에서 렌더링 '장치(Device)'를 생성. 
	//
	HRESULT res = g_pD3D->CreateDevice(
						D3DADAPTER_DEFAULT,						//0번 비디오 어뎁터.
						D3DDEVTYPE_HAL,							//하드웨어 레스터(HW Rasterization) 
						hwnd,									//생성할 윈도 핸들.
						//D3DCREATE_SOFTWARE_VERTEXPROCESSING,	//정점 처리 방법.(CPU)
						D3DCREATE_HARDWARE_VERTEXPROCESSING,	//정점 처리 방법.(GPU)
						&d3dpp,									//화면 설정 '옵션'
						&g_pDevice								//생성된 장치의 포인터를 받을 포인터변수.
						);
	if(FAILED(res))
	{
		char msg[256];
		sprintf(msg, "[ERROR] Device  생성 실패, 옵션 체크요망 \n[Call] ResetDevice():Reset(): hRes=%s,\n[Option] Res=%dx%d", 
			DXGetErrorString(res), g_Mode.Width, g_Mode.Height);
		MessageBox(g_hWnd, msg, "Error", MB_OK);

		return E_FAIL;
	}


	// 디바이스 기본 상태 옵션 결정.
	// ...
	//culling off. 삼각형 앞뒷면 모두 렌더링..
	g_pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);


	//Light OFF.
	g_pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);


	//Z-Buffer On!! (ZBuffer 사용시 기본값) 
	//g_pDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE); 



	// DX 폰트 생성 : '디바이스 리셋(Reset) 시 복구(Restore) 필요
	// 
	res = D3DXCreateFont(g_pDevice, 
		12,				//세로..
		6,				//가로.
		1,				// 두께..
		0,				//Mip Level.
		false,			//bUseItalic, 
		DEFAULT_CHARSET, 
		OUT_DEFAULT_PRECIS,		//9.0b 2003, summer.
		//OUT_TT_PRECIS,		//9.0c 호환.
		DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE, 
		(LPSTR)"굴림",
		&g_pFont
		);	 
	if(FAILED(res))
	{
		//error...
		return FALSE; 
	}	



	//그리드 생성.
	GridAxisCreate();

	return S_OK;

}




///////////////////////////////////////////////////////////////////////////// 
//
void DXRelease()
{ 	 
	//축 제거.
	GridAxisRelease();

	//폰트제거
	SAFE_RELEASE(g_pFont); 

	SAFE_RELEASE(g_pDevice);		//디바이스 제거.
	SAFE_RELEASE(g_pD3D);			//D3D 제거.
}
 




////////////////////////////////////////////////////////////////////////////// 
//
void GridAxisCreate()
{ 	 
	int w = g_Mode.Width;
	int h = g_Mode.Height;
	float s = 5.0f;				//그리드 스캐일.(1칸의 크기)

	g_pAxis = new B3Axis;
	//ASSERT(g_pAxis);
	B3Axis::_AXISINFO ai;
	ai.length = 5.0f;  
	ai.scale = s;
	g_pAxis->Init(NULL, &ai, w, h);		 


	g_Screen.cx = w;
	g_Screen.cy = h;


	g_pGrid = new B3Grid;
	B3Grid::GRIDINFO  gi;
	//ZeroMemory(&gi, sizeof(gi));
	gi.width  = 100;			//전체 폭.
	gi.height = 100;			
	gi.scale =  s;		//한칸의 크기. 
	gi.color = COLOR(0.3f, 0.3f, 0.3f, 1.0f); 
	g_pGrid->Init(g_pDevice, &gi);


}


////////////////////////////////////////////////////////////////////////////// 
//
void GridAxisRelease()
{
	SAFE_DELETE(g_pAxis);
	SAFE_DELETE(g_pGrid);

}



////////////////////////////////////////////////////////////////////////////// 
//
void GridAxisUpdate(float dTime)
{
	if(IsKeyUp(VK_F2)) g_bShowGrid ^= TRUE;		 
	if(IsKeyUp(VK_F3)) g_bShowAxis ^= TRUE;	

	g_pGrid->Update(g_pDevice);
	g_pAxis->Update( g_pDevice, D3DXVECTOR3(0, 0, 0), g_Mode.Width, g_Mode.Height ); 

}


////////////////////////////////////////////////////////////////////////////// 
//
//  시스템 개체 그리기.
//
void GridAxisDraw() 
{
	if(g_bShowGrid) g_pGrid->Render(0);		
	if(g_bShowAxis) g_pAxis->Render(g_pDevice, g_pFont, g_Mode.Width, g_Mode.Height); 

	//if(g_bShowHelp) SysInfo(); 
	//SysInfo();

}





////////////////////////////////////////////////////////////////////////////// 
//
//  카메라 : View -Project 행렬 계산 및 설정.
// 
void CameraSetup()
{

	//-----------------------------
	// 카메라 바디 : 뷰 행렬 설정 
	//-----------------------------  
	D3DXMATRIX		mView;
  	D3DXMatrixLookAtLH(&mView, 	&g_vEye,  &g_vLookAt,  &g_vUp);	 
  	g_pDevice->SetTransform(D3DTS_VIEW, &mView);			



	//-----------------------------
	// 렌즈: 투영 변환 행렬 설정   
	//-----------------------------
	g_fAspect =  g_Mode.Width/(float)g_Mode.Height;		  

	D3DXMATRIX	mProj;
	D3DXMatrixPerspectiveFovLH(&mProj, g_fFOV, g_fAspect, g_fZnear, g_fZfar);		
 	g_pDevice->SetTransform(D3DTS_PROJECTION, &mProj);		

}



////////////////////////////////////////////////////////////////////////////// 
// 
// 카메라 상태 갱신.
//
void CameraUpdate()
{	

	// 뷰 : 카메라 정보 갱신..
 	D3DXMATRIX		mView;
 	D3DXMatrixLookAtLH(&mView,  &g_vEye, 
								&g_pHero->vPos,
								&g_vUp);
  	g_pDevice->SetTransform(D3DTS_VIEW, &mView);	

 
	//
	// 투영변환 : 렌즈의 변화는 없음
	// .............

}





/////////////////////////////////////////////////////////////////////////////
//
// 타이머 갱신
//
	
float GetEngineTime()
{
	static int oldtime = timeGetTime();
	int nowtime = timeGetTime();
	float dTime = (nowtime - oldtime) * 0.001f;
	oldtime = nowtime;

	return dTime;
}


///////////////////////////////////////////////////////////////////////////////
//
// PutFPS
//
void PutFPS(int x, int y)
{
	static int oldtime = timeGetTime();
	int nowtime = timeGetTime();

	static int frmcnt = 0;
	static float fps = 0.0f;

	++frmcnt;


	int time = nowtime - oldtime;
	if( time >= 999)
	{
		oldtime = nowtime;

		fps = (float)frmcnt*1000/(float)time;
		frmcnt = 0;
	}


	char msg[40];
	sprintf(msg,"FPS:%.1f/%d", fps, frmcnt );
	g_pFont->DrawText(NULL, msg, strlen(msg), NULL, DT_NOCLIP, D3DXCOLOR(0, 1, 0, 1));
}



 


///////////////////////////////////////////////////////////////////////////////
//
// 문자열 출력   
//
void DrawText( int x, int y, D3DXCOLOR col, char* msg, ...) 
{
	char buff[256];
	va_list vl;
	va_start(vl, msg); 
	vsprintf(buff, msg, vl);
	va_end(vl);

	RECT rc = { x, y, 0, 0};
	g_pFont->DrawText(NULL, buff, strlen(buff), &rc, DT_NOCLIP, col);
}



////////////////////////////////////////////////////////////////////////////// 
//
void SystemUpdate(float dTime)
{
  
	if(IsKeyUp(VK_SPACE)) g_bShowFrame ^= TRUE;
	g_pDevice->SetRenderState(D3DRS_FILLMODE, 
							(g_bShowFrame)?D3DFILL_WIREFRAME: D3DFILL_SOLID);
  
	//배경색 전환.
	if(g_bShowFrame) g_BkColor = g_ColDGray;
	else			 g_BkColor = g_ColGray;

	GridAxisUpdate(dTime); 
 	//CameraUpdate();		--> Render() 로 이동. 		  

}




////////////////////////////////////////////////////////////////////////////// 
//
void SystemInfoShow(int& x, int&y, D3DXCOLOR color)
{  
	//int x=1, y=1; 
	//FPS 
	//PutFPS(x, y, &g_Font);
	D3DXCOLOR col(0, 1, 0, 1);

	DrawText(x, y+=14, col, "[System]"); 
	DrawText(x, y+=14, col, "Res:%dx%d ", g_Mode.Width, g_Mode.Height); 
	DrawText(x, y+=14, (g_bShowGrid)?col:col*0.7f, "그리드: F2 (%.1f(m))", g_pGrid->GetInfo().scale); 
	DrawText(x, y+=14, (g_bShowAxis)?col:col*0.7f, "방향축: F3"); 


	y+=14;
	DrawText(x, y+=14, col, "[카메라]");  
	DrawText(x, y+=14, col, "Eye={%.2f, %.2f, %.2f}", g_vEye.x, g_vEye.y, g_vEye.z);  
	DrawText(x, y+=14, col, "Look={%.2f, %.2f, %.2f}", g_vLookAt.x, g_vLookAt.y, g_vLookAt.z);  
	DrawText(x, y+=14, col, "Up={%.2f, %.2f, %.2f}", g_vUp.x, g_vUp.y, g_vUp.z);  


	y+=14;
	DrawText(x, y+=14, col, "[렌즈]");  
	DrawText(x, y+=14, col, "FOV=%.2f (%.2fº)", g_fFOV, D3DXToDegree(g_fFOV)); 
	DrawText(x, y+=14, col, "Aspect=%.2f", g_fAspect);  
	DrawText(x, y+=14, col, "Znear=%.1f", g_fZnear); 
	DrawText(x, y+=14, col, "Zfar=%.1f", g_fZfar); 

	//텍스처 필터.★
	{
		x += 1000;
		y = 83;
		col = D3DXCOLOR(1, 1, 0, 1);
		DrawText(x, y += 14, col, "[그래픽]");

		DWORD Min, Mag, Mip, AF;

		g_pDevice->GetSamplerState(0, D3DSAMP_MINFILTER, &Min);
		g_pDevice->GetSamplerState(0, D3DSAMP_MAGFILTER, &Mag);
		g_pDevice->GetSamplerState(0, D3DSAMP_MIPFILTER, &Mip);
		g_pDevice->GetSamplerState(0, D3DSAMP_MAXANISOTROPY, &AF);

		char* TexFilter[] = { "None", "Point", "Linear", "Anisotropy" };

		DrawText(x, y += 14, col, "AA = x%d", g_dwAA);
		if (Min == D3DTEXF_ANISOTROPIC || Mag == D3DTEXF_ANISOTROPIC)
			DrawText(x, y += 14, col, "AF = x%d", AF);

		y += 14;
		DrawText(x, y += 14, col, "Min = %s", TexFilter[Min]);
		DrawText(x, y += 14, col, "Mag = %s", TexFilter[Mag]);
		//if(Mip != D3DTEXF_NONE) 
		DrawText(x, y += 14, col, "Mip = %s", TexFilter[Mip]);
		if (Min == D3DTEXF_ANISOTROPIC || Mag == D3DTEXF_ANISOTROPIC)
			DrawText(x, y += 14, col, "Aniso = x%d (max.%d)", g_dwAF, AF);


	}

}




/************ end of file "Device.cpp" ******************************/

 