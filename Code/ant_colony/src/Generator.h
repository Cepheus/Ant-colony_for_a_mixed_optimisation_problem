/*
 * Generator.h
 *
 *  Created on: 10 janv. 2014
 *      Author: Thomas Noguer
 */

#ifndef GENERATOR_H_
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#define GENERATOR_H_

using namespace std;

/**
 * This class contains the tools and function to generate instances into files.
 */
class Generator {
public:
	Generator(int* n, int n_size, int nb_instances, int p_max, double alpha, double gamma);
	virtual ~Generator();
	void generate(string destinationFolder);
private:
	/** The array of values n. */
	int *n;
	/** The size of the array n. */
	int n_size;
	/** The number of instances per value of n. */
	int nb_instances;
	/** The max value of processing time. */
	int p_max;
	/** The value of the parameter alpha. */
	double alpha;
	/** The value of the parameter gamma. */
	double gamma;
	/** Returns the distance between two points. */
	int distance(int x1, int y1, int x2, int y2);
};

#endif /* GENERATOR_H_ */
