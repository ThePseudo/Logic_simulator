#pragma once
#include <vector>
#include <iostream>
using namespace std;

enum gateTypes{ AND, OR, NOT, XOR, NAND, NOR, XNOR, UNVALID };

class LogicGate
{
public:
	LogicGate(uint32_t type);
	LogicGate() {};

	inline int8_t * getInput(uint32_t i) const { return _vInputs.at(i); };
	inline size_t inputSize() const { return _vInputs.size(); };
	inline int8_t *output() const { return _dOutput; };
	inline void output(int8_t *output) { _dOutput = output; };
	inline void setOutput() { *_dOutput = calculate(); };
	inline void addInput(int8_t *input) {_vInputs.push_back(input); };
	int8_t calculate() const;
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