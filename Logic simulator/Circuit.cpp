#include "Circuit.h"

Circuit::Circuit()
{
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
		if (!declarationsRead)
		{
			declarationsRead = readDeclarations(inputFile, buffer);
		}
	}
	inputFile.close();
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
		printf("Line %u: unknown declaration: %s\n", *nCurrentLine, declaration.c_str());
		getline(fin, declaration);
	}
	return declarationsRead;
}

void Circuit::readGates()
{

}
