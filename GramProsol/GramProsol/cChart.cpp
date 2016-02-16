#include "stdafx.h"
#include "cChart.h"
#include <vector>
#include <algorithm>
using namespace std;

Chart::Chart(double(*f_pEquation_h)(double), double dIntervalA_h, double dIntervalB_h, UINT uResolution) 
{
	if (dIntervalA_h > dIntervalB_h)
		MessageBox(NULL, L"A>B", L"Error", NULL);

	f_pEquation = f_pEquation_h;
	dIntervalA = dIntervalA_h;
	dIntervalB = dIntervalB_h;
	
	double dMaxElement; 
	double dMinElement;
	
	
	// finding the smallest and the bigget element
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
	dBoundryXRight = dIntervalB;

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

	GrainVector = createGrainVector(uResolution);
	LineXVector = createLineXVector(uResolution);
	LineYVector = createLineYVector(uResolution);

};

Chart::~Chart()
{
	f_pEquation = NULL;
}

vector<Chart::DotPosition<UINT>>* Chart::createGrainVector(UINT uResolution)
{
	vector<DotPosition<UINT>>* vResult = new vector<DotPosition<UINT>>(uResolution);
	vector<DotPosition<double>> vBuffer(uResolution);
	double dGrainSizeX =  (dBoundryXRight - dBoundryXLeft) / (double)uResolution;
	double dGrainSizeY = (dBoundryYUp- dBoundryYDown) / (double)uResolution;
	for (UINT i = 0; i < uResolution; i++)
	{
		vBuffer[i].Y=f_pEquation(dBoundryXLeft + (dGrainSizeX*i));
		
		
		vBuffer[i].X = i;
		vBuffer[i].Y = (vBuffer[i].Y - dBoundryYDown) * ((double)uResolution / (dBoundryYUp - dBoundryYDown));
		
		(*vResult)[i].X = (UINT)(vBuffer[i].X+0.5);
		(*vResult)[i].Y = (UINT)(vBuffer[i].Y+0.5);
	}
	return vResult;
}

std::vector<Chart::DotPosition<UINT>>* Chart::createLineXVector(UINT uResolution)
{
	if (dBoundryYUp <= 0 || dBoundryYDown >= 0)
		return NULL;

	vector<DotPosition<UINT>>* vResult = new vector<DotPosition<UINT>>(uResolution);
	double GrainSizeY = (double)uResolution/ (dBoundryYUp - dBoundryYDown) ;
	for (UINT i = 0; i < uResolution; i++)
	{
		(*vResult)[i].X = i;
		(*vResult)[i].Y = UINT((dBoundryYUp* GrainSizeY)+0.5);
	}
	return vResult;


}

std::vector<Chart::DotPosition<UINT>>* Chart::createLineYVector(UINT uResolution)
{
	if (dBoundryXLeft >= 0 || dBoundryXRight <= 0)
		return NULL;

	vector<DotPosition<UINT>>* vResult = new vector<DotPosition<UINT>>(uResolution);
	double GrainSizeX = (double)uResolution / (dBoundryXLeft - dBoundryXRight);
	for (UINT i = 0; i < uResolution; i++)
	{
		(*vResult)[i].X = UINT((dBoundryXLeft* GrainSizeX) + 0.5);
		(*vResult)[i].Y = i;
	}
	return vResult;


}