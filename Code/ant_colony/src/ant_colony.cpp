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
using namespace std;

int main() {
	// Generate the instance
	// Find the solution

	// Test instance
	int n = 3;
	int m = 3;
	Instance instance(n, m);
	for (int j = 0; j < n; j++) {
		instance.setA(j, j + 1);
		instance.setB(j, j + 1);
		instance.setD(j, n - j);
		instance.setk(j, (j)%2+1);
	}
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < m; j++) {
			if (i == j)
				instance.setK(i, j, 0);
			else
				instance.setK(i, j, i + j);
		}
	}
	//cout << instance;

	// Test solution
	Solution solution(&instance);
	int s[] = {0,1,2};
	int t[] = {1,0,1,1,1,2};
	solution.setS(s);
	solution.setT(t);
	solution.refresh(true);
	cout << solution;

	return 0;
}
