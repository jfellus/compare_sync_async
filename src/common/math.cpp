/*
 * math.cpp
 *
 *  Created on: 21 janv. 2014
 *      Author: jfellus
 */

#include "math.h"



float frand() {
	return ((float)rand())/INT_MAX;
}

float frand(float min, float max) {
	return frand()*(max-min)+min;
}

void randvec(float* v, int n, float min, float max) {
	for(int i=0; i<n; i++) {
		v[i] = frand(min,max);
	}
}

void randvec(double* v, int n, double min, double max) {
	for(int i=0; i<n; i++) {
		v[i] = frand(min,max);
	}
}


float rand_gaussian(float mu, float sigma) {
	float x1, x2, w, y1;

	do {
		x1 = 2.0 * frand() - 1.0;
		x2 = 2.0 * frand() - 1.0;
		w = x1 * x1 + x2 * x2;
	} while ( w >= 1.0 );

	w = sqrt( (-2.0 * log( w ) ) / w );
	y1 = x1 * w;
	return (y1*sigma) + mu;
}


float rand_exp(float lambda) {
	float u = frand();
	return -log(u)/lambda;
}




void randvec_gaussian(float* v, int d) {
	for(int i=0; i<d; i++) v[i] = rand_gaussian(0,1);
}


void randvec_gaussian(double* v, int d) {
	for(int i=0; i<d; i++) v[i] = rand_gaussian(0,1);
}
