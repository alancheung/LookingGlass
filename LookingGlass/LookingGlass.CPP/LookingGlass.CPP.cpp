// LookingGlass.CPP.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "LookingGlass.CPP.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: Place code here.

	// Initialize global strings
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_LOOKINGGLASSCPP, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LOOKINGGLASSCPP));

	MSG msg;

	// Main message loop:
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int)msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LOOKINGGLASSCPP));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)CreateSolidBrush(TRANSPARENCY_KEY_COLOR);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_LOOKINGGLASSCPP);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // Store instance handle in our global variable

	HWND hWnd = CreateWindowW(
		szWindowClass, 
		szTitle, 
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, 
		1920, 1080, 
		nullptr, nullptr, hInstance, nullptr);

	if (!hWnd)
	{
		return FALSE;
	}

	// Set the window as topmost
	SetWindowPos(hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);

	// Set the window as a layered window to enable transparency
	SetWindowLong(hWnd, GWL_EXSTYLE, GetWindowLong(hWnd, GWL_EXSTYLE) | WS_EX_LAYERED);

	// Set the transparency color key
	COLORREF clrKey = TRANSPARENCY_KEY_COLOR;
	SetLayeredWindowAttributes(hWnd, clrKey, 255, LWA_COLORKEY);

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_COMMAND:
		{
			int wmId = LOWORD(wParam);
			// Parse the menu selections:
			switch (wmId)
			{
			case IDM_ABOUT:
				DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
				break;
			case IDM_EXIT:
				DestroyWindow(hWnd);
				break;
			default:
				return DefWindowProc(hWnd, message, wParam, lParam);
			}
		}
		break;
		case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hWnd, &ps);
			
			Paint(hWnd, hdc);

			EndPaint(hWnd, &ps);
		}
		break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		default:
				return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

void Paint(const HWND hWnd, const HDC& hdc)
{
	//PaintDebugMessages(hdc, hWnd);

	// Draw a black border around the client area
	RECT rect;
	GetClientRect(hWnd, &rect);
	HBRUSH hBrush = CreateSolidBrush(RGB(0, 0, 0));
	FrameRect(hdc, &rect, hBrush);
	DeleteObject(hBrush);

	SetBkMode(hdc, TRANSPARENT);

	// Retrieve the client area rectangle
	TCHAR clientRect[64];
	_stprintf_s(clientRect, _T("Client Rect: (%d, %d)"), rect.right - rect.left, rect.bottom - rect.top);
	TextOut(hdc, 1725, 980, clientRect, lstrlen(clientRect));

	TextOut(hdc, 1725, 1000, egoStr, egoStrLen);
}

void PaintDebugMessages(const HDC& hdc, const HWND& hWnd)
{
	//// Retrieve the mouse position
	//POINT pt;
	//GetCursorPos(&pt);
	////ScreenToClient(hWnd, &pt); // Convert screen coordinates to client coordinates

	//// Convert the mouse position to a string
	//TCHAR szMousePos[64];
	//TCHAR dragStartStr[64];
	//TCHAR dragCurrStr[64];
	//_stprintf_s(szMousePos, _T("Mouse Position: (%d, %d)"), pt.x, pt.y);
	//_stprintf_s(dragStartStr, _T("Drag Start: (%d, %d)"), dragStart.x, dragStart.y);
	//_stprintf_s(dragCurrStr, _T("Drag Current: (%d, %d)"), dragCurrent.x, dragCurrent.y);

	//// Draw the mouse position on the window
	//TextOut(hdc, 10, 10, szMousePos, lstrlen(szMousePos));
	//TextOut(hdc, 10, 30, dragStartStr, lstrlen(dragStartStr));
	//TextOut(hdc, 10, 50, dragCurrStr, lstrlen(dragCurrStr));
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
