
#include <tools/CReader.hh>

#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <iostream>

#define MAX_LINE 600
#define MAX_VAR_LEN 20
#define MAX_VAL_LEN 40

using namespace std;

namespace tools
{

CReader::CReader(const char *fn)
{
	FILE *fp;
	if((fp=fopen(fn,"r")) == NULL)
	{
		printf("Parameter file open error!\n");
		exit(0);
	}
	char temp[MAX_LINE][MAX_LINE];
	int i,num=0;
	n=0;
	while (!feof(fp))fgets(temp[num++],MAX_LINE,fp);
	for (i=0;i<num;i++)
	{
		if ( strlen(temp[i])<=0 || strlen(temp[i])>MAX_LINE ) continue;
		mychomp(temp[i]);
		if ( strchr(temp[i],'=')!=NULL && temp[i][0]!='#' )
		{
			n++;
		}
	}
	vars = new char*[n];
	vals = new char*[n];
	for (i=0;i<n;i++)
	{
		vars[i] = new char[MAX_VAR_LEN];
		vals[i] = new char[MAX_VAL_LEN];
	}
	int ndx=0;
	for (i=0;i<num;i++)
	{
		if ( strlen(temp[i])<=0 || strlen(temp[i])>MAX_LINE ) continue;
		if ( strchr(temp[i],'=')!=NULL && temp[i][0]!='#' )
		{
			sscanf(temp[i],"%[^=]%[^$]",vars[ndx],vals[ndx]);
			mychomp(vars[ndx]);
			mychomp(vals[ndx]);
			ndx++;
		}
	}
	if (ndx!=n)
	{
		printf("Parse error!\n");
		exit(0);
	}
}

CReader::~CReader()
{
	int i;
	if (vars!=NULL)
	{
		for (i=0;i<n;i++)
			if(vars[i]!=NULL)delete [] vars[i];
		delete [] vars;
	}
	if (vals!=NULL)
	{
		for (i=0;i<n;i++)
			if(vals[i]!=NULL)delete [] vals[i];
		delete [] vals;
	}
}

int CReader::getn( const char *var )
{
	int i=0;
	for (i=0;i<n;i++)
		if (strcmp(var,vars[i])==0)
			break;
	return i;
}
void CReader::getval( const char *var, int &val )
{
	int ndx=getn(var);
	if (ndx<n)
	{
		sscanf(vals[ndx],"%d",&val);
	}
	else
	{
		printf("Can't find the varible's name!\n");
		exit(0);
	}
}
void CReader::getval( const char *var, float &val )
{
	int ndx=getn(var);
	if (ndx<n)
		sscanf(vals[ndx],"%f",&val);
	else
	{
		printf("Can't find the varible's name!\n");
		exit(0);
	}
}
void CReader::getval( const char *var, double &val )
{
	int ndx=getn(var);
	if (ndx<n)
		sscanf(vals[ndx],"%lf",&val);
	else
	{
		printf("Can't find the varible's name!\n");
		exit(0);
	}
}
void CReader::getval( const char *var, long &val )
{
	int ndx=getn(var);
	if (ndx<n)
		sscanf(vals[ndx],"%ld",&val);
	else
	{
		printf("Can't find the varible's name!\n");
		exit(0);
	}
}
/*
void CReader::getval( const char *var, long double &val )
{
	int ndx=getn(var);
	if (ndx<n)
		sscanf(vals[ndx],"%L",&val);
	else
	{
		printf("Can't find the varible's name!\n");
		exit(0);
	}
}*/
void CReader::getval( const char *var, char *val )
{
	int ndx=getn(var);
	if (ndx<n)
		sscanf(vals[ndx],"%s",val);
	else
	{
		printf("Can't find the varible's name!\n");
		exit(0);
	}
}

bool mychomp( char *str )
{
	char temp[MAX_LINE];
	int len = strlen(str);
	int i;
	int ndx = 0;
	for (i=0;i<len;i++)
	{
		if( str[i]!=' ' && str[i]!='\t' && str[i]!='\n' && str[i]!='=')break;
	}
	if (i>=len)
	{
		return false;
	}
	strcpy(temp,str+i);
	len = strlen(temp);
	for (i=len-1;i>0;i--)
	{
		if( temp[i]!=' ' && temp[i]!='\t' && temp[i]!='\n' && temp[i]!='=')break;
	}
	temp[i+1] = '\0';
	strcpy(str,temp);
	return true;
}

}

