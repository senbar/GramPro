#pragma once

#include "resource.h"
#include "cChart.h"
#include <iostream>

HWND g_hwndPlot=NULL;
Chart* g_cChart;

//DEBUG ONLY FUNCTION
double QuadraticEquation(double);

//todo: delete these fuckers
#define CHART_WIDTH 400
#define CHART_HEIGHT 400
#define RESOLUTION 400