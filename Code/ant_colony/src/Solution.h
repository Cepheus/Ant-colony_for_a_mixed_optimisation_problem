/*
 * Solution.h
 *  Created on: 23 déc. 2013
 *      Author: Caelum
 */

#ifndef SOLUTION_H_
#include "Instance.h"
#include "Job.h"
#include <climits>
#include <algorithm>
#define SOLUTION_H_

/**
 * This class contains the data of a solution of an instance of our problem.
 */
class Solution {
private:
	/** The instance for which the solution comes from. */
	Instance* I;
	/** The list of jobs. */
	Job *jobs;
	/** The sequence of jobs for the flowshop problem. */
	int *s;
	/** The array containing the groups of jobs to be delivered as well as they delivery order (see report). */
	int *r;
	/** The sum of lateness, this is our objective function. */
	int T;
	/** The idle time for the truck. Amount of time the truck waited before shipping. */
	int v;
	/** The idle time of jobs. Amount of time the jobs waited before being being shipped. */
	int w;

public:
	Solution(Instance*);
	virtual ~Solution();
	void print(ostream &flux) const;

	/** Does the calculations of the solution.
	 *  @param whole True is the function must refresh the whole solution. False is we must only refresh from the array t.
	 */
	void refresh(bool whole);

	const Instance* getI() const {
		return I;
	}

	void setI(Instance* i) {
		I = i;
	}

	int* getS() const {
		return s;
	}

	void setS(int* s) {
		this->s = s;
	}

	int* getR() const {
		return r;
	}

	void setR(int* r) {
		this->r = r;
	}

	int getT() const {
		return T;
	}

	int getV() const {
		return v;
	}

	void setV(int v) {
		this->v = v;
	}

	int getW() const {
		return w;
	}

	void setW(int w) {
		this->w = w;
	}
};

ostream& operator<<(ostream &flux, const Solution& solution);

#endif /* SOLUTION_H_ */
