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
#include "Ants.h"
#include "Job.h"
using namespace std;

int main() {
	
	cout << "START" << endl;

	/* Generator */
//	int n[3] = { 10, 20, 50 };
//	Generator generator(n, 3, 10, 100, 0.5, 0.5);
//	generator.generate("./data");

	/* Tester */
	Tester tester("./data", "./results", true);
	tester.begin();

	/* Test */
//	Instance instance("./test/test_3.txt");
//	cout << instance;
//	// Test solution
//	Solution solution(&instance);
//	int s[instance.getN()];
//	int r[2 * instance.getN()];
//	Ants ants(&instance, 50, 10, 0.2, 0.1, 0.1, 1, 1, 1, 1, 1);
//	ants.begin(s, r);
//	//cout << ants << endl;
//	solution.setS(s);
//	solution.setR(r);
//	solution.refresh(true);
//	cout << solution;

	return 0;
}
