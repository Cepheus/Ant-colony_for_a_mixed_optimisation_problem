/*
 * Generator.cpp
 *
 *  Created on: 10 janv. 2014
 *      Author: Thomas
 */

#include "Generator.h"

/**
 * @param n The array of values n.
 * @param n_size The size of the array n.
 * @param nb_instances The number of instances per value n.
 * @param p_max The max value of processing time.
 * @param alpha The value of the parameter alpha;
 * @param gamma The value of the parameter gamma;
 */
Generator::Generator(int* n, int n_size, int nb_instances, int p_max,
		double alpha, double gamma) {
	this->n = n;
	this->n_size = n_size;
	this->nb_instances = nb_instances;
	this->p_max = p_max;
	this->alpha = alpha;
	this->gamma = gamma;
}

Generator::~Generator() {
}

/**
 * The generation of the instances.
 * This function generate instances into files.
 * @param destinationFolder The destination folder of the files to be generated.
 */
void Generator::generate(string destinationFolder) {
	ofstream file;
	stringstream fileName;

	// For each value of n.
	for (int k = 0; k < n_size; k++) {
		// We generate nb_instances instances.
		for(int i = 1; i <= nb_instances; i++) {
			fileName.str("");
			fileName.clear();
			fileName << destinationFolder << "/dat_" << n[k] << "_" << i << ".txt";
			file.open(fileName.str().c_str());
			file << "n\t" << n[k] << "\n";
			file << "m\t" << n[k]+1 << "\n";
			// We generate n jobs.
			for(int j = 0; j < n[k]; j++) {
				;
			}
			file.close();
		}
	}
}

