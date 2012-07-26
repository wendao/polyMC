
#ifndef MODEL_SIMPLE_H
#define MODEL_SIMPLE_H

#include <model/model.hh>

/*
	class Link is a single chain polymer
	represented by internal coordinates
	with diherals as the only degree of
	freedom.

	two parameters for constructor:
	length -- how many beads
	angle -- fixed bond angle
*/

namespace model
{

class Link : public Model
{
public:
	Link();
	Link(int len, Real angle);
	Real move();
	Real energy();
	void accept();
	void reject();
	void stat();
	void output();

private:
	Real value;
};

}

#endif

