
#include <model/singlechain.hh>
#include <sampler/canonical.hh>
#include <iostream>
#include <cstdlib>

int main(int argc, char *argv[])
{
	model::Model *sc=new model::SingleChain();
	sampler::Canonical can;
	can.set_temperature(std::atof(argv[1]));
	for (int i=1; i<=10000; i++)
	{
		can.sample(sc);
		if (i%100 == 0)
		{
			can.stat(sc);
			std::cout << sc->energy() << std::endl;
		}
	}
	can.output();
	sc->output();

	return 0;
}

