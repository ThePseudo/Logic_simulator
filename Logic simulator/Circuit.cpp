#include "Circuit.h"

Circuit::Circuit()
{
	errorFound = false;
	sStructureFile = new string;
	sInputsFile = new string;
	sOutputFile = new string;
	nCurrentLine = new uint32_t;
	nInputs = new uint32_t;
	nNets = new uint32_t;
	nOutputs = new uint32_t;
	vData = new vector<int8_t>;
	* sStructureFile = "structure.txt";
	* sInputsFile = "inputs.txt";
	*sOutputFile = "output.txt";
}

Circuit::~Circuit()
{
	delete sStructureFile;
	delete sInputsFile;
	delete sOutputFile;
	delete nCurrentLine;
	delete nInputs;
	delete nNets;
	delete nOutputs;
	vData->resize(0);
	delete vData;
}

void Circuit::readData()
{
	* nCurrentLine = 0;
	ifstream inputFile(sStructureFile->c_str());
	string buffer;
	bool declarationsRead = false;
	while (inputFile >> buffer)
	{
		++(* nCurrentLine);
		while (isComment(buffer))
		{
			getline(inputFile, buffer);
			inputFile >> buffer;
			++(* nCurrentLine);
		}
		if(declarationsRead)
		{
			readGates(buffer, inputFile);
		}
		else if (!declarationsRead)
		{
			declarationsRead = readDeclarations(inputFile, buffer);
		}
	}
	inputFile.close();
}

bool Circuit::readDeclarations(ifstream & fin, string declaration)
{
	bool declarationsRead = false;
	if ("NAME" == declaration)
	{
		getline(fin, declaration);
	}
	else if ("INPUTS" == declaration)
	{
		fin >> *nInputs;
	}
	else if ("NETS" == declaration)
	{
		fin >> *nNets;
	}
	else if ("OUTPUTS" == declaration)
	{
		fin >> *nOutputs;
	}
	else if ("GATES" == declaration)
	{
		declarationsRead = true;
		vData->resize(*nOutputs + *nNets + *nInputs);
	}
	else
	{
		errorFound = true;
		printf("Line %u: unknown declaration: %s\n", *nCurrentLine, declaration.c_str());
		getline(fin, declaration);
	}
	return declarationsRead;
}

void Circuit::readGates(string gate, ifstream & fin)
{
	uint16_t gateType = gateTypes::UNVALID;
	uint16_t numberOfInputs;
	if("NOT" == gate.substr(0, 3))
	{
		gateType = gateTypes::NOT;
		numberOfInputs = 1;
	}
	else if ("AND" == gate.substr(0, 3))
	{
		gateType = gateTypes::AND;
		numberOfInputs = intFromString(gate.substr(3, gate.size()-1), 2);
	}
	else if ("OR" == gate.substr(0, 2))
	{
		gateType = gateTypes::OR;
		numberOfInputs = intFromString(gate.substr(2, gate.size() - 1), 2);
	}
	else if ("XOR" == gate.substr(0, 3))
	{
		gateType = gateTypes::XOR;
		numberOfInputs = intFromString(gate.substr(3, gate.size() - 1), 2);
	}
	else if ("NAND" == gate.substr(0, 4))
	{
		gateType = gateTypes::NAND;
		numberOfInputs = intFromString(gate.substr(4, gate.size() - 1), 2);
	}
	else if ("NOR" == gate.substr(0, 3))
	{
		gateType = gateTypes::NOR;
		numberOfInputs = intFromString(gate.substr(3, gate.size() - 1), 2);
	}
	else if ("XNOR" == gate.substr(0, 4))
	{
		gateType = gateTypes::XNOR;
		numberOfInputs = intFromString(gate.substr(4, gate.size() - 1), 2);
	}
	else
	{
		printf("Line %u: unknown gate: %s\n", *nCurrentLine, gate.c_str());
	}
}

bool Circuit::isComment(string word)
{
	bool isComment = false;
	if (word.substr(0, 2) == "//")
	{
		isComment = true;
	}
	return isComment;
}

int32_t Circuit::intFromString(string number, int32_t error)
{
	if (!number.empty())
	{
		for (int i = 0; i < number.size(); ++i)
		{
			if (!isdigit(number.at(i)))
			{
				return error;
			}
		}
		return atoi(number.c_str());
	}
	return error;
}