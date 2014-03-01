
#include <model/link.hh>

namespace model
{

Link::Link():value(0.5){}

Real Link::move()
{
  Real de=(value>0)?-1.0:1.0;
  value += de;
  return de;
}

Real Link::energy(){return value;}
void Link::accept(){return;}
void Link::reject(){return;}
void Link::stat(){return;}
void Link::output(){return;}

}

