// GramProsol.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "GramProsol.h"

#define MAX_LOADSTRING 100

using namespace std;

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
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
    LoadStringW(hInstance, IDC_GRAMPROSOL, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_GRAMPROSOL));

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

    return (int) msg.wParam;
}




ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_GRAMPROSOL));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW);
    wcex.lpszMenuName   = NULL;
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}


BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; 

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
      CW_USEDEFAULT, CW_USEDEFAULT, 750, 475, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
	case WM_CREATE:
		try {
			g_hwndPlot = CreateWindowExW(NULL, L"STATIC", L"test", WS_CHILD | WS_VISIBLE | WS_BORDER, 0, 0, CHART_WIDTH, CHART_HEIGHT + 3, hWnd, (HMENU)IDC_STATIC, hInst, NULL);
			if (g_hwndPlot == NULL)
				throw(L"STATIC ERROR");

			if(CreateWindowExW(NULL, L"STATIC", L"Who bents our curves:", WS_CHILD | WS_VISIBLE, 415, 150, 400, 20, hWnd, NULL, hInst, NULL)==NULL)
				throw(L"STATIC ERROR");

			if (CreateWindowExW(NULL, L"EDIT", L"Equation edit", WS_CHILD | WS_VISIBLE | WS_BORDER, 415, 25, 300, 20, hWnd, (HMENU)IDD_EQUATION_DIALOGBAR, hInst, NULL) == NULL)
				throw(L"EQUATION DIALOGBAR ERROR");


			if (CreateWindowExW(NULL, L"EDIT", L"", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_CENTER, 415, 50, 100, 20,
								hWnd, (HMENU)IDD_EQUATION_INTERVAL_FROM, hInst, NULL) == NULL)
				throw(L"EQUATION INTERVAL FROM ERROR");


			if (CreateWindowExW(NULL, L"EDIT", L"", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_CENTER, 525, 50, 100, 20, 
								hWnd, (HMENU)IDD_EQUATION_INTERVAL_TO, hInst, NULL) == NULL)
				throw(L"EQUATION INTERBAL TO ERROR");

			if (CreateWindowExW(NULL, L"BUTTON", L"Execute", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_CENTER, 635, 50, 80, 20,
				hWnd, (HMENU)IDD_BUTTON_EXECUTE, hInst, NULL) == NULL)
				throw(L"BUTTON ERROR");
		}
		catch (WCHAR* cCatch)
		{
			MessageBoxW(NULL, cCatch, L"Error", NULL);
			SendMessage(hWnd, WM_DESTROY, NULL, NULL);
		}

		// setting subclasses to prevent getting characters from interval controls
		SetWindowSubclass(GetDlgItem(hWnd, IDD_EQUATION_INTERVAL_FROM), subclassIntervalEditProc, 0, 0);
		SetWindowSubclass(GetDlgItem(hWnd, IDD_EQUATION_INTERVAL_TO), subclassIntervalEditProc, 0, 0);

		/////////////
		//CHART CREATION 
		/////////////
		g_cChart = new Chart(&QuadraticEquation, -2, 2, RESOLUTION);

		g_bmpTheRippedGuy = NULL;
		//Create that fucker
		g_bmpTheRippedGuy = (HBITMAP) LoadImage(NULL, L"POLICJA3.BMP", IMAGE_BITMAP, 0,0, LR_LOADFROMFILE);

		break;

	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{

		}
	}
	break;

	case WM_PAINT:
	{

		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);

		EndPaint(hWnd, &ps);



		PAINTSTRUCT psPlot;
		HDC hdcPlot = BeginPaint(g_hwndPlot, &psPlot);

		std::vector<Chart::DotPosition<UINT>>* LineYVector = g_cChart->getLineYVectorPtr();
		std::vector<Chart::DotPosition<UINT>>* LineXVector = g_cChart->getLineXVectorPtr();
		std::vector<Chart::DotPosition<UINT>>* GrainVector = g_cChart->getGrainVectorPtr();

		for (int i = 0; i < RESOLUTION; i++)
		{
			SetPixel(hdcPlot, (*GrainVector)[i].X, RESOLUTION - (*GrainVector)[i].Y, RGB(0, 0, 0));

			if (LineXVector != NULL)
				SetPixel(hdcPlot, (*LineXVector)[i].X, (*LineXVector)[i].Y, RGB(255, 0, 0));
			if (LineYVector != NULL)
				SetPixel(hdcPlot, (*LineYVector)[i].X, (*LineYVector)[i].Y, RGB(255, 0, 0));
		}

		BITMAP bm2;

		SetPixel(hdc, 415, 52, RGB(0, 255, 0));
		HDC hdcMem = CreateCompatibleDC(hdc);
		HBITMAP hbmOld = (HBITMAP)SelectObject(hdcMem, g_bmpTheRippedGuy);

		GetObject(g_bmpTheRippedGuy, sizeof(bm2), &bm2);

		StretchBlt(hdc, 415, 175, 300, 225, hdcMem, 0, 0, bm2.bmWidth, bm2.bmHeight, SRCCOPY);

		SelectObject(hdcMem, hbmOld);
		DeleteDC(hdcMem);

		EndPaint(g_hwndPlot, &psPlot);


		//Regulating time


		

		

	}
	break;
	
    case WM_DESTROY:
		DeleteObject(g_bmpTheRippedGuy);
		delete g_cChart;
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}


LRESULT CALLBACK subclassIntervalEditProc(HWND hWnd, UINT uMsg, WPARAM wParam,
	LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData)
{
	if (uMsg == WM_CHAR && wParam >= ' ' && !isdigit(wParam) && wParam!='-' && wParam!=',' && wParam!='.')
		return 0;
	if (uMsg == WM_CHAR &&  wParam == '-')
	{
		
		WCHAR chString[100];
		wstring sString;

		GetWindowText(hWnd, chString, 100);
		sString = chString;

		int iMinusPos = sString.find(L'-');

		if (iMinusPos == string::npos)
			sString.insert(0, L"-");
		else
			sString.erase(iMinusPos, 1);

		SetWindowText(hWnd, sString.c_str());

		return 0;
	}
	if ((uMsg == WM_CHAR &&  wParam == ',') || (uMsg == WM_CHAR &&  wParam == '.'))
	{
		WCHAR chString[100];
		wstring sString;
		int wPosition;
		
		SendMessage(hWnd, EM_GETSEL, (WPARAM)&wPosition, NULL);
		GetWindowText(hWnd, chString, 100);
		sString = chString;

		int iDotPos = sString.find(L'.');
		int iCommaPos = sString.find(L',');

		if (iDotPos == string::npos && iCommaPos == string::npos)
		{
			sString.insert(wPosition, L".");
			SetWindowText(hWnd, sString.c_str());
			SendMessage(hWnd, EM_SETSEL, (WPARAM)wPosition + 1, (LPARAM)wPosition+1);
		}
		return 0;
	}
	else
		return DefSubclassProc(hWnd, uMsg, wParam, lParam);
}






//
//
double QuadraticEquation(double x)
{
	
	return (x*x*x);
}