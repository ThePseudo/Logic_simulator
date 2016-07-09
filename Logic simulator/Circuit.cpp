#include "Circuit.h"

Circuit::Circuit()
{
	errorFound = new bool;
	*errorFound = false;
	_sStructureFile = new string;
	_sInputsFile = new string;
	_sOutputFile = new string;
	_nCurrentLine = new uint32_t;
	_nInputs = new uint32_t;
	_nNets = new uint32_t;
	_nOutputs = new uint32_t;
	_vData = new vector<int8_t>;
	_vGates = new vector<LogicGate>;
	* _sStructureFile = "structure.txt";
	* _sInputsFile = "inputs.txt";
	* _sOutputFile = "output.txt";
	* _nInputs = 0;
	* _nNets = 0;
	* _nOutputs = 0;
}

Circuit::~Circuit()
{
	delete errorFound;
	delete _sStructureFile;
	delete _sInputsFile;
	delete _sOutputFile;
	delete _nCurrentLine;
	delete _nInputs;
	delete _nNets;
	delete _nOutputs;
	_vData->resize(0);
	delete _vData;
	_vGates->resize(0);
	delete _vGates;
}

void Circuit::readData()
{
	* _nCurrentLine = 0;
	ifstream inputFile(_sStructureFile->c_str());
	string buffer;
	bool declarationsRead = false;
	while (inputFile >> buffer)
	{
		++(* _nCurrentLine);
		while (isComment(buffer))
		{
			getline(inputFile, buffer);
			inputFile >> buffer;
			++(*_nCurrentLine);
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
		fin >> declaration;
	}
	else if ("INPUTS" == declaration)
	{
		fin >> *_nInputs;
	}
	else if ("NETS" == declaration)
	{
		fin >> *_nNets;
	}
	else if ("OUTPUTS" == declaration)
	{
		fin >> *_nOutputs;
	}
	else if ("GATES" == declaration)
	{
		declarationsRead = true;
		_vData->resize(*_nOutputs + *_nNets + *_nInputs);
	}
	else
	{
		*errorFound = true;
		printf("%u line: unknown declaration of %s\n", *_nCurrentLine, declaration.c_str());
		getline(fin, declaration);
	}
	getline(fin, declaration);
	if (!isLineComment(declaration))
	{
		*errorFound = true;
		printf("%u line: unexpected syntax: %s\n", *_nCurrentLine, declaration.c_str());
	}

	return declarationsRead;
}

void Circuit::readGates(string gate, ifstream & fin)
{
	uint32_t gateType = gateTypes::UNVALID;
	uint32_t numberOfInputs;
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
		*errorFound = true;
		printf("%u line: unknown gate type: %s\n", *_nCurrentLine, gate.c_str());
		getline(fin, gate);
		return;
	}
	LogicGate tempGate(gateType);
	fin >> gate;
	for (uint32_t i = 0; i < numberOfInputs; ++i)
	{
		fin >> gate;
		gateType = intFromString(gate.substr(1, gate.size() - 2));
		gate = gate.substr(0, 1);
		if ("N" == gate)
		{
			if (gateType > * _nNets)
			{
				*errorFound = true;
				printf("%u line: input net not valid: %s%u\n", *_nCurrentLine, gate.c_str(), gateType);
				getline(fin, gate);
				return;
			}
			else
			{
				tempGate.addInput(&_vData->at(*_nInputs + gateType));
			}
		}
		else if ("I" == gate)
		{
			if (gateType > * _nInputs)
			{
				*errorFound = true;
				printf("%u line: input not valid: %s%u\n", *_nCurrentLine, gate.c_str(), gateType);
				getline(fin, gate);
				return;
			}
			else
			{
				tempGate.addInput(&_vData->at(gateType));
			}
		}
		else
		{
			*errorFound = true;
			printf("%u line: input not valid: %s%u\n", *_nCurrentLine, gate.c_str(), gateType);
			getline(fin, gate);
			return;
		}
	}
	fin >> gate;
	gateType = intFromString(gate.substr(1, gate.length() - 1));
	gate = gate.substr(0, 1);
	if ("N" == gate)
	{
		if (gateType > * _nNets)
		{
			*errorFound = true;
			printf("%u line: output net not valid: %s%u\n", *_nCurrentLine, gate.c_str(), gateType);
			getline(fin, gate);
			return;
		}
		else
		{
			tempGate.output(&_vData->at(*_nInputs + gateType));
		}
	}
	else if ("O" == gate)
	{
		if (gateType > * _nOutputs)
		{
			*errorFound = true;
			printf("%u line: output not valid: %s%u\n", *_nCurrentLine, gate.c_str(), gateType);
			getline(fin, gate);
			return;
		}
		else
		{
			tempGate.output(&_vData->at(*_nInputs + *_nNets + gateType));
		}
	}
	else
	{
		*errorFound = true;
		printf("%u line: output not valid: %s%u\n", *_nCurrentLine, gate.c_str(), gateType);
		getline(fin, gate);
		return;
	}
	_vGates->push_back(tempGate);
	gate = "";
	getline(fin, gate);
	if (!isLineComment(gate))
	{
		*errorFound = true;
		printf("%u line: unexpected syntax: %s\n", *_nCurrentLine, gate.c_str());
	}
}

