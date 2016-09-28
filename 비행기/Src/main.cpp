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
// ���� ������.
//
HWND g_hWnd = NULL;
BOOL g_bLoop = TRUE;

char* g_ClassName = "B3Yena::D3D TripleWindmill";
extern char* g_WindowName;

// ������ ���� ���� �Լ���.
BOOL InitWindow(int width, int height);
void ResizeWindow(HWND hWnd, UINT NewWidth, UINT NewHeight);
BOOL MessagePump();

// �޼��� ó�� ���ν���.
LRESULT CALLBACK MsgProc(HWND, UINT, WPARAM, LPARAM);

 
/////////////////////////////////////////////////////////////////////////////
//
// WinMain : ���� �Լ�.
//
int APIENTRY WinMain(HINSTANCE hInstance,
					 HINSTANCE hPrevInstance,
					 LPSTR     lpCmdLine,
					 int       nCmdShow)
{
	//------------------------------------------------------------------//
	// �⺻���� ������ ������ ����..                                //
	//------------------------------------------------------------------//
	if(!InitWindow(1200, 700)) return 0;

	//------------------------------------------------------------------//
	// DX �� ���� ��ü �ʱ�ȭ.                                       //
	//------------------------------------------------------------------//
	if(FAILED(DXSetup(g_hWnd)))
		return 0;

	//------------------------------------------------------------------//
	// ������ �ε�                                              //
	//------------------------------------------------------------------//
	if(!DataLoading())
	{
		g_bLoop = FALSE;  
	}
 
	//------------------------------------------------------------------//
	// ����  ����														//
	//------------------------------------------------------------------//
	while(g_bLoop) 
	{
		if(!MessagePump())		// �޼��� ����.
			break;
 
		SceneRender();			//������.	 
	}

	//------------------------------------------------------------------//
	// ���ø����̼� ����                                        // 
	//------------------------------------------------------------------//
	DataRelease();				//������ ����.
	DXRelease();				//DX �� ���� ��ü ����.

	return 0;
}



 

//////////////////////////////////////////////////////////////////////////////
//
// MsgProc :  ������ �޼��� ���ν���.
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
// InitWindow  : ������ ���� �Լ�.
//
// width  : ������ ������ ���� ũ�� (pixel)
// height : ������ ������ ���� ũ�� (pixel)
//
// �Է¹��� ũ�⿡ ���߾� ������ ������ �����ϱ� ���ؼ� 
// Ŭ���̾�Ʈ ������ ���� ������ ��ü ũ�⸦ �������մϴ�.
//
BOOL InitWindow(int width, int height)
{
	WNDCLASSEX wc = { 
		sizeof(WNDCLASSEX), CS_CLASSDC, MsgProc, 0, 0,
			::GetModuleHandle(NULL), NULL, NULL, NULL, NULL,
			g_ClassName, NULL 
	};

	RegisterClassEx(&wc);
 
	//������ ����.
	HWND hWnd = ::CreateWindow( g_ClassName, g_WindowName, 
								WS_OVERLAPPEDWINDOW, 0, 0, 
								width, height, 
								GetDesktopWindow(), NULL, 
								wc.hInstance, NULL
								);
	if(hWnd == NULL) return FALSE; 
	

	::ShowWindow(hWnd, SW_SHOWDEFAULT);
	::UpdateWindow(hWnd);

	//������ �ڵ� �������� ����.
	g_hWnd = hWnd;
	g_Mode.Width = width;
	g_Mode.Height = height;

	//Ŭ���̾�Ʈ ���� ũ�� ������ : �ʼ�. ��������
	ResizeWindow(hWnd, width, height);

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// 
// int MessagePump() : ������ �޼��� ó�� �Լ�.
//
// ���� ���� �޼��� ó���� ���ؼ� �޼��� ������ �����Ѵ�            
// ��������(OS)�κ��� �� ���ø����̼����� Ư���� �޼����� �������  
// �ʴ´ٸ�  ������ ���� �ϵ��� �մϴ�.                               
// ���Ŀ� �ѹ��� ������ �� ����.                                    
// 
int MessagePump()
{
	MSG msg;	::ZeroMemory(&msg, sizeof(msg));

	while(1)
	{
		//�޼��� ť�� �޼����� ������...ó���ϰ�..
		if(::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if(msg.message == WM_QUIT)			//������ ���Ḧ ���� ����.
				return FALSE;		

			//������ �޼��� ó��.
			::TranslateMessage(&msg);
			::DispatchMessage(&msg);
		}
		else  //Ư���� �޼����� ���ٸ� ����(������)�� �����մϴ�..
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
// â����� ��� �ػ� ����� ���߾� ��ü ������ ũ�⸦ �������մϴ�. 
// ex)
//'Ŭ���� ��Ʈ'������ 640 * 480 �� ���߾�  ��ü �������� ũ�⸦ 
// �ٽ� �����մϴ�. --> �׷��� '���� �̹���'�� ��� ȭ�鿡 ���δ�.
//
// ��  �� :  Ŭ���̾�Ʈ ������ ũ�� - NewWidth, NewHeight
// ���ϰ� :  ����. 
//
// 2004.05.28. ������.
//
void ResizeWindow(HWND hWnd, UINT NewWidth, UINT NewHeight)
{	
	//���� �������� ��Ÿ�� ���ϱ�.
	RECT oldrc;
	DWORD sytle  = (DWORD) ::GetWindowLong(hWnd, GWL_STYLE);
	DWORD exstyle = (DWORD) ::GetWindowLong(hWnd, GWL_EXSTYLE);

	//���� ������ '��ü' ũ�� (��ũ����ǥ) �� ��´�.
	::GetWindowRect(hWnd, &oldrc);

	//���� ������ �������� 'Ŭ���̾�Ʈ' ���� ũ�� ����ϱ�.
	RECT newrc;
	newrc.left = 0;  
	newrc.top = 0;
	newrc.right = NewWidth;
	newrc.bottom = NewHeight;

	//newrc ��ŭ�� Ŭ���̾�Ʈ ������ �����ϴ� ������ '��ü' ũ�⸦ ���մϴ�.
	//���� '�޴�' �� ���ٴ� �����Ͽ� ó���ǰ� ����.
	//���� ����� newrc �� �ٽ� ���´�. ( ��ũ�� ��ǥ )
	//exstyle &= ~WS_EX_TOPMOST;
	::AdjustWindowRectEx(&newrc, sytle, NULL, exstyle);


	//������ �������� �ʺ�� ���� ���մϴ�. 
	int width = (newrc.right - newrc.left);
	int height = (newrc.bottom - newrc.top);


	//���ο� ũ�⸦ �����쿡 �����մϴ�.
	::SetWindowPos(hWnd, HWND_NOTOPMOST, 
					oldrc.left, oldrc.top, 
 					width, height, SWP_SHOWWINDOW);

}

/*************** end of "main.cpp" *****************************************/