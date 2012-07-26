
#include <tools/ext_math.hh>
#include <iostream>
#include <fstream>
using namespace std;
int main()
{
	//test for art
	tools::RandomNumber artOne(13579);
	tools::RandomNumber artTwo(24680);
	ofstream fp("art.uni");
	ofstream fp2("art.gau");
	for (int i=0; i<100000; i++)
	{
		fp << artOne.uniform() << " " << artTwo.uniform() << endl;
		fp2 << artOne.gaussian() << " " << artTwo.gaussian() << endl;
	}

	//test for old
	tools::RandomNumberA oldOne(13579);
	tools::RandomNumberA oldTwo(24680);
	ofstream fp3("old.uni");
	ofstream fp4("old.gau");
	for (int i=0; i<100000; i++)
	{
		fp3 << oldOne.uniform() << " " << oldTwo.uniform() << endl;
		fp4 << oldOne.gaussian() << " " << oldTwo.gaussian() << endl;
	}
	return 0;
}
