/*
 * Instance.h
 *  Created on: 25 nov. 2013
 *      Author: Thomas
 */

#ifndef INSTANCE_H_
#define INSTANCE_H_

#include <iostream>
using namespace std;

/**
 * This class contains the data of an instance for our mixed scheduling problem.
 */
class Instance {
private:
	/** The number of jobs */
	int n;
	/** The processing times for M1 */
	int *a;
	/** The processing times for M2 */
	int *b;
	/** The due dates */
	int *d;
	/** The number of destinations */
	int m;
	/** The destinations of the jobs (k[j] is the destination of job j) */
	int *k;
	/** The distance matrix */
	int **K;
public:
	Instance(int n, int m);
	virtual ~Instance();
	void print(ostream &flux) const;

	int getA(int j) {
		return this->a[j];
	}

	void setA(int j, int p) {
		this->a[j] = p;
	}

	int getB(int j) {
		return b[j];
	}

	void setB(int j, int p) {
		this->b[j] = p;
	}

	int getD(int j) {
		return d[j];
	}

	void setD(int j, int d) {
		this->d[j] = d;
	}

	int getk(int j) {
		return k[j];
	}

	void setk(int j, int k) {
		this->k[j] = k;
	}

	int getK(int i, int j) {
		return K[i][j];
	}

	void setK(int i, int j, int d) {
		this->K[i][j] = d;
	}

	int getM() {
		return m;
	}

	void setM(int m) {
		this->m = m;
	}

	int getN() {
		return n;
	}

	void setN(int n) {
		this->n = n;
	}
};

ostream& operator<<(ostream &flux, const Instance& instance);

#endif /* INSTANCE_H_ */
