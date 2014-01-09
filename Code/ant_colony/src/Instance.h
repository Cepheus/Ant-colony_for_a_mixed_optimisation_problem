/*
 * Instance.h
 *  Created on: 25 nov. 2013
 *      Author: Thomas Noguer
 */

#ifndef INSTANCE_H_
#include "Job.h"
#define INSTANCE_H_

#include <iostream>
using namespace std;

/**
 * This class contains the data of an instance for our mixed scheduling problem.
 * @author Thomas Noguer
 */
class Instance {
private:
	/** The number of jobs. */
	int n;
	/** The number of destinations. */
	int m;
	/** The list of jobs. */
	Job* jobs;
	/** The distance matrix. */
	int **K;
public:
	Instance(int n, int m);
	virtual ~Instance();
	void print(ostream &flux) const;

	/**
	 * @return the list of jobs.
	 */
	Job* getJobs() {
		return jobs;
	}

	/**
	 * @param id The id of the job to return.
	 * @return The job of id id.
	 */
	Job getJob(int id) {
		return jobs[id];
	}

	/**
	 * Adds the job i to the list.
	 * @param i The id of the job, also its position in the array.
	 * @param a The processing time of the job on M1.
	 * @param b The processing time of the job on M2.
	 * @param k The id of destination of the job.
	 */
	void setJob(int i, int a, int b, int d, int k) {
		jobs[i].setA(a);
		jobs[i].setB(b);
		jobs[i].setD(d);
		jobs[i].setK(k);
	}

	/**
	 * Adds the job i to the list.
	 * @param i The id of the job, also its position in the array.
	 * @param job The job to add to the list.
	 */
	void setJob(int i, Job job) {
		jobs[i] = job;
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
