#pragma once

#include "resource.h"
#include "cChart.h"
#include <iostream>
HWND g_hwndPlot=NULL;
HBRUSH g_hbrBackground = CreateSolidBrush(RGB(0, 0, 0));
Chart* g_cChart;


double QuadraticEquation(double);
std::vector<Chart::DotPosition<int>>* g_vDots;

#define CHART_WIDTH 400
#define CHART_HEIGHT 400
#define RESOLUTION 400