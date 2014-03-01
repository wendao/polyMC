/*i forgot where this piece of code came from*/

#ifndef _CARRAY_H
#define _CARRAY_H

#include <cstdio>
#include <string>

namespace tools
{

enum Ctype { internal, external };

template <class T>
class CArray1 {
public:
	CArray1() :p(NULL),n(0),t(external) {
		//do nothing
	}

    CArray1( int nelem ) :CArray1() {
		alloc(nelem);
    }

    CArray1( CArray1& array ) :CArray1() {
        alloc(array.n);
        memcpy( p, array.p, n*sizeof(T) );
    }

    CArray1( T* space, int nelem ) :CArray1() {
        p = space;
        n = nelem;
        t = external;
    }

    ~CArray1() {
        recyc();
    }

	void recyc() {
		if (p!=NULL) {
			if (internal==t) {
				delete [] p;
			}
			p = NULL;
		}
	}

	void alloc( int nelem ) {
		recyc();
		p = new T[nelem];
		n = nelem;
		t = internal;
	}

    T& operator[] (int ndx) {
        return *(p+ndx);
    }

    CArray1& operator= ( CArray1& array ) {
        if (n==array.n) {
            memcpy( p, array.p, n*sizeof(T) );
        }
        return *this;
    }

private:
    T* p;
    int n;
    Ctype t;
};

template < class T >
class CArray2 {
private:
    T** p;
    int nx,ny;
    Ctype t;

public:
	void recyc() {
		if (p!=NULL) {
			if (internal==t) {
				delete [] p[0];
				delete [] p;
			}
			p = NULL;
		}
	}

	void alloc( int x, int y ) {
		recyc();
        p = new T*[x];
        p[0] = new T[x*y];
        int i;
        for ( i=1; i<x; i++ ) {
            p[i] = p[0] + i*y;
        }
        nx = x;
        ny = y;
        t = internal;
	}

	CArray2() :p(NULL),nx(0),ny(0),t(external){}

    CArray2( int x, int y ) :CArray2() {
		alloc(x,y);
    }

    CArray2( T** space, int x, int y ) :CArray2() {
        p = space;
        nx = x;
        ny = y;
        t = external;
    }

    CArray2( CArray2& array ) :CArray2() {
		alloc(array.nx,array.ny);
        memcpy( p[0], array.p[0], nx*ny*sizeof(T) );
    }

    CArray2& operator=( CArray2& array ) {
        if (nx*ny==array.nx*array.ny) {
            memcpy( p[0], array.p[0], nx*ny*sizeof(T) );
        }
        return *this;
    }

    T * const & operator[] (int ndx) {
        return *(p+ndx);
    }

    ~CArray2() {
		recyc();
    }
};

template < class T >
class CArray3 {
private:
    int nx,ny,nz;
    T *** p;
    Ctype t;

public:
	void recyc() {
		if (p!=NULL) {
			if (internal==t) {
				delete [] p[0][0];
				delete [] p[0];
				delete [] p;
			}
			p = NULL;
		}
	}
	void alloc( int x, int y, int z ) {
		recyc();
        p = new T**[x];
        p[0] = new T*[x*y];
        int i,j;
        for (i=1;i<x;i++) {
            p[i] = p[0] + i*y;
        }
        p[0][0] = new T[x*y*z];
        for (i=0;i<x;i++) {
            for	(j=0;j<y;j++) {
                p[i][j] = p[0][0] + i*y*z + j*z;
            }
        }
        nx = x;
        ny = y;
        nz = z;
        t = internal;
	}

	CArray3() :p(NULL),nx(0),ny(0),nz(0),t(external){}

    CArray3( int x, int y, int z ) :p(NULL) {
		alloc(x,y,z);
    }

    ~CArray3() {
		recyc();
    }

	CArray3( T*** space, int x, int y, int z ) :p(NULL) {
        p = space;
        nx = x;
        ny = y;
		nz = z;
        t = external;
    }

	CArray3( CArray3& array ) :p(NULL) {
		alloc(array.nx,array.ny,array.nz);
		memcpy( p[0][0], array.p[0][0], nx*ny*nz*sizeof(T) );
	}

	CArray3& operator=( CArray3& array ) {
        if (nx*ny*nz==array.nx*array.ny*array.nz) {
            memcpy( p[0][0], array.p[0][0], nx*ny*nz*sizeof(T) );
        }
        return *this;
    }

    T ** const & operator[] (int ndx) {
        return *(p+ndx);
    }
};

}

#endif
