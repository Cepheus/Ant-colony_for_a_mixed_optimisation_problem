/*
 * Heuristics.h
 *
 *  Created on: 9 janv. 2014
 *      Author: Thomas Noguer
 */

#ifndef HEURISTICS_H_
#include "Job.h"
#include "Cliste.h"
#include <climits>
#define HEURISTICS_H_

/** This class contains the tools and heuristics used to find the solution of our problem.
 * @author Thomas Noguer
 */
class Heuristics {
public:
	Heuristics();
	virtual ~Heuristics();

	/**
	 * The minimal due date batch scheduling algorithm.
	 * @param batches The sequence of batches to be ordered. Will contain the result at the end of execution.
	 * @param jobs The jobs.
	 * @param n The size of the array batches.
	 */
	void MinimumDueDateBatch(int* batches, Job* jobs, int n);

	/**
	 * Johnson's algorithm.
	 * @param jobs The list of jobs to be scheduled.
	 * @param n The number of jobs to be scheduled.
	 * @param sequence The array in which we will put the schedule
	 */
	void Jonhson(Job* jobs, int n, int* sequence);

	/**
	 * The batch heuristic.
	 * @param The sequence of id of jobs already scheduled on the flowshop.
	 * @param The list of jobs.
	 * @return The batches of id of jobs. (ex: batches found: {1,2}{4}{3}, sequence returned: [2,1,2,1,4,1,3,0])
	 */
	int* Batching(Job* jobs);

	/**
	 * Nearest neighbor algorithm.
	 * @param towns The list of towns to be scheduled.
	 * @param K The distance matrix.
	 * @return The sequence of id of towns ordered following the nearest neighbor algorithm.
	 */
	int* NearestNeighbor(int* towns, int** K);

};

#endif /* HEURISTICS_H_ */
