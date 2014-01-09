/*
 * Job.h
 *
 *  Created on: 9 janv. 2014
 *      Author: Thomas Noguer
 */

#ifndef JOB_H_
#include <climits>
#define JOB_H_

/**
 * This class contains all the informations and tools related to a job.
 * @author Thomas Noguer
 */
class Job {
public:
	Job();
	Job(int id, int a, int b, int d, int k);
	virtual ~Job();

	int getId() {
		return this->id;
	}

	void setId(int id) {
		this->id = id;
	}

	int getA() {
		return this->a;
	}

	void setA(int a) {
		this->a = a;
	}

	int getB() {
		return b;
	}

	void setB(int b) {
		this->b = b;
	}

	int getD() {
		return d;
	}

	void setD(int d) {
		this->d = d;
	}

	int getK() {
		return k;
	}

	void setK(int k) {
		this->k = k;
	}

	int getc() {
		return c;
	}

	void setc(int c) {
		this->c = c;
	}

	int getC() {
		return C;
	}

	void setC(int C) {
		this->C = C;
	}

	int getL() {
		return l;
	}

	void setL(int l) {
		this->l = l;
	}

private:
	/** The id of the job. */
	int id;
	/** The processing time for M1. */
	int a;
	/** The processing time for M2. */
	int b;
	/** The due date. */
	int d;
	/** The destination of the job. */
	int k;
	/**	The completion time for the flowshop subproblem. */
	int c;
	/**	The completion time for the traveling salesman subproblem. */
	int C;
	/** The lateness.*/
	int l;
};

#endif /* JOB_H_ */
