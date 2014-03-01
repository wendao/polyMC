

#include <tools/math.hh>

namespace tools
{

RandomNumber::RandomNumber():iseed_(1111){}
RandomNumber::RandomNumber(int seed):iseed_(seed){}

//art
#define IADD   453806245
#define IMUL   314159269
#define MASK   2147483647
#define SCALE  0.4656612873e-9

Real RandomNumber::uniform()
{
  iseed_ = (iseed_ * IMUL + IADD) & MASK;
  return (iseed_ * SCALE);
}
//end art


//this one need negative integer
//add minus to keep all seeds are positive
RandomNumberA::RandomNumberA():iseed_(-1111){}
RandomNumberA::RandomNumberA(int seed):iseed_(-seed){}

//old
#define m 714025
#define ia 1366
#define ic 150889
#define rm (1.0/m)

Real RandomNumberA::uniform()
{
	Real ran;

	if(iseed_<0) {
		iseed_=(ic-iseed_)%m;
		for(int j=1;j<=97; j++) {
			iseed_=(ia*iseed_+ic)%m;
			ir[j]=iseed_;
		}
		iseed_=(ia*iseed_+ic)%m;
		iy=iseed_;
	}

	jj=1+(97*iy)/m;
	iy = ir[jj];
	ran=iy*rm;
	iseed_=(ia*iseed_+ic)%m;
	ir[jj] =iseed_;
	return ran;
}
//end old
}

