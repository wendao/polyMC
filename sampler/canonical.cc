#include <sampler/canonical.hh>
#include <tools/ext_math.hh>
#include <iostream>
#include <cmath>
#include <algorithm>

tools::RandomNumber RG(1949);

namespace sampler
{

void Canonical::sample(model::Model *mod)
{
	Real de=mod->move();
	Real prob=0;
	if (de<0) prob = 1.0;
	else prob = std::exp( std::max(Real(-40.0),-de/temperature_) );
	
	if (RG.uniform()<prob)
	{
		//accept
		mod->accept();
	}
	else
	{
		//reject
		mod->reject();
	}
}

void Canonical::set_temperature(Real t){temperature_=t;}

void Canonical::stat(model::Model *mod)
{
	Real e=mod->energy();
	e_ave.addData(e);
	e_square_ave.addData(e*e);
}

void Canonical::output()
{
	Real cv = e_square_ave.getAvg() - e_ave.getAvg()*e_ave.getAvg();
	cv /= temperature_;
	std::cout << "Cv(" << temperature_ << ") = " << cv << std::endl;
}

}
