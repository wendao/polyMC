
#include <iostream>
#include <model/ising.hh>
#include <tools/CArray.hh>
#include <tools/CReader.hh>
#include <tools/ext_math.hh>

using namespace std;
using namespace tools;

static RandomNumber is_RG(2831);

namespace model
{

Ising::Ising() {
	cout << "Ising model initializing ..." << endl;
	
	//init parameters
	CReader par("ising.txt");
	par.getval("nx",nx);
	par.getval("ny",ny);
	
	spin.alloc( nx, ny );
	nbr1.alloc( nx );
	nbr2.alloc( ny );

	int i,j;
	//all 1
	for ( i=0; i<nx; i++ ) {
		for ( j=0; j<ny; j++ ) {
			spin[i][j] = 1;
		}
	}
	//neighbor list
	for (i = 0 ; i < nx ; i++)
    {
        nbr1[i] = i - 1;
        if (i == 0 ) nbr1[i] = nx - 1;
    }
	for (i = 0 ; i < ny ; i++)
    {
        nbr2[i] = i + 1;
        if (i == ny - 1) nbr2[i] = 0;
    }

	energy_ = all_energy();
	last_energy_ = energy_;
}

Ising::~Ising() {
}

Real Ising::all_energy() {
	int ix, iy;
	int fooe;
	fooe = 0;
    for (ix = 0; ix < nx; ix++) {
        for (iy = 0; iy < ny; iy++) {
		    fooe -= spin[ix][iy] * spin[ix][nbr1[iy]] \
		            + spin[ix][iy] * spin[nbr2[ix]][iy];
        }
	}
	return fooe;
}

Real Ising::energy(){return last_energy_;}

Real Ising::move() {
	oldx = int(nx*is_RG.uniform());
	oldy = int(ny*is_RG.uniform());
	spin[oldx][oldy]=-spin[oldx][oldy];
	energy_ += 2*(-spin[oldx][oldy])*( \
		spin[nbr1[oldx]][oldy] \
		+spin[oldx][nbr1[oldy]] \
		+spin[nbr2[oldx]][oldy] \
		+spin[oldx][nbr2[oldy]] );
	return (energy_-last_energy_);
}

void Ising::accept() {last_energy_=energy_;}

void Ising::reject() {
	spin[oldx][oldy]=-spin[oldx][oldy];
	energy_=last_energy_;
}

void Ising::stat()
{
}

void Ising::output()
{
}

}
