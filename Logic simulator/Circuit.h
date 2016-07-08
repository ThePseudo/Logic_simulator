#pragma once
#include <iostream>
#include <cstdio>
#include <vector>
#include <fstream>
#include <string>
using namespace std;

enum gateTypes{AND, OR, XOR, NOT, NAND, NOR, XNOR, UNVALID};

class Circuit
{
public:
	Circuit();
	~Circuit();
	void readData();
private:
	bool errorFound;
	string * sStructureFile;
	string * sInputsFile;
	string * sOutputFile;
	vector<int8_t> * vData;
	uint32_t * nCurrentLine;
	uint32_t * nInputs;
	uint32_t * nNets;
	uint32_t * nOutputs;
	//helping functions
	bool readDeclarations(ifstream & fin, string declaration);
	void readGates(string gate, ifstream & fin);

	bool isComment(string word);
	int32_t intFromString(string number, int32_t error);
};

