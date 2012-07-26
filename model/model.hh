
#ifndef MODEL_H
#define MODEL_H

#include <tools/types.hh>
namespace model
{

class Model
{
public:
	Model();
	virtual ~Model();
	virtual Real move()=0;
	virtual Real energy()=0;
	virtual void accept()=0;
	virtual void reject()=0;
	virtual void stat()=0;
	virtual void output()=0;
};

}

#endif
