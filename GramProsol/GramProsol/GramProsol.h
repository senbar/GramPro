#pragma once

#include "resource.h"
#include "cChart.h"
#include <iostream>
HWND g_hwndPlot=NULL;

Chart* g_cChart;


double QuadraticEquation(double);

#define CHART_WIDTH 400
#define CHART_HEIGHT 400
#define RESOLUTION 400