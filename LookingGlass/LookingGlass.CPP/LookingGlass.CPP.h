#pragma once

#include "resource.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

// Magenta color
#define TRANSPARENCY_KEY_COLOR RGB(255, 0, 255)

/* Ego string declaration */
TCHAR egoStr[] = _T("LookingGlass by Alan C.");
/* Length of the Ego string */
int egoStrLen = lstrlen(egoStr);

void Paint(const HWND hWnd, const HDC& hdc);
void PaintDebugMessages(const HDC& hdc, const HWND& hWnd);
