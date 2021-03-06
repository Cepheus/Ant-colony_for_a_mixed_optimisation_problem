/*
 * Ants.cpp
 *
 *  Created on: 11 janv. 2014
 *      Author: Thomas
 */

#include "Ants.h"

Ants::Ants(Instance *I, int iteration_number, int ant_number,
		double diversification_probability, double initial_pheromone_value,
		double rho, double alpha, double beta, double psi, double omega,
		double chi) {
	this->I = I;
	this->iteration_number = iteration_number;
	this->ant_number = ant_number;
	this->diversification_probability = diversification_probability;
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
	for (int i = 0; i < n; i++) {
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

void Ants::begin(int *s, int *r) {
	int distance_max = INT_MIN;
	for (int i = 1; i < I->getM(); i++) {
		if (I->getK(0, i) > distance_max) {
			distance_max = I->getK(0, i);
		}
	}
	/* Initialization of the pheromone matrix. */
	/* Computation of the visibility matrix. */
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

	srand(time(NULL));
	// tabu[0] == True: job 0 is tabu, should not be considered.
	bool tabu[n];
	int start;
	int end;
	char color;
	int edge_start[n - 1];
	int edge_end[n - 1];
	char edge_color[n - 1];
	int edge_best_ant_start[n - 1];
	int edge_best_ant_end[n - 1];
	char edge_best_ant_color[n - 1];
	double sum_green;
	double sum_red;
	double p_green[n];
	double p_red[n];
	double max;
	int max_i;
	char max_c;
	int *s_found;
	int *r_found;
	Solution current_solution(I);
	Solution best_ant(I);
	Solution best(I);
	Heuristics heuristics;
	Job jobs_jonhson[n];
	int bestT = INT_MAX;
	double deltaT = initial_pheromone_value;
	// We set the pointers of the differents solutions we will store
	s_found = current_solution.getS();
	r_found = current_solution.getR();
	for (int i = 0; i < iteration_number; i++) {
		for (int m = 0; m < ant_number; m++) {
			/* Construct solution */
			// Init tabu list at false
			for (int j = 0; j < n; j++) {
				tabu[j] = false;
			}
			// We choose a random job as start point.
			start = rand() % n;
			// The start job is tabu
			tabu[start] = true;
			// We construct a Hamiltonian path within the graph.
			for (int e = 0; e < n - 1; e++) {
				sum_green = sum_red = 0;
				// We get the proba to do classic P or roulette P
				// We do classic P
				if ((double) rand() / RAND_MAX > diversification_probability) {
					// We get the sum of (pheromone_startj)^alpha * (visibility_startj)^beta where j not in tabu.
					// For both green and red
					for (int j = 0; j < n; j++) {
						if (!tabu[j]) {
							sum_green += pow(pheromone_green[start][j], alpha)
									* pow(visibility_green[start][j], beta);
							sum_red += pow(pheromone_red[start][j], alpha)
									* pow(visibility_red[start][j], beta);
						}
					}
					// We compute the probability for each edge.
					for (int j = 0; j < n; j++) {
						if (!tabu[j]) {
							p_green[j] = pow(pheromone_green[start][j], alpha)
									* pow(visibility_green[start][j], beta)
									/ sum_green;
							p_red[j] = pow(pheromone_red[start][j], alpha)
									* pow(visibility_red[start][j], beta)
									/ sum_red;
						} else
							p_green[j] = p_red[j] = 0;
					}
					max = INT_MIN;
					// We search for the highest probability.
					for (int j = 0; j < n; j++) {
						if (p_green[j] > max && !tabu[j]) {
							max = p_green[j];
							max_i = j;
							max_c = 'g';
						}
						if (p_red[j] > max && !tabu[j]) {
							max = p_red[j];
							max_i = j;
							max_c = 'r';
						}
					}
					// Our edge is chosen
					end = max_i;
					color = max_c;
				}
				// We do roulette P
				else {
					int j = 0;
					double cumul = 0;
					// We get the first non-tabu node.
					while (tabu[j] && j < n) {
						j++;
						p_green[j] = p_red[j] = 0;
					}
					// And give its p the initial pheromone value.
					p_green[j] = pheromone_green[start][j];
					cumul = p_red[j] = p_green[j] + pheromone_red[start][j];
					int last_j = j;
					// We compute the cumul of pheromone value
					for (j = j + 1; j < n; j++) {
						if (!tabu[j]) {
							p_green[j] = p_red[last_j]
									+ pheromone_green[start][j];
							cumul = p_red[j] = p_green[j]
									+ pheromone_red[start][j];
							last_j = j;
						} else
							p_green[j] = p_red[j] = 0;
					}
					// We pull a random number between 0 and the cumul of pheromone.
					max = (double) rand() / RAND_MAX * cumul;
					j = -1;
					do {
						j++;
						if (!tabu[j]) {
							if (p_green[j] >= max) {
								end = j;
								color = 'g';
							} else if (p_red[j] >= max) {
								end = j;
								color = 'r';
							}
						}
					} while (tabu[j] || (p_green[j] < max && p_red[j] < max));
				}
				edge_start[e] = start;
				edge_end[e] = end;
				edge_color[e] = color;
				start = end;
				tabu[start] = true;
			}

			// Init r_found with 0.
			for (int j = 0; j < n * 2; j++) {
				r_found[j] = 0;
			}
			int r_i;
			int batch_size_i = 0;
			r_found[0] = 1;
			r_found[1] = edge_start[0];
			r_i = 2;
			// We form the array r from the edges found by the ant.
			// Also we do the local pheromone update.
			for (int e = 0; e < n - 1; e++) {
				// Add to existing batch.
				if (edge_color[e] == 'g') {
					r_found[batch_size_i]++;
				}
				// Make a new batch.
				else {
					r_found[r_i] = 1;
					batch_size_i = r_i;
					r_i++;
				}
				r_found[r_i] = edge_end[e];
				r_i++;

				// Local pheromone update
				if (edge_color[e] == 'g') {
					pheromone_green[edge_start[e]][edge_end[e]] = (1 - rho)
							* pheromone_green[edge_start[e]][edge_end[e]]
							+ rho * initial_pheromone_value;
					pheromone_green[edge_end[e]][edge_start[e]] =
							pheromone_green[edge_start[e]][edge_end[e]];
				} else {
					pheromone_red[edge_start[e]][edge_end[e]] = (1 - rho)
							* pheromone_red[edge_start[e]][edge_end[e]]
							+ rho * initial_pheromone_value;
					pheromone_red[edge_end[e]][edge_start[e]] =
							pheromone_red[edge_start[e]][edge_end[e]];
				}
			}
			/* Use of heuristics to form the rest of the solution */
			// Order the batches by increasing order of minimum due date.
			heuristics.MinimumDueDateBatch(r_found, I->getJobs(), n * 2);
			// For each batch we apply Jonhson.
			int k;
			int nb_done = 0;
			int j = 0;
			while (j < n * 2) {
				k = r_found[j];
				if (k == 0) {
					j = n * 2;
				} else {
					// We make a new list of jobs in order of array r_found.
					for (int l = 0; l < k; l++) {
						jobs_jonhson[nb_done + l] = I->getJob(
								r_found[j + 1 + l]);
					}
					heuristics.Jonhson(jobs_jonhson + nb_done, k,
							s_found + nb_done);
					nb_done += k;
					j += k + 1;
				}
			}
			// We apply the nearest neighbor for the jobs of the batches.
			heuristics.NearestNeighbor(I, r_found);

			// We keep the best ant.
			current_solution.refresh(true);
			if (current_solution.getT() < best_ant.getT()) {
				best_ant = current_solution;
				for (int j = 0; j < n - 1; j++) {
					edge_best_ant_start[j] = edge_start[j];
					edge_best_ant_end[j] = edge_end[j];
					edge_best_ant_color[j] = edge_color[j];
				}
			}
		} // end for ants

		/* Global pheromone update. */
		// We update the pheromone matrix with the % of amelioration of the solution on the edges, the ant visited.
		// We keep the best from the best ants.
		if (best_ant.getT() < best.getT()) {
			if (bestT != INT_MAX) {
				deltaT = bestT - best_ant.getT() / bestT;
			}
			for (int e = 0; e < n - 1; e++) {
				if (edge_best_ant_color[e] == 'g') {
					pheromone_green[edge_best_ant_start[e]][edge_best_ant_end[e]] +=
							deltaT;
					pheromone_green[edge_best_ant_end[e]][edge_best_ant_start[e]] +=
							deltaT;
				} else {
					pheromone_red[edge_best_ant_start[e]][edge_best_ant_end[e]] +=
							deltaT;
					pheromone_red[edge_best_ant_end[e]][edge_best_ant_start[e]] +=
												deltaT;
				}
			}
			best = best_ant;
		}

	} // end for interations
	// We copy the best found solution into the return arrays.
	for (int j = 0; j < n * 2; j++) {
		if (j < n)
			s[j] = best.getS()[j];
		r[j] = best.getR()[j];
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

