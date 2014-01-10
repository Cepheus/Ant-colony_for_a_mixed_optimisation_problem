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

void Heuristics::MinimumDueDateBatch(int* batches, Job* jobs, int n) {
	int result[n];
	// min[0] minimal d for first batch.
	int min[n / 2];
	// size_batch[0] = 3 i.e. 3 elements are in the first batch.
	int size_batch[n / 2];
	// start_batch[0] = 3 i.e. The first batch start at position 3 in the array batches.
	int start_batch[n / 2];
	// scheduled[0] = true i.e. batch 0 has been scheduled.
	bool scheduled[n / 2];
	int i_batch = 0;
	int i;
	int k;
	// Initialization of min, size_batch and scheduled
	for (int i = 0; i < n / 2; i++) {
		min[i] = INT_MAX;
		size_batch[i] = 0;
		scheduled[i] = false;
	}
	i = 0;
	// For each batch
	while (i < n) {
		k = batches[i];
		// Batch size 0 i.e. end of array
		if (k == 0) {
			i = n;
			i_batch--;
		} else {
			size_batch[i_batch] = k;
			start_batch[i_batch] = i + 1;
			// For each job of our batch
			for (int j = 1; j <= k; j++) {
				// We get the min(d)
				if (jobs[batches[i + j]].getD() < min[i_batch]) {
					min[i_batch] = jobs[batches[i + j]].getD();
				}
			}
			i = i + k + 1;
			i_batch++;
		}
	}

	int min_all;
	int i_min;
	// The current position of the result array.
	int i_seq = 0;
	bool all_scheduled = false;
	// While we haven't scheduled all the batches
	while (!all_scheduled) {
		all_scheduled = true;
		min_all = INT_MAX;
		// For each batch
		for (i = 0; i < i_batch; i++) {
			if (!scheduled[i]) {
				all_scheduled = false;
				// We search for the minimal value within the min(d) of the batches.
				if (min[i] < min_all) {
					min_all = min[i];
					i_min = i;
				}
			}
		}
		// We schedule the batch with the minimal value
		if (!all_scheduled) {
			result[i_seq] = size_batch[i_min];
			i_seq++;
			for (i = 0; i < size_batch[i_min]; i++) {
				result[i_seq] = batches[i + start_batch[i_min]];
				i_seq++;
			}
			scheduled[i_min] = true;
		}
	}

	for (int i = 0; i < n; i++) {
		batches[i] = result[i];
	}
}

void Heuristics::Jonhson(Job* jobs, int n, int* sequence) {
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
		sequence[i + k1] = subSeq2[i];
	}
}

void Heuristics::Batching(Instance *instance, int* s, int* result) {
	int n = instance->getN();
	// The current sequence of job.
	int current_s[n];
	int i_result;
	int i_current_s;
	int batch_start;
	int min;
	Solution solution(instance);

	// Initialization of result and current_s at 0.
	for (int i = 0; i < 2 * n; i++) {
		result[i] = 0;
		if (i < n)
			current_s[i] = 0;
	}

	// We take the first job in the schedule and form a first batch with it.
	current_s[0] = s[0];
	i_current_s = 1;
	result[0] = 1;
	result[1] = s[0];
	i_result = 2;
	batch_start = 1;
	solution.setS(current_s);
	solution.setR(result);
	// For each other job, we see if the SumT is better if we put the next job in the old batch or in a new one.
	for (int i = 1; i < n; i++) {
		current_s[i_current_s] = s[i];
		i_current_s++;
		instance->setN(i_current_s);
		result[i_result] = s[i];
		result[batch_start - 1] = result[batch_start - 1] + 1;
		solution.refresh(true);
		min = solution.getT();

		result[batch_start - 1] = result[batch_start - 1] - 1;
		result[i_result] = 1;
		result[i_result + 1] = s[i];
		i_result += 2;
		solution.refresh(true);
		if (solution.getT() < min) {
			batch_start = i_result - 1;
		} else {
			i_result--;
			result[batch_start - 1] = result[batch_start - 1] + 1;
			result[i_result - 1] = s[i];

		}
	}
}

int* Heuristics::NearestNeighbor(int* towns, int** K) {
	return towns;
}
