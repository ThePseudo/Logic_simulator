#pragma once
#include <iostream>
#include <cstdio>
#include <fstream>
#include <vector>
#include <string>
#include "LogicGate.h"
using namespace std;

class Circuit
{
public:
	Circuit();
	~Circuit();
	void readData();
	void calculate();
private:
	bool *errorFound;
	string * _sStructureFile;
	string * _sInputsFile;
	string * _sOutputFile;
	vector<int8_t> * _vData;
	vector<LogicGate> * _vGates;
	uint32_t * _nCurrentLine;
	uint32_t * _nInputs;
	uint32_t * _nNets;
	uint32_t * _nOutputs;

	bool readDeclarations(ifstream & fin, string declaration);
	void readGates(string gate, ifstream & fin);
	void sort();

	bool isComment(const string word) const;
	bool isLineComment(string word);
	int32_t intFromString(const string number, const int32_t error = 0) const;
};

