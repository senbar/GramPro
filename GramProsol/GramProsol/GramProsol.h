#pragma once

#include "resource.h"
#include "cChart.h"
#include <iostream>
#include <string>
#include <Commctrl.h>
#include <sstream>

HWND g_hwndPlot=NULL;
Chart* g_cChart;

//przemek-inspired GUI
HBITMAP g_bmpTheRippedGuy;

//DEBUG ONLY FUNCTION
double QuadraticEquation(double);

//subclassing
LRESULT CALLBACK subclassIntervalEditProc(HWND hWnd, UINT uMsg, WPARAM wParam,
	LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData);
LRESULT CALLBACK subclassStaticPlotProc(HWND hWnd, UINT uMsg, WPARAM wParam,
	LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData);


//funcition for getting interval from edit window
double GetIntervalFromWindow(HWND windowToGetIntervalFrom);


//todo: delete these fuckers
#define CHART_WIDTH 400
#define CHART_HEIGHT 400
#define RESOLUTION 400