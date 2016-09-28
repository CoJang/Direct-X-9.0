#if _MSC_VER >= 1900
#pragma comment(lib,"legacy_stdio_definitions.lib")
#endif

//
// Direct3D Basic Techniques
//
// main.cpp :   
//
// 2003.11.4. Kihong Kim / mad_dog@hanmail.net		
// 2004.05.07. Update
// 2005.09.23. Update (.Net)
// 2009.11.19. Update 
//
#include "windows.h"
#include "Device.h"
#include "Render.h"
 

//////////////////////////////////////////////////////////////////////////////
//
// 전역 변수들.
//
HWND g_hWnd = NULL;
BOOL g_bLoop = TRUE;

char* g_ClassName = "B3Yena::D3D TripleWindmill";
extern char* g_WindowName;

// 윈도우 설정 관련 함수들.
BOOL InitWindow(int width, int height);
void ResizeWindow(HWND hWnd, UINT NewWidth, UINT NewHeight);
BOOL MessagePump();

// 메세지 처리 프로시져.
LRESULT CALLBACK MsgProc(HWND, UINT, WPARAM, LPARAM);

 
/////////////////////////////////////////////////////////////////////////////
//
// WinMain : 메인 함수.
//
int APIENTRY WinMain(HINSTANCE hInstance,
					 HINSTANCE hPrevInstance,
					 LPSTR     lpCmdLine,
					 int       nCmdShow)
{
	//------------------------------------------------------------------//
	// 기본적인 윈도우 프레임 생성..                                //
	//------------------------------------------------------------------//
	if(!InitWindow(1200, 700)) return 0;

	//------------------------------------------------------------------//
	// DX 및 관련 객체 초기화.                                       //
	//------------------------------------------------------------------//
	if(FAILED(DXSetup(g_hWnd)))
		return 0;

	//------------------------------------------------------------------//
	// 데이터 로딩                                              //
	//------------------------------------------------------------------//
	if(!DataLoading())
	{
		g_bLoop = FALSE;  
	}
 
	//------------------------------------------------------------------//
	// 메인  루프														//
	//------------------------------------------------------------------//
	while(g_bLoop) 
	{
		if(!MessagePump())		// 메세지 펌프.
			break;
 
		SceneRender();			//렌더링.	 
	}

	//------------------------------------------------------------------//
	// 어플리케이션 종료                                        // 
	//------------------------------------------------------------------//
	DataRelease();				//데이터 제거.
	DXRelease();				//DX 및 관련 객체 제거.

	return 0;
}



 

//////////////////////////////////////////////////////////////////////////////
//
// MsgProc :  윈도우 메세지 프로시져.
// 
LRESULT CALLBACK MsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch(msg)
	{ 
	case WM_KEYDOWN:
		switch(wParam)
		{
 		case VK_ESCAPE:
			SendMessage(hwnd, WM_DESTROY, 0, 0);
			break;
		}
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0); 
		return 0;
	}

	return DefWindowProc(hwnd, msg, wParam, lParam);

}


