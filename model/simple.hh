
#ifndef MODEL_SIMPLE_H
#define MODEL_SIMPLE_H

#include <model/model.hh>

namespace model
{

class Simple : public Model
{
public:
	Simple();
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

