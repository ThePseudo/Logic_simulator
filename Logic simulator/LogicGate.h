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
	int8_t calculateAnd() const;
	int8_t calculateOr() const;
	int8_t calculateNot() const;
	int8_t calculateXor() const;
	int8_t calculateNand() const;
	int8_t calculateNor() const;
	int8_t calculateXnor() const;
};