/*
*	Class for a vector
*	From NAMD mindy
*	2007.4.3
*	2010.4.2
*/

#ifndef CR_HH
#define CR_HH

#include <iostream>
#include <cmath>
#include <cstdio>
#include <tools/types.hh>

namespace tools
{

class CR {
   public:
     Real x,y,z;
     
     CR(void) {         // default is to create a 0 CR
       x = y = z = 0.0;
     }
     CR( const CR &v2) { // CR x = another_CR
       x = v2.x;
       y = v2.y;
       z = v2.z;
     }
     CR( Real newx, Real newy, Real newz) {
       x = newx;
       y = newy;
       z = newz;
     }
     ~CR( void) { }

     //  v1 = v2;
     CR& operator=(const CR &v2) {
       x = v2.x;
       y = v2.y;
       z = v2.z;
       return *this;
     }

     //  v1 = const;
     CR& operator=(const Real &v2) {
       x = v2;
       y = v2;
       z = v2;
       return *this;
     }

     //  v1 += v2;
     void operator+=(const CR &v2) {
       x += v2.x;
       y += v2.y;
       z += v2.z;
     }

     // v1 -= v2;
     void operator-=(const CR &v2) {
       x -= v2.x;
       y -= v2.y;
       z -= v2.z;
     }

     // v1 *= const
     void operator*=(const Real &v2) {
       x *= v2;
       y *= v2;
       z *= v2;
     }

     // v1 /= const
     void operator/=(const Real& v2) {
       x /= v2;
       y /= v2;
       z /= v2;
     }

     friend int operator == (const CR& v1, const CR& v2) {
       return v1.x == v2.x && v1.y == v2.y && v1.z == v2.z;
     }
     friend int operator != (const CR& v1, const CR& v2) {
       return v1.x != v2.x || v1.y != v2.y || v1.z != v2.z;
     }

     // addition of two CRs
     friend CR operator+(const CR& v1, const CR& v2) {
       return CR( v1.x+v2.x, v1.y+v2.y, v1.z+v2.z);
     }

     // negation
     friend CR operator-(const CR &v1) {
       return CR( -v1.x, -v1.y, -v1.z);
     }

     // subtraction
     friend CR operator-(const CR &v1, const CR &v2) {
       return CR( v1.x-v2.x, v1.y-v2.y, v1.z-v2.z);
     }
     // inner ("dot") product
     friend Real operator*(const CR &v1, const CR &v2) {
       return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
     }
     // scalar product
     friend CR operator*(const Real &f, const CR &v1) {
       return CR(f*v1.x, f*v1.y, f*v1.z);
     }
     // scalar product
     friend CR operator*(const CR &v1, const Real &f) {
       return CR(f*v1.x, f*v1.y, f*v1.z);
     }
     // division by a scalar
     friend CR operator/(const CR &v1, const Real &f) {
       return CR(v1.x/f, v1.y/f, v1.z/f);
     }
     
     // return the norm
     inline Real length(void) const {
       return std::sqrt(x*x+y*y+z*z);
     }
     
     Real length2(void) const {
       return (x*x + y*y + z*z);
     }

     // return the unit CR in the same direction
     CR unit(void) const {
       return CR(x, y, z)/length();
     }
     
     // print out
     friend std::ostream& operator<<(std::ostream& strm, const CR &v1) {
       strm << "( "<< v1.x << ", " << v1.y << ", " << v1.z << ')';
       return strm;
     }

     // one cross product  self = cross(v1, v2)
     void cross(const CR &v1, const CR &v2) {
       x= v1.y*v2.z-v2.y*v1.z;
       y= v2.x*v1.z-v1.x*v2.z;
       z= v1.x*v2.y-v2.x*v1.y;
     }

     // multiplying a cross product by a scalar is very common
     // one cross product  v3 = k*cross(v1, v2)
     inline friend CR cross(const Real k, const CR &v1, const CR &v2) {
       return CR( k*(v1.y*v2.z-v2.y*v1.z),
                      // k*(-v1.x*v2.z+v2.x*v1.z),
                      k*(v2.x*v1.z-v1.x*v2.z),
                      k*(v1.x*v2.y-v2.x*v1.y) );
     }

     // add a CR to this CR
     void add(const CR &v1) {
       x+=v1.x; y+=v1.y; z+=v1.z;
     }

     // subtract the CR from this one
     void sub(const CR &v1) {
       x-=v1.x; y-=v1.y; z-=v1.z;
     }

     // add a constant factor to each element of a CR
     void add_const(Real c)
     {
		x+=c;
		y+=c;
		z+=c;
     }

     // rescale everything by a scalar -- V = a*V
     void mult(Real f) {
       x*=f; y*=f; z*=f;
     }

     // divide each element by a scalar
     void div(Real f) {
       x/=f; y/=f; z/=f;
     }

     // returns (*this) * V2
     Real dot(const CR &v2) {
       return x*v2.x + y*v2.y + z*v2.z;
     }

     // set the CR based on a string.  If bad, return 0
     // the string can be in the form "x y z" or "x, y, z"
     int set(const char *s) {
	Real a[3];    // read into Reals, since I don't know what
	char tmp[100];  // a "Real" is in real life
	// cheap way to get commas, etc.  a poor regex

#ifndef DOUBLE_
       int i=std::sscanf(s, "%f%99[ \t,]%f%99[ \t,]%f%99s",
                    a, tmp, a+1, tmp, a+2, tmp);
#else
       int i=std::sscanf(s, "%lf%99[ \t,]%lf%99[ \t,]%lf%99s",
                    a, tmp, a+1, tmp, a+2, tmp);
	   
#endif
       if (i != 5) return 0;
       const char *t = s;       // now count commas (for "1,,,,2,  , 3")
       int flg = 0;                 // and check for "1 2,,3"
       i = 0;
       for (;*t;t++) {
          if (*t == ',') { 
             if (flg == 0) {   // expecting non-whitespace
                return 0;  //    so error
             }
             flg = 0;          // now expect non-whitespace
             i++;              // and increment comma counter
          }
          else if (*t != ' ' && *t != '\t') {  // got non-whitespace
             flg = 1;          // so the next can be whitespace or commas
          }
       }
       if (i == 0 || i == 2) {  // allow "1 2 3" or "1, 2,3" forms
          x = a[0]; y = a[1]; z = a[2];
          return 1;
       }
       return 0;
     }
};

}

#endif

