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
//	int n[3] = { 10, 20, 50 };
//	Generator generator(n, 3, 10, 100, 0.5, 0.5);
//	generator.generate("./data");


	/* Tester */
	Tester tester("./data", "./results", false);
	tester.begin();

	/* Test */
//	Heuristics heuristics;
//	Instance instance("./data/test_02.txt");
//	cout << instance;
//	// Test solution
//	Solution solution(&instance);
//	int s[] = { 0, 1, 2 };
//	int r[] = { 1, 0, 1, 2, 1, 1 };
//	solution.setS(heuristics.Jonhson(instance.getJobs(), 3, s));
//	solution.setR(r);
//	solution.refresh(true);
//	cout << solution;

	return 0;
}
