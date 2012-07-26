#include <sampler/simple.hh>
#include <iostream>

namespace sampler
{

void Simple::sample(model::Model *mod)
{
	mod->move();
	std::cout << mod->energy() << std::endl;
}

}
