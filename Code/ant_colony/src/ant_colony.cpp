//============================================================================
// Name        : ant_colony.cpp
// Author      : Thomas Noguer
// Version     :
// Copyright   : 
// Description :
//============================================================================

#include <iostream>
#include "Instance.h"
using namespace std;

int main() {
	// Generate the instance
	// Find the solution

	int n = 3;
	int m = 3;
	Instance instance(n, m);
	for (int j = 0; j < n; j++) {
		instance.setA(j, j);
		instance.setB(j, j);
		instance.setD(j, n - j);
		instance.setk(j, n - j);
	}
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < m; j++) {
			instance.setK(i, j, i + j);
		}
	}

	cout << instance;
	return 0;
}
