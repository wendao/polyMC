
#include <model/simple.hh>
#include <sampler/simple.hh>
#include <tools/CR.hh>
#include <tools/CAverage.hh>
#include <tools/CArray.hh>
#include <tools/CReader.hh>
#include <model/ising.hh>
#include <iostream>

int main()
{
	//test for sampler and model
	model::Model *mod = new model::Simple();
	sampler::Simple sam;
	//plus CAverage
	tools::CAverage<int> all(0);
	tools::CAverage<int> win(3);
	for (int i=0; i<=20; i++)
	{
		sam.sample(mod);
		all.addData(i);
		win.addData(i);
	}
	std::cout << "all:" << all.getAvg() << " " << all.getSum() << "/" << all.getNum() << std::endl;
	std::cout << "win:" << win.getAvg() << " " << win.getSum() << "/" << win.getNum() << std::endl;

	//test for CArray
	tools::CArray1<int> bin;
	bin.alloc(10);
	for (int i=0; i<10; i++) std::cout << bin[i] << std::endl;

	//test for CReader
	char line[]={"Hello world#haha"};
	tools::mychomp(line);
	std::cout << line << std::endl;

	tools::CReader readp("params.txt");
	int i;
	float f;
	double d;
	char s[100];
	double c0;
	
	readp.getval("I",i);
	readp.getval("F",f);
	readp.getval("D",d);
	readp.getval("S",s);
	readp.getval("c0",c0);

	std::cout << "I=" << i << std::endl;
	std::cout << "F=" << f << std::endl;
	std::cout << "D=" << d << std::endl;
	std::cout << "S=" << s << std::endl;
	std::cout << "c0=" << c0 << std::endl;

	//test for ising model
	model::Ising is;
	for (int i=0; i<10; i++)
	{
		for (int j=0; j<20; j++)
		{
			std::cout << is.move() << " ";
		}
		std::cout << std::endl;
	}


	return 0;
}
