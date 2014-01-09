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
	this->jobs = new Job[n]();
	this->K = new int*[m];
	for (int i = 0; i < m; i++)
		this->K[i] = new int[m];
}

Instance::~Instance() {
	delete jobs;
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
		flux << jobs[j].getA() << " ";
	}
	flux << endl;

	flux << "b ";
	for (int j = 0; j < n; j++) {
		flux << jobs[j].getB() << " ";
	}
	flux << endl;

	flux << "d ";
	for (int j = 0; j < n; j++) {
		flux << jobs[j].getD() << " ";
	}
	flux << endl;

	flux << "k ";
	for (int j = 0; j < n; j++) {
		flux << jobs[j].getK() << " ";
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

