/*
 * Solution.cpp
 *
 *  Created on: 23 déc. 2013
 *      Author: Caelum
 */

#include "Solution.h"

void Solution::init() {
	s = NULL;
	r = NULL;
	I = NULL;
	n = 0;
	v = 0;
	w = 0;
	T = INT_MAX;
}

Solution::Solution() {
	init();
}

Solution::Solution(Instance * I) {
	init();
	this->n = I->getN();
	this->s = new int[n];
	this->r = new int[n];
	this->jobs = I->getJobs();
	setI(I);
	v = 0;
	w = 0;
	T = INT_MAX;
}

Solution::~Solution() {
//	if (s != NULL)
//		delete s;
//	if (r != NULL)
//		delete r;
}

void Solution::refresh(bool whole) {
	// Date for M1
	int date = 0;
	if (whole == true) {
		// For each job of the sequence s we compute the completion times of the flowshop
		for (int i = 0; i < n; i++) {
			date += jobs[s[i]].getA();
			if (i == 0 || date > jobs[s[i - 1]].getc())
				jobs[s[i]].setc(date + jobs[s[i]].getB());
			else
				jobs[s[i]].setc(jobs[s[i - 1]].getc() + jobs[s[i]].getB());
		}
	}

	date = jobs[s[0]].getc();
	v = 0;
	w = 0;
	int i = 0;
	int k = 0;
	int max = 0;
	// For each group of jobs we compute the completion times for the traveling salesman problem.
	while (i < n * 2) {
		k = r[i];
		if (k == 0) {
			i = n * 2;
		} else {
			i++;
			max = 0;
			// The truck leaves at the max completion time of the jobs of the group (or last date of arrival of the truck if the date is greater).
			for (int j = i; j < i + k; j++) {
				max = std::max(jobs[r[j]].getc(), max);
			}
			// The truck waits
			if (max > date) {
				v += max - date;
			}
			// The jobs wait
			else if (date > max) {
				w += date - max;
			}
			date = std::max(max, date);

			// We compute the completion times of the traveling salesman problem for our group of jobs.
			// Distance between factory and first destination
			date += I->getK(0, jobs[r[i]].getK());
			for (int j = i + 1; j < i + k; j++) {
				// Distance between last destination and next destination
				date += I->getK(jobs[r[j - 1]].getK(), jobs[r[j]].getK());
			}
			// Distance between last destination and factory
			date += I->getK(jobs[r[i + k - 1]].getK(), 0);

			// We set the completion times of the jobs
			for (int j = i; j < i + k; j++) {
				jobs[r[j]].setC(date);
			}
			i += k;
		}
	}
	T = 0;
	for (int i = 0; i < n; i++) {
		jobs[s[i]].setL(jobs[s[i]].getC() - jobs[s[i]].getD());
		T += std::max(jobs[s[i]].getL(), 0);
	}
}

void Solution::print(ostream &flux) const {

	flux << "s\t";
	for (int j = 0; j < n; j++) {
		flux << s[j] << "\t";
	}
	flux << endl;

	flux << "r\t";
	for (int j = 0; j < n * 2; j++) {
		flux << r[j] << "\t";
	}
	flux << endl;

	flux << "c\t";
	for (int j = 0; j < n; j++) {
		flux << jobs[j].getc() << "\t";
	}
	flux << endl;

	flux << "C\t";
	for (int j = 0; j < n; j++) {
		flux << jobs[j].getC() << "\t";
	}
	flux << endl;

	flux << "l\t";
	for (int j = 0; j < n; j++) {
		flux << jobs[j].getL() << "\t";
	}
	flux << endl;

	flux << "v\t" << v << endl;
	flux << "w\t" << w << endl;
	flux << "%v\t" << v * 100 / jobs[s[n - 1]].getC() << "%" << endl;
	flux << "%w\t" << w * 100 / jobs[s[n - 1]].getC() << "%" << endl;

	flux << "SumT\t" << T << endl;
}

Solution& Solution::operator=(const Solution& solution) {
	if (n != solution.getN()) {
		if (s != NULL)
			delete s;
		if (r != NULL)
			delete r;
		n = solution.getN();
		s = new int[n];
		r = new int[n * 2];
	}
	I = (Instance*) solution.getI();
	this->jobs = I->getJobs();
	v = solution.getV();
	w = solution.getW();
	T = solution.getT();
	for (int i = 0; i < n * 2; i++) {
		if (i < n)
			s[i] = solution.getS()[i];
		r[i] = solution.getR()[i];
	}
	return *this;
}

ostream& operator<<(ostream &flux, const Solution& solution) {
	solution.print(flux);
	return flux;
}
