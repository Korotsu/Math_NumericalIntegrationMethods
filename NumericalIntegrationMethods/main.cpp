#include <iostream>
#include <functional>
#include <vector>

using namespace std;

[[nodiscard]] inline float RectangleMethod(const function<float(float)>& func, const float& a, const float& b, const unsigned int& subdivision)
{
    float h			= (b-a)/ subdivision;
	float result	= 0;

	for (unsigned int i = 0; i < subdivision; i++)
	{
		result += func(a+i*h);
	}

	return h * result;
}

[[nodiscard]] inline float MedianRectangleMethod(const function<float(float)>& func, const float& a, const float& b, const unsigned int& subdivision)
{
	float h			= (b - a) / subdivision;
	float result	= 0;
	float xi		= 0;

	for (unsigned int i = 1; i <= subdivision; i++)
	{
		xi = a + (i * h);
		result += func( (xi - h + xi)/2 );
	}

	return h * result;
}

[[nodiscard]] inline float NewtonCotesMethod(const function<float(float)>& func, const float& a, const float& b, const unsigned int& subdivision, unsigned int degree)
{
	if (degree > 6)
	{
		degree = 6;
		cout << "Error : can't get a degree superior to 6 !" << endl;
	}

	float h						= (b - a) / subdivision;
	float hi					= h / degree;
	float result				= 0;
	float xi					= 0;
	float xij					= 0; 
	vector<vector<float>> table = { {1.f  / 2.f,   1.f   / 2.f},
									{1.f  / 6.f,   4.f   / 6.f,  1.f  / 6.f},
									{1.f  / 8.f,   3.f   / 8.f,  3.f  / 8.f,   1.f   / 8.f},
									{7.f  / 90.f,  32.f  / 90.f, 12.f / 90.f,  32.f  / 90.f,  7.f  / 90.f},
									{19.f / 288.f, 75.f  / 288,  50.f / 288.f, 50.f  / 288.f, 75.f / 288.f, 19.f  / 288.f},
									{41.f / 840.f, 216.f / 840,  27.f / 840.f, 272.f / 840.f, 27.f / 840.f, 216.f / 840.f, 41.f / 840.f}};

	for (unsigned int i = 0; i < subdivision; i++)
	{
		xi = a + i * h;

		for (unsigned int j = 0; j <= degree; j++)
		{
			xij		= xi + j * hi;
			result	+= table[degree-1][j] * func(xij);
		}
	}

	return h * result;
}

[[nodiscard]] inline float TrapezeMethod(const function<float(float)>& func, const float& a, const float& b, const unsigned int& subdivision)
{
	return NewtonCotesMethod(func, a, b, subdivision, 1);
}

[[nodiscard]] inline float SimpsonMethod(const function<float(float)>& func, const float& a, const float& b, const unsigned int& subdivision)
{
	return NewtonCotesMethod(func, a, b, subdivision, 2);
}

[[nodiscard]] inline float NewtonMethod(const function<float(float)>& func, const float& a, const float& b, const unsigned int& subdivision)
{
	return NewtonCotesMethod(func, a, b, subdivision, 3);
}

[[nodiscard]] inline float BooleMethod(const function<float(float)>& func, const float& a, const float& b, const unsigned int& subdivision)
{
	return NewtonCotesMethod(func, a, b, subdivision, 4);
}

[[nodiscard]] inline float BooleVillarceauMethod(const function<float(float)>& func, const float& a, const float& b, const unsigned int& subdivision)
{
	return NewtonCotesMethod(func, a, b, subdivision, 5);
}

[[nodiscard]] inline float WeddleHardyMethod(const function<float(float)>& func, const float& a, const float& b, const unsigned int& subdivision)
{
	return NewtonCotesMethod(func, a, b, subdivision, 6);
}

int main()
{
	unsigned int	subdivision = 2;
	float			from		= -1;
	float			to			= 2;

	cout << "This benchmark is for the function 2x^2+3, from " << from << " to " << to << ", with a subdivision of " << subdivision << " : " << '\n' << endl;

	cout << "RectangleMethod 	    = " << RectangleMethod(			[](float x) { return (2 * x * x) + 3; }, from, to, subdivision) << ";" << endl;
	cout << "MedianRectangleMethod  = "	<< MedianRectangleMethod(	[](float x) { return (2 * x * x) + 3; }, from, to, subdivision) << ";" << endl;
	cout << "TrapezeMethod          = "	<< TrapezeMethod(			[](float x) { return (2 * x * x) + 3; }, from, to, subdivision) << ";" << endl;
	cout << "SimpsonMethod          = "	<< SimpsonMethod(			[](float x) { return (2 * x * x) + 3; }, from, to, subdivision) << ";" << endl;
	cout << "NewtonMethod           = "	<< NewtonMethod(			[](float x) { return (2 * x * x) + 3; }, from, to, subdivision) << ";" << endl;
	cout << "BooleMethod            = "	<< BooleMethod(				[](float x) { return (2 * x * x) + 3; }, from, to, subdivision) << ";" << endl;
	cout << "BooleVillarceauMethod  = "	<< BooleVillarceauMethod(	[](float x) { return (2 * x * x) + 3; }, from, to, subdivision) << ";" << endl;
	cout << "WeddleHardyMethod      = "	<< WeddleHardyMethod(		[](float x) { return (2 * x * x) + 3; }, from, to, subdivision) << ";" << endl;

	return 0;
}