void Circuit::calculate()
{
	if (*errorFound)
	{
		printf("Your outputs will not be calculated\n");
		system("pause");
		return;
	}
	sort();
	ifstream inputsFile(_sInputsFile->c_str());
	ofstream outputFile(_sOutputFile->c_str());
	int16_t buffer;
	while (inputsFile >> buffer)
	{
		if (buffer > 1)
		{
			buffer = 1;
		}
		else if (buffer < 0)
		{
			buffer = 0;
		}
		_vData->at(0) = static_cast<uint8_t>(buffer);
		for (uint32_t i = 1; i < *_nInputs; ++i)
		{
			inputsFile >> buffer;
			if (buffer > 1)
			{
				buffer = 1;
			}
			else if (buffer < 0)
			{
				buffer = 0;
			}
			_vData->at(i) = static_cast<int8_t>(buffer);
		}
		for (size_t i = 0; i < _vGates->size(); ++i)
		{
			_vGates->at(i).setOutput();
		}
		for (size_t i = (*_nInputs + *_nNets); i < _vData->size(); ++i)
		{
			outputFile << static_cast<int16_t>(_vData->at(i)) << " ";
		}
		outputFile << endl;
	}
	outputFile.close();
	inputsFile.close();
}

void Circuit::sort() //Basically, if a not already computable net is detected, this routine swaps it with the gate that should be calculated before
{
	bool swapped = false;
	for (size_t i = 0; i < _vGates->size(); ++i)
	{
		if (swapped)
		{
			i = i - 1;
			swapped = false;
		}
		for (uint32_t j = 0; j < _vGates->at(i).inputSize(); ++j)
		{
			for (size_t k = i+1; k < _vGates->size(); ++k)
			{
				if (_vGates->at(k).output() == _vGates->at(i).getInput(j))
				{
					LogicGate tempGate = _vGates->at(i);
					_vGates->at(i) = _vGates->at(k);
					_vGates->at(k) = tempGate;
					k = _vGates->size() + 1;
					swapped = true;
				}
			}
		}
	}
}

bool Circuit::isComment(string word) const
{
	bool isComment = false;
	if (word.substr(0, 2) == "//")
	{
		isComment = true;
	}
	return isComment;
}

bool Circuit::isLineComment(string word)
{
	bool comment = false;
	for (size_t i = 0; i < word.size(); ++i)
	{
		if (' ' == word.at(i))
		{
			word = word.substr(1, word.size());
			--i;
		}
		else
		{
			i = word.size() + 1;
		}
	}
	if (!word.empty())
	{
		if (isComment(word))
		{
			comment = true;
		}
	}
	else
	{
		comment = true;
	}
	return comment;
}

int32_t Circuit::intFromString(string number, int32_t error) const
{
	if (!number.empty())
	{
		for (uint32_t i = 0; i < number.size(); ++i)
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