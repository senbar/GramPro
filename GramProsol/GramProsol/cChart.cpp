#include "stdafx.h"
#include "cChart.h"
#include <vector>
#include <algorithm>
using namespace std;

Chart::Chart(double(*f_pEquation_h)(double), double dIntervalA_h, double dIntervalB_h, UINT uiResolution) 
{
	if (dIntervalA_h > dIntervalB_h)
		MessageBox(NULL, L"A>B", L"Error", NULL);

	f_pEquation = f_pEquation_h;
	dIntervalA = dIntervalA_h;
	dIntervalB = dIntervalB_h;
	
	double dMaxElement; 
	double dMinElement;
	
	
	// finding smallest and bigget element
	double dCurrentElement;
	for (int i = 0; i < 100; i++) 
	{
		dCurrentElement= f_pEquation(dIntervalA + (((dIntervalB - dIntervalA) / 100)*i));
		
		if (i == 0)
		{
			dMaxElement = dCurrentElement;
			dMinElement = dCurrentElement;
		}
		if (dMaxElement < dCurrentElement)
			dMaxElement = dCurrentElement;
		if (dMinElement > dCurrentElement)
			dMinElement = dCurrentElement;
	}
	
	dBoundryXLeft = dIntervalA;
	dBoundryXRright = dIntervalB;

	//if function is constant we will get division by zero later on
	if (dMaxElement != dMinElement)
	{
		dBoundryYUp = dMaxElement;
		dBoundryYDown = dMinElement;
	}
	else if (dMaxElement == dMinElement)
	{
		dBoundryYUp = dMaxElement + 1;
		dBoundryYDown = dMinElement - 1;
	}

	LineXVector = getLineXVector(uiResolution);

};

Chart::~Chart()
{
	f_pEquation = NULL;
}

vector<Chart::DotPosition<int>>* Chart::getGrainVector(UINT uResolution)
{
	vector<DotPosition<int>>* vResult = new vector<DotPosition<int>>(uResolution);
	vector<DotPosition<double>> vBuffer(uResolution);
	double dGrainSizeX =  (dBoundryXRright - dBoundryXLeft) / (double)uResolution;
	double dGrainSizeY = (dBoundryYUp- dBoundryYDown) / (double)uResolution;
	for (UINT i = 0; i < uResolution; i++)
	{
		vBuffer[i].Y=f_pEquation(dBoundryXLeft + (dGrainSizeX*i));
		
		
		vBuffer[i].X = i;
		vBuffer[i].Y = (vBuffer[i].Y - dBoundryYDown) * ((double)uResolution / (dBoundryYUp - dBoundryYDown));
		CHAR str[256];
		sprintf_s(str, "buffery %f  :  %f , intervat to %f \n", (float)vBuffer[i].Y, vBuffer[i].X, (float)dIntervalA);
		OutputDebugStringA(str);
		(*vResult)[i].X = (int)(vBuffer[i].X+0.5);
		(*vResult)[i].Y = (int)(vBuffer[i].Y+0.5);
	}
	return vResult;
}

std::vector<Chart::DotPosition<UINT>>* Chart::getLineXVector(UINT uResolution)
{
	vector<DotPosition<UINT>>* vResult = new vector<DotPosition<UINT>>(uResolution);
	double GrainSizeY = (double)uResolution/ (dBoundryYUp - dBoundryYDown) ;
	for (UINT i = 0; i < uResolution; i++)
	{
		(*vResult)[i].X = i;
		(*vResult)[i].Y = UINT((dBoundryYUp* GrainSizeY)+0.5);
	}
	return vResult;


}