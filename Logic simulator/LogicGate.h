#pragma once
#include <vector>
#include <iostream>
using namespace std;

enum gateTypes{ AND, OR, NOT, XOR, NAND, NOR, XNOR, UNVALID };

class LogicGate
{
public:
	LogicGate(uint32_t type);
	LogicGate();
	int8_t calculate();
	int8_t *output() const;
	void output(int8_t *output);
	void setOutput();
	void addInput(int8_t *input);
private:
	vector<int8_t *> _vInputs;
	int32_t _nType;
	int8_t *_dOutput;
	int8_t calculateAnd();
	int8_t calculateOr();
	int8_t calculateNot();
	int8_t calculateXor();
	int8_t calculateNand();
	int8_t calculateNor();
	int8_t calculateXnor();
};