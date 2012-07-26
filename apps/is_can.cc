#include <model/ising.hh>
#include <sampler/canonical.hh>
#include <iostream>
#include <cstdlib>

int main(int argc, char *argv[])
{
	model::Model *is=new model::Ising();
	sampler::Canonical can;
	if (argc>1)
	{
		can.set_temperature(std::atof(argv[1]));
	}
	else
	{
		can.set_temperature(1.0);
	}
	for (int i=1; i<=1000000; i++)
	{
		can.sample(is);
		if(i>200000 && i%100==0)can.stat(is);
	}
	can.output();

	return 0;
}
