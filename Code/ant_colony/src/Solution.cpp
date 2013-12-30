/*
 * Solution.cpp
 *
 *  Created on: 23 déc. 2013
 *      Author: Caelum
 */

#include "Solution.h"

Solution::Solution(Instance * I) {
	this->s = new int[I->getN()];
	this->t = new int[I->getN() * 2];
	this->l = new int[I->getN()];
	this->c = new int[I->getN()];
	this->C = new int[I->getN()];
	L = INT_MAX;
	setI(I);
}

Solution::~Solution() {
	delete s;
	delete t;
	delete l;
	delete c;
	delete C;
}

void Solution::refresh(bool whole) {
	// Date for M1
	int n = I->getN();
	int date = 0;
	if (whole == true) {
		// For each job of the sequence s we compute the completion times of the flowshop
		for (int i = 0; i < n; i++) {
			date += I->getA(s[i]);
			if (date > c[s[i - 1]] || i == 0)
				c[s[i]] = date + I->getB(s[i]);
			else
				c[s[i]] = c[s[i - 1]] + I->getB(s[i]);
		}
	}

	date = 0;
	int i = 0;
	int k = 0;
	int max = 0;
	// For each group of jobs we compute the completion times for the traveling salesman problem.
	while (i < n * 2) {
		k = t[i];
		i++;
		max = 0;
		// The truck leaves at the max completion time of the jobs of the group (or last date of arrival of the truck if the date is greater).
		for (int j = i; j < i + k; j++) {
			max = std::max(t[j], max);
		}
		date = std::max(max, date);

		// We compute the completion times of the traveling salesman problem for ou group of jobs.
		// Distance between factory and first destination
		date += I->getK(0, I->getk(t[i]));
		for (int j = i + 1; j < i + k; j++) {
			// Distance between last destination and next destination
			date += I->getK(I->getk(t[i - 1]), I->getk(t[i]));
		}
		// Distance between last destination and factory
		date += date += I->getK(I->getk(t[i + k - 1]), 0);

		// We set the completion times of the jobs
		for (int j = i; j < i + k; j++) {
			C[j] = date;
		}
		i += k;
	}
}

void Solution::print(ostream &flux) const {
	int n = I->getN();

	flux << "s ";
	for (int j = 0; j < n; j++) {
		flux << s[j] << " ";
	}
	flux << endl;

	flux << "t ";
	for (int j = 0; j < n * 2; j++) {
		flux << t[j] << " ";
	}
	flux << endl;

	flux << "c ";
	for (int j = 0; j < n; j++) {
		flux << c[j] << " ";
	}
	flux << endl;

	flux << "C ";
	for (int j = 0; j < n; j++) {
		flux << C[j] << " ";
	}
	flux << endl;

	flux << "l ";
	for (int j = 0; j < n; j++) {
		flux << l[j] << " ";
	}
	flux << endl;

	flux << "L " << L << endl;
}

ostream& operator<<(ostream &flux, const Solution& solution) {
	solution.print(flux);
	return flux;
}