/////////////////////////////////////////////////////////////////////////////
//
// InitWindow  : 윈도우 생성 함수.
//
// width  : 생성할 윈도우 가로 크기 (pixel)
// height : 생성할 윈도우 세로 크기 (pixel)
//
// 입력받은 크기에 맞추어 렌더링 영역을 생성하기 위해서 
// 클라이언트 영역을 포함 윈도우 전체 크기를 재조정합니다.
//
BOOL InitWindow(int width, int height)
{
	WNDCLASSEX wc = { 
		sizeof(WNDCLASSEX), CS_CLASSDC, MsgProc, 0, 0,
			::GetModuleHandle(NULL), NULL, NULL, NULL, NULL,
			g_ClassName, NULL 
	};

	RegisterClassEx(&wc);
 
	//윈도우 생성.
	HWND hWnd = ::CreateWindow( g_ClassName, g_WindowName, 
								WS_OVERLAPPEDWINDOW, 0, 0, 
								width, height, 
								GetDesktopWindow(), NULL, 
								wc.hInstance, NULL
								);
	if(hWnd == NULL) return FALSE; 
	

	::ShowWindow(hWnd, SW_SHOWDEFAULT);
	::UpdateWindow(hWnd);

	//윈도우 핸들 전역변수 복사.
	g_hWnd = hWnd;
	g_Mode.Width = width;
	g_Mode.Height = height;

	//클라이언트 영역 크기 재조정 : 필수. 삭제금지
	ResizeWindow(hWnd, width, height);

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// 
// int MessagePump() : 윈도우 메세지 처리 함수.
//
// 보다 빠른 메세지 처리를 위해서 메세지 펌프를 수정한다            
// 윈도우즈(OS)로부터 이 어플리케이션으로 특별히 메세지가 날라오지  
// 않는다면  게임을 진행 하도록 합니다.                               
// 향후에 한번더 버전업 할 것임.                                    
// 
int MessagePump()
{
	MSG msg;	::ZeroMemory(&msg, sizeof(msg));

	while(1)
	{
		//메세지 큐에 메세지가 있으면...처리하고..
		if(::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if(msg.message == WM_QUIT)			//윈도우 종료를 위해 리턴.
				return FALSE;		

			//나머지 메세지 처리.
			::TranslateMessage(&msg);
			::DispatchMessage(&msg);
		}
		else  //특별한 메세지가 없다면 게임(렌더링)을 진행합니다..
		{
			return TRUE;		
		}
	}

	return FALSE;
}





//////////////////////////////////////////////////////////////////////////////
//
// void B3D_ResizeWindow(UINT NewWidth, UINT NewHeight)
//
// 창모드의 경우 해상도 사이즈에 맞추어 전체 윈도우 크기를 재조정합니다. 
// ex)
//'클라이 언트'영역을 640 * 480 에 맞추어  전체 윈도우의 크기를 
// 다시 보정합니다. --> 그래야 '게임 이미지'가 모두 화면에 보인다.
//
// 인  자 :  클라이언트 영역의 크기 - NewWidth, NewHeight
// 리턴값 :  없음. 
//
// 2004.05.28. 버전업.
//
void ResizeWindow(HWND hWnd, UINT NewWidth, UINT NewHeight)
{	
	//현재 윈도우의 스타일 구하기.
	RECT oldrc;
	DWORD sytle  = (DWORD) ::GetWindowLong(hWnd, GWL_STYLE);
	DWORD exstyle = (DWORD) ::GetWindowLong(hWnd, GWL_EXSTYLE);

	//현재 윈도우 '전체' 크기 (스크린좌표) 를 얻는다.
	::GetWindowRect(hWnd, &oldrc);

	//새로 생성될 윈도우의 '클라이언트' 영역 크기 계산하기.
	RECT newrc;
	newrc.left = 0;  
	newrc.top = 0;
	newrc.right = NewWidth;
	newrc.bottom = NewHeight;

	//newrc 만큼의 클라이언트 영역을 포함하는 윈도우 '전체' 크기를 구합니다.
	//현재 '메뉴' 는 없다는 가정하에 처리되고 있음.
	//계산된 결과는 newrc 에 다시 들어온다. ( 스크린 좌표 )
	//exstyle &= ~WS_EX_TOPMOST;
	::AdjustWindowRectEx(&newrc, sytle, NULL, exstyle);


	//보정된 윈도우의 너비와 폭을 구합니다. 
	int width = (newrc.right - newrc.left);
	int height = (newrc.bottom - newrc.top);


	//새로운 크기를 윈도우에 설정합니다.
	::SetWindowPos(hWnd, HWND_NOTOPMOST, 
					oldrc.left, oldrc.top, 
 					width, height, SWP_SHOWWINDOW);

}

/*************** end of "main.cpp" *****************************************/