/*
 * Tester.h
 *
 *  Created on: 10 janv. 2014
 *      Author: Thomas Noguer
 */

#ifndef TESTER_H_
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <conio.h>
#include <ctime>
#include "Instance.h"
#include "Solution.h"
#include "Heuristics.h"
#include "Ants.h"
#define TESTER_H_

using namespace std;

/**
 * This class contains all the tools to launch a tester that will give output results in files.
 */
class Tester {
public:
	/**
	 * @param dataFolder The path to the folder containing the data to be used during testing.
	 * @param outputFolder The path to the folder containing the results.
	 * @param use_ants True if we must use the ant colony heuristic to build the batches, false to use basic heuristic.
	 */
	Tester(string dataFolder, string outputFolder, bool useAnts);
	virtual ~Tester();
	/**
	 * Begins testing.
	 */
	void begin();
private:
	/**
	 * The path to the folder containing the data to be used during testing.
	 */
	string dataFolder;
	/*
	 * The path to the folder containing the results.
	 */
	string outputFolder;
	/*
	 * The prefix of the output file. Heuristic or Ant.
	 */
	string outputFilePrefix;
	/**
	 * True if we must use the ant colony heuristic to build the batches, false to use basic heuristic.
	 */
	bool useAnts;
};

#endif /* TESTER_H_ */
