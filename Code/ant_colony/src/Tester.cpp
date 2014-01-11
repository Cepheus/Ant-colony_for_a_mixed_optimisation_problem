/*
 * Tester.cpp
 *
 *  Created on: 10 janv. 2014
 *      Author: Thomas
 */

#include "Tester.h"

Tester::Tester(string dataFolder, string outputFolder, bool useAnts) {
	this->dataFolder = dataFolder;
	this->outputFolder = outputFolder;
	this->useAnts = useAnts;
	if (useAnts)
		outputFilePrefix = "Ant";
	else
		outputFilePrefix = "Heuristic";
}

Tester::~Tester() {
}

void Tester::begin() {
	stringstream fileName;
	string inputFileName;
	ifstream inFile;
	ofstream outFile;
	DIR * dir = NULL;
	struct dirent* dirFile = NULL;
	clock_t start_time, end_time, total_time;
	Heuristics heuristics;
	int instance_number = 0;

	// Open the data folder
	dir = opendir(dataFolder.c_str());
	if (dir == NULL) {
		cerr << "Error while opening instances directory!" << endl;
		getch();
		exit(1);
	}
	readdir(dir);	// exploring .
	readdir(dir);	// exploring ..

	// Explore each file in the data folder
	while ((dirFile = readdir(dir)) != NULL) {
		// Read data
		fileName.str("");
		fileName.clear();
		fileName << dataFolder << "/" << dirFile->d_name;
		inputFileName = fileName.str();
		cout << inputFileName << endl;
		Instance instance(inputFileName);
		int n = instance.getN();
		int s[n];
		int r[2*n];
		Solution solution(&instance);
		// Prepare output file
		fileName.str("");
		fileName.clear();
		inputFileName.find_last_of("_");
		fileName << outputFolder << "/" << outputFilePrefix << "_" << instance.getN() << inputFileName.substr(inputFileName.find_last_of("_"));
		cout << fileName.str() << endl;
		instance_number++;
		outFile.open(fileName.str().c_str(), ofstream::out | ofstream::trunc);

		// Execution
		start_time = clock();
		if (useAnts) {
			// Ants
		} else {
			heuristics.Jonhson(instance.getJobs(), n, s);
			solution.setS(s);
			heuristics.Batching(&instance, s, r);
			heuristics.NearestNeighbor(&instance, r);
			solution.setR(r);
			solution.refresh(true);
		}
		end_time = clock();
		total_time = (end_time - start_time) / CLOCKS_PER_SEC;
		cout << start_time << " " << end_time << " " << total_time << endl;
		outFile << "Time(s)\t" << (double)total_time << endl;
		outFile << "Solution" << endl;
		outFile << solution;
		outFile.close();
	}
}

