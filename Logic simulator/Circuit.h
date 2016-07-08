#pragma once
#include <iostream>
#include <cstdio>
#include <vector>
#include <fstream>
#include <string>
using namespace std;
class Circuit
{
public:
	Circuit();
	~Circuit();
	void readData();

private:
	string * sStructureFile;
	string * sInputsFile;
	string * sOutputFile;
	vector<int8_t> * vData;
	uint32_t * nCurrentLine;
	uint32_t * nInputs;
	uint32_t * nNets;
	uint32_t * nOutputs;

	bool readDeclarations(ifstream & fin, string declaration);
	void readGates();

	bool isComment(string word);

};

