/*
 * Ants.h
 *
 *  Created on: 11 janv. 2014
 *      Author: Thomas Noguer
 */

#ifndef ANTS_H_
#include <cmath>
#include <climits>
#include "Instance.h"
#define ZERO 0.00001
#define ANTS_H_

/**
 * This class contains the tools and function to use the ant colony heuristic.
 */
class Ants {
public:
	Ants(Instance *I, int iteration_number, int ant_number,
			double initial_pheromone_value, double rho, double alpha,
			double beta, double psi, double omega, double chi);
	virtual ~Ants();
	void print(ostream &flux) const;

	/**
	 * Launches the ant colony heuristic.
	 * @param r The output array. Contains the batches formed by the colony at the end of the execution.
	 */
	void begin(int *r);
private:

	/** The instance. */
	Instance *I;
	/** The number of jobs. */
	int n;

	int iteration_number;
	int ant_number;
	double initial_pheromone_value;

	/** Evaporation rate. */
	double rho;
	double alpha;
	double beta;
	double psi;
	double omega;
	double chi;

	/** Pheromone matrix for the green edges. */
	double **pheromone_green;
	/** Pheromone matrix for the red edges. */
	double **pheromone_red;
	/** Visibility matrix for the green edges. */
	double **visibility_green;
	/** Visibility matrix for the green edges. */
	double **visibility_red;
};

ostream& operator<<(ostream &flux, const Ants& ants);

#endif /* ANTS_H_ */
