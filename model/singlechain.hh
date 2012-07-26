

#ifndef _SINGLE_CHAIN_H
#define _SINGLE_CHAIN_H

#include <model/model.hh>
#include <tools/types.hh>
#include <tools/CR.hh>
#include <vector>

namespace model
{

class SingleChain : public Model
{
public:
	typedef tools::CR CR;

public:
	SingleChain();
	void save_pdb(int);
	void setCenter();
	Real all_energy();
	Real move();
	Real energy();
	void accept();
	void reject();
	void stat();
	void output();

private:
	inline CR normal_move(const CR &r1,const CR &r2,const CR &r3);
	inline CR end_move(const CR &end);

	std::vector<CR> chain;	//chain
	CR oldr;

	int old_ndx_;
	int number_;	//number of atom
	Real epsilon_;
	Real energy_;
	Real last_energy_;
};

}

#endif
