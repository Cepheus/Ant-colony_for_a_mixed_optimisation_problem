/*
 * Ants.cpp
 *
 *  Created on: 11 janv. 2014
 *      Author: Thomas
 */

#include "Ants.h"

Ants::Ants(Instance *I, int iteration_number, int ant_number,
		double initial_pheromone_value, double rho, double alpha, double beta,
		double psi, double omega, double chi) {
	this->I = I;
	this->iteration_number = iteration_number;
	this->ant_number = ant_number;
	this->initial_pheromone_value = initial_pheromone_value;
	this->rho = rho;
	this->alpha = alpha;
	this->beta = beta;
	this->psi = psi;
	this->omega = omega;
	this->chi = chi;

	n = I->getN();
	this->pheromone_green = new double*[n]();
	this->pheromone_red = new double*[n]();
	this->visibility_green = new double*[n]();
	this->visibility_red = new double*[n]();
	for (int i = 0; i < I->getN(); i++) {
		pheromone_green[i] = new double[n];
		pheromone_red[i] = new double[n];
		visibility_green[i] = new double[n];
		visibility_red[i] = new double[n];
	}
}

Ants::~Ants() {
	for (int i = 0; i < n; i++) {
		delete[] pheromone_green[i];
		delete[] pheromone_red[i];
		delete[] visibility_green[i];
		delete[] visibility_red[i];
	}
	delete[] pheromone_green;
	delete[] pheromone_red;
	delete[] visibility_green;
	delete[] visibility_red;
}

void Ants::begin(int *r) {
	int distance_max = INT_MIN;
	for (int i = 1; i < I->getM(); i++) {
		if (I->getK(0, i) > distance_max) {
			distance_max = I->getK(0, i);
		}
	}
	// Initialization of the pheromone matrix.b
	// Computation of the visibility matrix.
	for (int i = 0; i < n; i++) {
		for (int j = i; j < n; j++) {
			if (i == j) {
				pheromone_green[i][j] = 0;
				pheromone_red[i][j] = 0;
				visibility_green[i][j] = 0;
				visibility_red[i][j] = 0;
			} else {
				pheromone_green[i][j] = initial_pheromone_value;
				pheromone_red[i][j] = initial_pheromone_value;

				double visibility;
				// |di - dj|
				visibility = abs(I->getJob(i).getD() - I->getJob(j).getD());
				if (visibility == 0)
					visibility = 1;
				// (1/|di-dj|)^psi
				visibility = pow(1 / visibility, psi);
				visibility_green[i][j] = visibility;
				// delta_ij
				visibility = I->getK(I->getJob(i).getK(), I->getJob(j).getK());
				if (visibility == 0)
					visibility = 1;
				// (1/delta_ij)^omega
				visibility = pow(1 / visibility, omega);
				// (1/delta_ij)^omega * sqrt(delta_0i * delta_0j)/delta_max
				if (distance_max != 0)
					visibility = visibility
							* (sqrt(
									I->getK(0, I->getJob(i).getK())
											* I->getK(0, I->getJob(j).getK()))
									/ distance_max);
				// [(1/delta_ij)^omega * sqrt(delta_0i * delta_0j)/delta_max]^chi
				visibility = pow(visibility, chi);
				// (1/|di-dj|)^psi * [(1/delta_ij)^omega * sqrt(delta_0i * delta_0j)/delta_max]^chi
				visibility_green[i][j] *= visibility;

				if (visibility_green[i][j] == 0)
					visibility_red[i][j] = 1;
				else
					visibility_red[i][j] = 1 - visibility_green[i][j];
			}
		}
	}
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			pheromone_green[j][i] = pheromone_green[i][j];
			pheromone_red[j][i] = pheromone_red[i][j];
			visibility_green[j][i] = visibility_green[i][j];
			visibility_red[j][i] = visibility_red[i][j];
		}
	}

}

void Ants::print(ostream &flux) const {
	flux << "Green pheromone" << endl;
	for (int i = 0; i < n; i++) {
		flux << "   ";
		for (int j = 0; j < n; j++) {
			flux << pheromone_green[i][j] << "\t";
		}
		flux << endl;
	}
	flux << endl;

	flux << "Red pheromone" << endl;
	for (int i = 0; i < n; i++) {
		flux << "   ";
		for (int j = 0; j < n; j++) {
			flux << pheromone_red[i][j] << "\t";
		}
		flux << endl;
	}
	flux << endl;

	flux << "Green visibility" << endl;
	for (int i = 0; i < n; i++) {
		flux << "   ";
		for (int j = 0; j < n; j++) {
			flux << visibility_green[i][j] << "\t";
		}
		flux << endl;
	}
	flux << endl;

	flux << "Red visibility" << endl;
	for (int i = 0; i < n; i++) {
		flux << "   ";
		for (int j = 0; j < n; j++) {
			flux << visibility_red[i][j] << "\t";
		}
		flux << endl;
	}
	flux << endl;
}

ostream& operator<<(ostream &flux, const Ants& ants) {
	ants.print(flux);
	return flux;
}

