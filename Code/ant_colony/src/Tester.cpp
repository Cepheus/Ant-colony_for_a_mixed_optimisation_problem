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
	clock_t start_time, end_time;
	double total_time;
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
		int *s;
		int *r;
		Solution solution(&instance);
		s = solution.getS();
		r = solution.getR();
		// Prepare output file
		fileName.str("");
		fileName.clear();
		inputFileName.find_last_of("_");
		fileName << outputFolder << "/" << outputFilePrefix << "_"
				<< instance.getN()
				<< inputFileName.substr(inputFileName.find_last_of("_"));
		cout << fileName.str() << endl;
		instance_number++;
		outFile.open(fileName.str().c_str(), ofstream::out | ofstream::trunc);

		// Execution
		start_time = clock();
		if (useAnts) {
			Ants ants(&instance, 50, 10, 0.2, 0.1, 0.1, 1, 1, 1, 1, 1);
			ants.begin(s, r);
			solution.refresh(true);
		} else {
			heuristics.Jonhson(instance.getJobs(), n, s);
			heuristics.Batching(&instance, s, r);
			heuristics.NearestNeighbor(&instance, r);
			solution.refresh(true);
			if (inputFileName.compare("./data/dat_10_3.txt") == 0) {
				cout << solution << endl;
				int i = 0;
			}
		}
		end_time = clock();
		total_time = (double) (end_time - start_time) / CLOCKS_PER_SEC;
		cout << start_time << " " << end_time << " " << total_time << endl;
		outFile << solution.getT() << "\t" << total_time << "\t"
				<< (double) solution.getV() / instance.getJob(s[n - 1]).getC()
				<< "\t"
				<< (double) solution.getW() / instance.getJob(s[n - 1]).getC()
				<< "\t";
		for (int i = 0; i < n; i++)
			outFile << s[i] << " ";
		outFile << "\t";
		for (int i = 0; i < n * 2; i++)
			outFile << r[i] << " ";
		outFile << "\t";
//		outFile << "Time(s)\t" << total_time << endl;
//		outFile << "Solution" << endl;
//		outFile << solution;
		outFile.close();
	}
}

