//============================================================================
// Name        : ant_colony.cpp
// Author      : Thomas Noguer
// Version     :
// Copyright   : 
// Description :
//============================================================================

#include <iostream>
#include "Generator.h"
#include "Tester.h"
#include "Instance.h"
#include "Solution.h"
#include "Heuristics.h"
#include "Job.h"
using namespace std;

int main() {
	/* Generator */
	int n[3] = { 10, 20, 50 };
	Generator generator(n, 3, 10, 100, 0.5, 0.5);
	generator.generate("./data");

	/* Tester */
//	Tester tester("./data", "./results", false);
//	tester.begin();

	/* Test */
//	Heuristics heuristics;
//	Instance instance("./test/test_02.txt");
//	cout << instance;
//	// Test solution
//	Solution solution(&instance);
//	int s[instance.getN()];
//	//int r[6] = {1,0,2,1,2,0};
//	int r[2*instance.getN()];
//	heuristics.Jonhson(instance.getJobs(), instance.getN(), s);
//	solution.setS(s);
//	heuristics.Batching(&instance, s, r);
//	heuristics.NearestNeighbor(&instance, r);
//	//heuristics.MinimumDueDateBatch(r, instance.getJobs(), instance.getN()*2);
//	solution.setR(r);
//	solution.refresh(true);
//	cout << solution;

	return 0;
}
