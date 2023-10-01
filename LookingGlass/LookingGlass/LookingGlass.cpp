// LookingGlass.cpp : Defines the entry point for the application.
//

#include "pch.h"
#include "framework.h"
#include "LookingGlass.h"

// GdiPlus imports
#include <windows.h>
#include <objidl.h>
#include <gdiplus.h>
#include <string>
using namespace Gdiplus;
#pragma comment (lib,"Gdiplus.lib")

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                RegisterWindow(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

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
    LoadStringW(hInstance, IDC_LOOKINGGLASS, szWindowClass, MAX_LOADSTRING);
    RegisterWindow(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LOOKINGGLASS));

    // Main message loop:
    MSG msg;
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}

//
//  FUNCTION: RegisterWindow()
//
//  PURPOSE: Registers the window class.
//
ATOM RegisterWindow(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LOOKINGGLASS));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_LOOKINGGLASS);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

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

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);

   std::string str = "";
   RenderWindow(hWnd, );

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
    case WM_LBUTTONDOWN:
        PostMessage(hWnd, WM_NCLBUTTONDOWN, HTCAPTION, lParam);  /* send a HTCAPTION to the message queue */
        return DefWindowProc(hWnd, message, wParam, lParam);
        break;
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
            // TODO: Add any drawing code that uses hdc here...
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

//transparentwindowbuilder.cpp  
HWND MakeTransparentWindowProc(HINSTANCE hThisInstance,


    int nCmdShow,
    const wchar_t* ImagePng1, /* This is the PNG image path */
    const wchar_t* windowClassName1,/* This is the class name */
    const wchar_t* windowName1, /* This is the application name */
    int width, /* This is the window width */
    int height,/* This is the window height */
    WNDPROC windocProcedure,
    bool toolwindow, HWND Parent)
{
    /* Start GDIPlus */
    ULONG_PTR gdiplusStartupToken;  /* GDIPlus Startup Token */
    Gdiplus::GdiplusStartupInput gdiInput;
    Gdiplus::GdiplusStartup(&gdiplusStartupToken, &gdiInput, NULL);


    /* Make a transparent Window*/

    /* Local Variables*/

    HWND hwnd;               /* This is the handle for our window */
    /* Make Transparent Window */
    auto result = makeTransParentWindow(hThisInstance,  /* the hInstance, Should use WinMains HInstance */
        hwnd,  /* This is the handle for our window */
        nCmdShow,  /* The show Window Flag */
        ImagePng1,  /* The path to the Image File */
        windocProcedure, /* The pointer to the window procedure */
        windowClassName1, /* The name of the NEw class to create */
        width,/* The length */
        height,/* The width */
        windowName1, toolwindow, Parent);

    /* Shut down GDIPlus*/
    Gdiplus::GdiplusShutdown(gdiplusStartupToken);

    return result ? hwnd : nullptr;
}

bool makeTransParentWindow(HINSTANCE& hThisInstance, HWND& hWnd, int& nCmdShow, const wchar_t*& imagePath, WNDPROC lpfnWndProc, const wchar_t*& szClassName, int Width, int Height, const wchar_t*& szWindowName, bool toolwindow, HWND Parent)
{
    WNDCLASSEX wincl;        /* Data structure for the windowclass */

    if (!RegisterWindow(wincl, hThisInstance, szClassName, lpfnWndProc)) return false;

    /* The class is registered, let's create the program*/
    if (!CreateWindowPane(hWnd, szClassName, Width, Height, hThisInstance, szWindowName, toolwindow, Parent)) return false;

    /* Make the window visible on the screen */
    ShowWindow(hWnd, nCmdShow);

    RenderWindow(hWnd, imagePath);

    return true;
}

void RenderWindow(HWND& hWnd, const wchar_t*& imagePath)
{
    RECT wndRect;

    ::GetWindowRect(hWnd, &wndRect);

    SIZE wndSize = { wndRect.right - wndRect.left,wndRect.bottom - wndRect.top };

    DrawSizedWindow(hWnd, wndSize, imagePath);
}

