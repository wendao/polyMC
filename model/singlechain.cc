
#include <tools/CReader.hh>
#include <model/singlechain.hh>
#include <tools/ext_math.hh>
#include <cstdio>
#include <cmath>

#define LBOND 1.01
#define LBOND22 (4.0*LBOND*LBOND)
#define RBALL 1.00
#define MIN_D2 1E-6

tools::RandomNumber sc_RG(1950);

using namespace tools;
namespace model
{

SingleChain::SingleChain()
{
	CReader par("chain.txt");
	par.getval("number", number_);
	par.getval("epsilon", epsilon_);
	chain.resize(number_);

	//put around y-axe in x-y plane
	Real dy=LBOND*std::sqrt(3.0);
	Real dx=LBOND/2.0;
	chain[0].x=chain[0].y=chain[0].z=0.0;
	chain[1].x=dx;
	chain[1].y=dy/2.0;
	chain[1].z=0.0;
	for (int i=2;i<number_;i++)
	{
		chain[i].x = chain[i-2].x;
		chain[i].y = chain[i-2].y+dy;
		chain[i].z = chain[i-2].z;
	}
	all_energy();
}

void SingleChain::save_pdb(int ndx)
{
	int i;
	char fn[100];
	std::sprintf(fn,"conf_%04d.pdb",ndx);
	FILE *fp=std::fopen(fn,"w");
	std::fprintf(fp,"TITLE energy: %f\n",energy_);
	for (i=0;i<number_;i++)
	{
		std::fprintf(fp,"ATOM  %-5d %-4s %-3s  %-4d    %8.3f%8.3f%8.3f\n",\
			i+1,"B","HOM",i+1,chain[i].x,chain[i].y,chain[i].z);
	}
	for (i=1;i<number_;i++)
	{
		std::fprintf(fp,"CONECT%5d%5d\n",i,i+1);
	}
	std::fclose(fp);
}

void SingleChain::setCenter()
{
	Real x0,y0,z0;
	int i;
	x0=y0=z0=0.0;
	for (i=0;i<number_;i++)
	{
		x0 += chain[i].x;
		y0 += chain[i].y;
		z0 += chain[i].z;
	}
	x0 /= number_;
	y0 /= number_;
	z0 /= number_;
	for (i=0;i<number_;i++)
	{
		chain[i].x -= x0;
		chain[i].y -= y0;
		chain[i].z -= z0;
	}
}

Real SingleChain::all_energy()
{
	int i, j;
	energy_=0.0;
	Real d2, d6;
	CR d;
	for (i=0;i<number_-1;i++)
	{
		for (j=i+1;j<number_;j++)
		{
			d = (chain[i]-chain[j]);
			d2 = d.length2();
			if (d2<MIN_D2) energy_+=FLT_MAX;
			else
			{
				d6 = d2*d2*d2;
				energy_ += 4.0*epsilon_*(-1.0/d6+1.0/d6/d6);
			}
		}
	}
	last_energy_=energy_;
	return energy_;
}

Real SingleChain::move()
{
	Real de=0.0;
	CR d;
	Real d2, d6;
	int i;

	old_ndx_ = int(sc_RG.uniform()*number_);
	
	//cal old energy
	for (i=0;i<old_ndx_;i++)
	{
		d = chain[i]-chain[old_ndx_];
		d2 = d.length2();
		if (d2<MIN_D2) de -=FLT_MAX;
		else
		{
			d6 = d2*d2*d2;
			de -= 4.0*epsilon_*(-1.0/d6+1.0/d6/d6);
		}
	}
	for (i=old_ndx_+1; i<number_; i++)
	{
		d = chain[i]-chain[old_ndx_];
		d2 = d.length2();
		if (d2<MIN_D2) de -=FLT_MAX;
		else
		{
			d6 = d2*d2*d2;
			de -= 4.0*epsilon_*(-1.0/d6+1.0/d6/d6);
		}
	}

	//save
	oldr = chain[old_ndx_]; 
	//move
	if (old_ndx_==0)
	{
		chain[0] = end_move(chain[1]);
	}
	else if(old_ndx_==number_-1)
	{
		chain[number_-1] = end_move(chain[number_-2]);
	}
	else
	{
		chain[old_ndx_] = normal_move(chain[old_ndx_-1],chain[old_ndx_],chain[old_ndx_+1]);
	}

	//cal new energy
	for (i=0;i<old_ndx_;i++)
	{
		d = chain[i]-chain[old_ndx_];
		d2 = d.length2();
		if (d2<MIN_D2) de += FLT_MAX;
		else
		{
			d6 = d2*d2*d2;
			de += 4.0*epsilon_*(-1.0/d6+1.0/d6/d6);
		}
	}
	for (i=old_ndx_+1;i<number_;i++)
	{
		d = chain[i]-chain[old_ndx_];
		d2 = d.length2();
		if (d2<MIN_D2) de += FLT_MAX;
		else
		{
			d6 = d2*d2*d2;
			de += 4.0*epsilon_*(-1.0/d6+1.0/d6/d6);
		}
	}
	
	energy_+=de;
	return de;
}

CR SingleChain::normal_move(const CR &r1,const CR &r2,const CR &r3)
{
	CR d=r3-r1;
	if (d.length2()<MIN_D2) return end_move(r1);
	if (d.length2()>=LBOND22) return r2;
	CR o=(r3+r1)/2.0;
	CR old=r2-o;
	
	Real phi = 2.0*M_PI*sc_RG.uniform();
	Real sine=std::sin(phi);
	Real cosine=std::cos(phi);
	return (o + old*cosine - cross(1.0/d.length(),d,old)*sine);
}

CR SingleChain::end_move(const CR &end)
{
	Real phi, theta, x;
	x = sc_RG.uniform();
	theta = asin(x);
	phi = 2.0*M_PI*sc_RG.uniform();
	CR n;
	n.x = LBOND*cos(theta)*cos(phi);
	n.y = LBOND*cos(theta)*sin(phi);
	n.z = LBOND*sin(theta);
	return n+end;
}

void SingleChain::accept()
{
	last_energy_ = energy_;
}

void SingleChain::reject()
{
	chain[old_ndx_] = oldr;
	energy_ = last_energy_;
}

void SingleChain::output()
{
	save_pdb(0);
}

Real SingleChain::energy()
{
	return energy_;
}

void SingleChain::stat()
{
}

}
