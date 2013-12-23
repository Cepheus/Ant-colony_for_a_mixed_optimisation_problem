/*
 * Solution.cpp
 *
 *  Created on: 23 déc. 2013
 *      Author: Caelum
 */

#include "Solution.h"

Solution::Solution(Instance * I) {
	this->s = new int[I->getN()];
	this->t = new int[I->getN()*2];
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
	int date = 0;
	if (whole == true) {
		// For each job of the sequence s we compute the completion times of the flowshop
		for (int i = 0; i < I->getN(); i++) {
			date += I->getA(s[i]);
			if (date > c[s[i-1]] || i == 0)
				c[s[i]] = date+I->getB(s[i]);
			else
				c[s[i]] = c[s[i-1]]+I->getB(s[i]);
		}
	}
}
