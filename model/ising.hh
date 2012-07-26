
#ifndef ISING_HH
#define ISING_HH

#include <model/model.hh>
#include <tools/CArray.hh>

namespace model
{

class Ising : public Model
{
public:
	Real move();
	Real energy();
	void accept();
	void reject();
	void stat();
	void output();

	Ising();
	~Ising();

private:
	Real all_energy();

	tools::CArray2<int> spin;
	tools::CArray1<int> nbr1, nbr2;
	int nx, ny;
	int oldx, oldy;
	Real energy_;
	Real last_energy_;
};

}

#endif

