/*
 * Heuristics.cpp
 *
 *  Created on: 9 janv. 2014
 *      Author: Thomas
 */

#include "Heuristics.h"

Heuristics::Heuristics() {
}

Heuristics::~Heuristics() {
}

int* Heuristics::MinimumDueDateBatch(int* batchs, Job* jobs) {
	return batchs;
}

int* Heuristics::Jonhson(Job* jobs, int n, int* sequence) {
	Cliste listJobs;
	int subSeq1[n];
	int subSeq2[n];
	int k1 = 0;
	int k2 = 0;
	int min = INT_MAX;
	int id_max = INT_MAX;
	int i_max = INT_MAX;
	// Minimum processing time is 'a' or a 'b'
	char type = 0;
	for (int i = 0; i < n; i++) {
		listJobs.LISajouter_element(jobs[i], i);
	}
	// While we haven't scheduled all jobs
	while (k1 + k2 < n) {
		// We pick the minimum processing time
		for (unsigned int i = 0; i < listJobs.LISlire_taille(); i++) {
			if (listJobs.LISlire_element(i).getA() < min) {
				min = listJobs.LISlire_element(i).getA();
				type = 'a';
				id_max = listJobs.LISlire_element(i).getId();
				i_max = i;
			}
			if (listJobs.LISlire_element(i).getB() < min) {
				min = listJobs.LISlire_element(i).getB();
				type = 'b';
				id_max = listJobs.LISlire_element(i).getId();
				i_max = i;
			}
		}
		// We put the minimum into the sub sequence for M1 or M2
		if (type == 'a') {
			subSeq1[k1] = id_max;
			k1++;
		} else {
			subSeq2[k2] = id_max;
			k2++;
		}
		listJobs.LISsupprimer_element(i_max);
		min = INT_MAX;
	}

	// We join the sub sequence 1 with the sub sequence 2
	for (int i = 0; i < k1; i++) {
		sequence[i] = subSeq1[i];
	}
	for (int i = 0; i < k2; i++) {
		sequence[i+k1] = subSeq2[i];
	}

	return sequence;
}

/*int* Heuristics::Batching(Job* jobs) {

 }*/

int* Heuristics::NearestNeighbor(int* towns, int** K) {
	return towns;
}
