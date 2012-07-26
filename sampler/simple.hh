
#ifndef SAMPLER_SIMPLE_HH
#define SAMPLER_SIMPLE_HH

#include <sampler/sampler.hh>

namespace sampler
{

class Simple : public Sampler
{
public:
	Simple(){}
	void sample(model::Model *);
};

}

#endif

