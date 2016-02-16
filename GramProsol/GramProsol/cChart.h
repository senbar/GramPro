#pragma once
#include <vector>

#define POSITIVE(n) ((n) < 0 ? 0 - (n) : (n))

class Chart
{
private:

	double (*f_pEquation)(double);

	double dBoundryXLeft;
	double dBoundryXRright;
	double dBoundryYUp;
	double dBoundryYDown;
	

	double dIntervalA;
	double dIntervalB;


public:
	template <typename var>
	struct DotPosition
	{
	public:
		var X;
		var Y;
	};

	std::vector<DotPosition<int>> getGrainVector(UINT uResolution);
	Chart(double(*)(double), double, double); 
	~Chart();


	
};