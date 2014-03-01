
/*
*	This class is used for calculate
*	a set of data's average value
*	2007.06.23
*	2010.04.02
*/

#ifndef _CAVERAGE_H
#define _CAVERAGE_H

#include <cstring>
#include <cstdio>
#include <vector>

#define CAVERAGE_ALL 0

namespace tools
{

template < class T >
class CAverage
{
private:
	T sum;
	int num;
	int pos;
	const int typ; //the size of data window, 0 mean all
	std::vector<T> database;

public:
	CAverage(int type):typ(type)
	{
		if (type>0) database.reserve(type);
		num = 0;
		pos = 0;
		std::memset( &sum, 0, sizeof(T) );
	}

	void addData( T data )
	{
		switch(typ)
		{
		case CAVERAGE_ALL:
			num++;
			sum += data;
			break;
		default:
			if ( num<typ )
			{
				//not full
				num++;
				pos++;
				sum+=data;
				database.push_back(data);
			}
			else
			{
				//full
				pos = (pos+1) % num;
				sum -= database[pos];
				database[pos] = data;
				sum += data;
			}
		}
	}

	T getAvg() { return sum/num; }
	T getSum() { return sum; }
	int getNum() { return num; }
};

}

#endif
