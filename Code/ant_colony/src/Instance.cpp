/*
 * Instance.cpp
 *
 *  Created on: 25 nov. 2013
 *      Author: Thomas
 */

#include "Instance.h"

/*
 * Default initialisation, must be called at the beginning of each constructor.
 */
void Instance::init() {
	n = 0;
	m = 0;
	jobs = NULL;
	K = NULL;
}

Instance::Instance() {
	init();
}

Instance::Instance(int n, int m) {
	init();
	this->n = n;
	this->m = m;
	this->jobs = new Job[n]();
	this->K = new int*[m];
	for (int i = 0; i < m; i++)
		this->K[i] = new int[m];
}

/**
 * Create the instance from a file.
 * @param fileName The path to the file to be used to create the instance.
 */
Instance::Instance(string fileName) {
	init();
	ifstream file;
	string line;
	stringstream ss;
	file.open(fileName.c_str());
	char c;
	int id;
	int a;
	int b;
	int d;
	int k;

	getline(file, line);
	ss.str(line);
	ss >> c;
	ss >> n;

	getline(file, line);
	ss.str(line);
	ss.clear();
	ss >> c;
	ss >> m;

	this->jobs = new Job[n]();
	this->K = new int*[m];
	for (int i = 0; i < m; i++)
		this->K[i] = new int[m];

	getline(file, line);
	do {
		getline(file, line);
		ss.str(line);
		ss.clear();
		ss >> c;
		if (c != 'K') {
			ss.str(line);
			ss.clear();
			ss >> id;
			ss >> a;
			ss >> b;
			ss >> d;
			ss >> k;
			setJob(id, a, b, d, k);
		}
	} while (c != 'K');

	int i = 0;
	int j;
	while (getline(file, line)) {
		ss.str(line);
		ss.clear();
		j = 0;
		while (!ss.eof()) {
			ss >> k;
			setK(i, j, k);
			j++;
		}
		i++;
	}
	file.close();
}

Instance::~Instance() {
	if (jobs != NULL)
		delete jobs;
	if (K != NULL) {
		for (int i = 0; i < m; i++)
			delete[] K[i];
		delete[] K;
	}
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

