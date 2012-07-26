
#ifndef SAMPLER_H
#define SAMPLER_H

#include <model/model.hh>

namespace sampler
{

class Sampler
{
public:
	Sampler();
	virtual ~Sampler();
	virtual void sample(model::Model *)=0;
};

}

#endif
