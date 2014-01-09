/*
 * Job.cpp
 *
 *  Created on: 9 janv. 2014
 *      Author: Thomas
 */

#include "Job.h"

Job::Job() {
	id = INT_MAX;
	a = INT_MAX;
	b = INT_MAX;
	d = INT_MAX;
	k = INT_MAX;
	c = INT_MAX;
	C = INT_MAX;
	l = INT_MAX;
}

Job::Job(int id, int a, int b, int d, int k) {
	this->id = id;
	this->a = a;
	this->b = b;
	this->d = d;
	this->k = k;
	c = INT_MAX;
	C = INT_MAX;
	l = INT_MAX;
}

Job::~Job() {

}

