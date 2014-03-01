/*
*	This file define some function
*	that extend the math lib
*	for easy using 
*	By Liu Yuan
*	2007.4.12
*	2010.4.3
*/

#ifndef _EXT_MATH_H
#define _EXT_MATH_H

#include <tools/types.hh>
#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265
#endif
#ifndef FLT_MAX
#define FLT_MAX 1E+36
#endif

namespace tools
{
//no matter how to get uniform rand
//gaussian rand comes the same way

class RandomNumberCore
{
public:
	RandomNumberCore():gaussian_iset(true),gaussian_gset(0){}
	virtual Real uniform()=0;
	Real gaussian()
	{
		double v1, v2, rsq, fac;
		double rgaussian; // Return value

		if ( gaussian_iset )
		{
			do {
			v1 = 2.0f * uniform() - 1.0f;
			v2 = 2.0f * uniform() - 1.0f;
			rsq = ( v1 * v1 ) + ( v2 * v2 );
			} while ( rsq >= 1.0 || rsq == 0.0 );
			fac = std::sqrt(-(2.0*std::log(rsq)/rsq));
			gaussian_gset = v1*fac;
			rgaussian = v2*fac;
			gaussian_iset = false;
		}
		else
		{
			rgaussian = gaussian_gset;
			gaussian_iset = true;
		}

		return rgaussian;
	}
private:
	bool gaussian_iset;
	Real gaussian_gset;
};

class RandomNumber : public RandomNumberCore
{
public:
	RandomNumber();
	RandomNumber(int seed);
	Real uniform();

private:
	int iseed_;

//////////////////////////////////////////////////////////////////////////
//copied from the source code of "The Art of Molecular Dynamics Simulation - 2nd edn"
//////////////////////////////////////////////////////////////////////////
};

class RandomNumberA : public RandomNumberCore
{
public:
	RandomNumberA();
	RandomNumberA(int seed);
	Real uniform();

private:
	int ir[98];
	int iy;
	int jj;
	int iseed_;
//////////////////////////////////////////////////////////////////////////
// from SCFT
//////////////////////////////////////////////////////////////////////////
};

}

#endif
