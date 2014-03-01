
#include <model/simple.hh>

namespace model
{

Simple::Simple():value(0.5){}

Real Simple::move()
{
  Real de=(value>0)?-1.0:1.0;
  value += de;
  return de;
}

Real Simple::energy(){return value;}
void Simple::accept(){return;}
void Simple::reject(){return;}
void Simple::stat(){return;}
void Simple::output(){return;}

}

