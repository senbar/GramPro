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
	double dBoundryXRight;
	double dBoundryYUp;
	double dBoundryYDown;
	

	double dIntervalA;
	double dIntervalB;

	std::vector<DotPosition<UINT>>* LineXVector;
	std::vector<DotPosition<UINT>>* LineYVector;
	std::vector<DotPosition<UINT>>* GrainVector;

	std::vector<DotPosition<UINT>>* createLineXVector(UINT uResolution);
	std::vector<DotPosition<UINT>>* createLineYVector(UINT uResolution);

	std::vector<DotPosition<UINT>>* createGrainVector(UINT uResolution);


public:
	std::vector<DotPosition<UINT>>* getLineXVectorPtr()
	{return LineXVector;}
	std::vector<DotPosition<UINT>>* getLineYVectorPtr()
	{return LineYVector;}
	std::vector<DotPosition<UINT>>* getGrainVectorPtr()
	{return GrainVector;}
	
	
	Chart(double(*)(double), double, double, UINT uiResolution); 
	~Chart();


	 
};