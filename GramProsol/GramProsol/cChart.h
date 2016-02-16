#pragma once
#include <vector>

#define POSITIVE(n) ((n) < 0 ? 0 - (n) : (n))

class Chart
{
public:
	template <typename var>
	struct DotPosition
	{
	public:
		var X;
		var Y;
	};
private:

	double (*f_pEquation)(double);

	double dBoundryXLeft;
	double dBoundryXRright;
	double dBoundryYUp;
	double dBoundryYDown;
	

	double dIntervalA;
	double dIntervalB;

	std::vector<DotPosition<UINT>>* LineXVector;

	std::vector<DotPosition<UINT>>* getLineXVector(UINT uResolution);
public:
	
	std::vector<DotPosition<UINT>>* GetLineXVectorPtr()
	{
		return LineXVector;
	}
	std::vector<DotPosition<int>>* getGrainVector(UINT uResolution);
	
	Chart(double(*)(double), double, double, UINT uiResolution); 
	~Chart();


	
};