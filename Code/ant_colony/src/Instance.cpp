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
	file.open(fileName.c_str());
	char c;
	string s;
	int j[MAX_JOBS];
	int i_j = 0;
	int a[MAX_JOBS];
	int i_a = 0;
	int b[MAX_JOBS];
	int i_b = 0;
	int d[MAX_JOBS];
	int i_d = 0;
	int k[MAX_JOBS];
	int i_k = 0;
	int K[MAX_JOBS][MAX_JOBS];
	int i_K = 0;
	int j_K = 0;

	while (getline(file, line)) {
		stringstream ss(line);
		ss >> c;

		switch (c) {
		case 'n':
			ss >> n;
			break;
		case 'm':
			ss >> m;
			break;
		case 'j':
			while (!ss.eof()) {
				ss >> j[i_j];
				i_j++;
			}
			break;
		case 'a':
			while (!ss.eof()) {
				ss >> a[i_a];
				i_a++;
			}
			break;
		case 'b':
			while (!ss.eof()) {
				ss >> b[i_b];
				i_b++;
			}
			break;
		case 'd':
			while (!ss.eof()) {
				ss >> d[i_d];
				i_d++;
			}
			break;
		case 'k':
			while (!ss.eof()) {
				ss >> k[i_k];
				i_k++;
			}
			break;
		case 'K':
			while (getline(file, line)) {
				stringstream sss(line);
				j_K = 0;
				while (!sss.eof()) {
					sss >> K[i_K][j_K];
					j_K++;
				}
				i_K++;
			}
			break;
		default:
			break;
		}
	}
	file.close();

	this->jobs = new Job[n]();
	this->K = new int*[m];
	for (int i = 0; i < m; i++)
		this->K[i] = new int[m];
	for(int i = 0; i < n; i++) {
		setJob(j[i],a[i],b[i],d[i],k[i]);
	}
	for (int i = 0; i < m; i ++) {
		for (int j = 0; j < m; j ++) {
			setK(i,j,K[i][j]);
		}
	}

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

