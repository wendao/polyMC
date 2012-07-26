#ifndef CANONICAL_SIMPLE_HH
#define CANONICAL_SIMPLE_HH

#include <sampler/sampler.hh>
#include <tools/types.hh>
#include <tools/CAverage.hh>

namespace sampler
{

class Canonical : public Sampler
{
public:
	Canonical():temperature_(0),e_ave(0),e_square_ave(0){}
	void sample(model::Model *);
	void set_temperature(Real t);
	void stat(model::Model *);
	void output();

private:
	Real temperature_;
	tools::CAverage<Real> e_ave;
	tools::CAverage<Real> e_square_ave;
};

}

#endif

