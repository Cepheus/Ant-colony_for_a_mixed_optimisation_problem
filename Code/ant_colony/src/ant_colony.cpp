//============================================================================
// Name        : ant_colony.cpp
// Author      : Thomas Noguer
// Version     :
// Copyright   : 
// Description :
//============================================================================

#include <iostream>
#include "Instance.h"
#include "Solution.h"
#include "Heuristics.h"
#include "Job.h"
using namespace std;

int main() {
	Heuristics heuristics;

	// Generate the instance
	// Find the solution

	// Test instance
	Instance instance(3,3);
	instance.setJob(0,1,2,3,1);
	instance.setJob(1,4,3,7,2);
	instance.setJob(2,5,5,10,1);
	instance.setK(0,0,0);
	instance.setK(0,1,1);
	instance.setK(0,2,2);
	instance.setK(1,0,1);
	instance.setK(1,1,0);
	instance.setK(1,2,3);
	instance.setK(2,0,2);
	instance.setK(2,1,3);
	instance.setK(2,2,0);

	/*int n = 3;
	int m = 3;
	Instance instance(n, m);
	for (int j = 0; j < n; j++) {
		instance.setJob(j, j + 1, j + 1, n - j, j % 2 + 1);
	}
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < m; j++) {
			if (i == j)
				instance.setK(i, j, 0);
			else
				instance.setK(i, j, i + j);
		}
	}*/
	cout << instance;

	// Test solution
	Solution solution(&instance);
	int s[] = { 0, 1, 2 };
	int r[] = { 1, 0, 1, 1, 1, 2 };
	solution.setS(heuristics.Jonhson(instance.getJobs(), 3, s));
	solution.setR(r);
	solution.refresh(true);
	cout << solution;

	return 0;
}
