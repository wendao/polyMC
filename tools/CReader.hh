
#ifndef _CREADER_H_
#define _CREADER_H_

namespace tools
{

class CReader
{
private:
	int getn( const char *var );
	int n;

	char **vars;
	char **vals;

public:
	CReader(const char *fn);
	~CReader();

	void getval( const char *var, int &val );
	void getval( const char *var, float &val );
	void getval( const char *var, double &val );
	void getval( const char *var, long &val );
	//void getval( const char *var, long double &val );
	void getval( const char *var, char *val );
};


//clear the blank char
bool mychomp( char *str );

}

#endif
