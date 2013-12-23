/*
 * Solution.h
 *  Created on: 23 déc. 2013
 *      Author: Caelum
 */

#ifndef SOLUTION_H_
#include "Instance.h"
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
	/** The sequence of jobs for the flowshop problem. */
	int *s;
	/** The array containing the groups of jobs to be delivered as well as they delivery order (see report). */
	int *t;
	/**	The array of completion times for our jobs in the flowshop subproblem. */
	int c;
	/**	The array of completion times for ou jobs for the traveling salesman subproblem. (completion time of the complete problem)  */
	int C;
	/** The array of lateness for our jobs. */
	int *l;
	/** The sum of lateness, this is our objective function. */
	int L;
	/** Does the calculations of the solution.
	 *  @param whole True is the function must refresh the whole solution. False is we must only refresh from the array t.
	 */
	void refresh(bool whole);

public:
	Solution(Instance*);
	virtual ~Solution();

	const Instance* getI() const {
		return I;
	}

	void setI(const Instance* i) {
		I = i;
	}

	int* getS() const {
		return s;
	}

	void setS(int* s) {
		this->s = s;
	}

	int* getT() const {
		return t;
	}

	void setT(int* t) {
		this->t = t;
	}

	int* getL() const {
		return l;
	}

	int getL() const {
		return L;
	}
};

#endif /* SOLUTION_H_ */
