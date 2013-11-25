/*
 * Instance.cpp
 *
 *  Created on: 25 nov. 2013
 *      Author: Thomas
 */

#include "Instance.h"

Instance::Instance(int n, int m) {
	this->n = n;
	this->m = m;
	this->a = new int[n];
	this->b = new int[n];
	this->d = new int[n];
	this->k = new int[n];
	this->K = new int*[m];
	for (int i = 0; i < m; i++)
		this->K[i] = new int[m];
}

Instance::~Instance() {
	delete a;
	delete b;
	delete d;
	for (int i = 0; i < m; i++)
		delete[] K[i];
	delete[] K;
}

void Instance::print(ostream &flux) const {
	flux << "n = " << n << endl;
	flux << "m = " << m << endl;

	flux << "j ";
	for (int j = 0; j < n; j++) {
		flux << j << " ";
	}
	flux << endl;

	flux << "a ";
	for (int j = 0; j < n; j++) {
		flux << a[j] << " ";
	}
	flux << endl;

	flux << "b ";
	for (int j = 0; j < n; j++) {
		flux << b[j] << " ";
	}
	flux << endl;

	flux << "d ";
	for (int j = 0; j < n; j++) {
		flux << d[j] << " ";
	}
	flux << endl;

	flux << "k ";
	for (int j = 0; j < n; j++) {
		flux << k[j] << " ";
	}
	flux << endl;

	flux << "K" << endl;
	for (int i = 0; i < m; i++) {
		flux << "   ";
		for (int j = 0; j < m; j++) {
			flux << K[i][j] << " ";
		}
		flux << endl;
	}
	flux << endl;
}

ostream& operator<<(ostream &flux, const Instance& instance) {
	instance.print(flux);
	return flux;
}

