/*
 * utils.h
 *
 *  Created on: 8 nov. 2013
 *      Author: jfellus
 */

#ifndef UTILS_H_
#define UTILS_H_

#include <iostream>
#include <string>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <string.h>
#include <string>
#include <libgen.h>
#include <sstream>


#define MAX(a,b) (((a) > (b)) ? (a) : (b))
using namespace std;

#define DBG_START(x) \
	do {CRITICAL_BEGIN(); \
	std::cout << x << " ... "; fflush(::stdout); \
	CRITICAL_END();} while(0);

#define DBG_END() \
	do {CRITICAL_BEGIN(); \
	std::cout << "ok\n"; fflush(::stdout); \
	CRITICAL_END();} while(0);


#define DBG(x) \
	do {CRITICAL_BEGIN(); \
	std::cout << x << "\n"; fflush(::stdout); \
	CRITICAL_END();}while(0);

void DBGVECTOR(float* x, int D);

#define DBGV(x) \
	std::cout << "" #x " : " << x << "\n"; fflush(::stdout);

#define DBGN(x) \
		do { \
			std::cout << x << "\n"; fflush(stdout); \
			std::cout  << "\033[1F\033[2K"; \
		}while(0);

#define DBG_PERCENT(x) DBGN((int)((float)x*1000)/10.0f << "%")

string stringprintf(const char* fmt, ...);
#define fmt(x...) stringprintf(x).c_str()

void fappend(const string& filename, const string& line);
void foverwrite(const string& filename, const string& line);

#define FATAL(x) do { DBG(x); exit(1); } while(0);



template <class T> T get_config(const char* what, T default_val) {
	FILE* f = fopen("config.properties", "r");
	char line[512];
	char* c = 0;
	T v = default_val;
	while ( fgets (line , 512 , f) != NULL ) {
	      if(!strncmp(what, line, strlen(what))) {
	    	  c = line + strlen(what);
	    	  while(*c==' ' || *c=='=') c++;
	    	  v = (T) atof(c);
	      }
	}
	fclose(f);
	return v;
}


#define ZZZZ(x) DBG(#x); x

string get_config_str(const char* what, const char* default_val);


void setenv(const char* name, int val);
void setenv(const char* name, double val);

inline void shell(const string& s, bool berrors = true) {if(system(s.c_str()) && berrors) throw "error";}

inline double TODOUBLE(const std::string& s) {
	std::istringstream iss(s);
	double i;
	iss >> i;
	return i;
}


#endif /* UTILS_H_ */