void DrawSizedWindow(HWND& hWnd, SIZE& wndSize, const wchar_t*& imagePath)
{
    HDC hdc = ::GetDC(hWnd);

    HDC memDC = ::CreateCompatibleDC(hdc);

    HBITMAP memBitmap = ::CreateCompatibleBitmap(hdc, wndSize.cx, wndSize.cy);

    SelectAndDrawObject(memDC, memBitmap, imagePath, wndSize);

    HDC screenDC = GetDC(NULL);

    BlendLayeredWindow(hWnd, screenDC, wndSize, memDC);

    CleanUpObjects(memDC, memBitmap, hWnd, screenDC);
}

void SelectAndDrawObject(HDC& memDC, const HBITMAP& memBitmap, const wchar_t*& imagePath, SIZE& wndSize)
{
    ::SelectObject(memDC, memBitmap);

    ::DrawGdiImage(imagePath, memDC, wndSize);
}

void BlendLayeredWindow(HWND& hWnd, const HDC& screenDC, SIZE& wndSize, const HDC& memDC)
{
    POINT ptSrc = { 0,0 };

    BLENDFUNCTION blendFunction;

    ::SetBlendFunctionSetiings(blendFunction);

    ::UpdateLayeredWindow(hWnd, screenDC, &ptSrc, &wndSize, memDC, &ptSrc, 0, &blendFunction, 2);
}

void CleanUpObjects(const HDC& memDC, const HBITMAP& memBitmap, HWND& hWnd, const HDC& screenDC)
{
    ::DeleteDC(memDC);

    ::DeleteObject(memBitmap);

    ::ReleaseDC(hWnd, screenDC);
}

void DrawGdiImage(const wchar_t*& imagePath, const HDC& memDC, SIZE& wndSize)
{
    Gdiplus::Image image(imagePath);
    Gdiplus::Graphics graphics(memDC);
    graphics.DrawImage(&image, 0, 0, wndSize.cx, wndSize.cy);
}

bool CreateWindowPane(HWND& hWnd, const wchar_t*& szClassName, int Width, int Height, HINSTANCE& hThisInstance, const wchar_t*& windowName, bool toolwindow, HWND Owner)
{
    if (toolwindow)
    {
        hWnd = CreateWindowEx(
            WS_EX_LAYERED | WS_EX_NOACTIVATE,                   /* Extended possibilites for variation */
            szClassName,         /* Classname */
            windowName,       /* Title Text */
            WS_POPUPWINDOW | WS_CHILD, /* default window */
            CW_USEDEFAULT,       /* Windows decides the position */
            CW_USEDEFAULT,       /* where the window ends up on the screen */
            Width,                 /* The programs width */
            Height,                 /* and height in pixels */
            Owner,        /* The window is a child-window to desktop */
            NULL,                /* No menu */
            hThisInstance,       /* Program Instance handler */
            NULL                 /* No Window Creation data */
        );

    }
    else
    {
        hWnd = CreateWindowEx(
            WS_EX_LAYERED,                   /* Extended possibilites for variation */
            szClassName,         /* Classname */
            windowName,       /* Title Text */
            WS_POPUPWINDOW, /* default window */
            CW_USEDEFAULT,       /* Windows decides the position */
            CW_USEDEFAULT,       /* where the window ends up on the screen */
            Width,                 /* The programs width */
            Height,                 /* and height in pixels */
            HWND_DESKTOP,        /* The window is a child-window to desktop */
            NULL,                /* No menu */
            hThisInstance,       /* Program Instance handler */
            NULL                 /* No Window Creation data */
        );
    }
    return hWnd != nullptr;
}

void SetBlendFunctionSetiings(BLENDFUNCTION& blendFunction)
{
    blendFunction.AlphaFormat = AC_SRC_ALPHA;
    blendFunction.BlendFlags = 0;
    blendFunction.BlendOp = AC_SRC_OVER;
    blendFunction.SourceConstantAlpha = 220;
}