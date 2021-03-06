#include "LogicGate.h"

LogicGate::LogicGate(uint32_t type)
{
	_nType = type;
	_dOutput = NULL;
}

int8_t LogicGate::calculate() const
{
	{
		switch (_nType)
		{
		case AND:
			return calculateAnd();
			break;
		case OR:
			return calculateOr();
			break;
		case NOT:
			return calculateNot();
			break;
		case XOR:
			return calculateXor();
			break;
		case NAND:
			return calculateNand();
			break;
		case NOR:
			return calculateNor();
			break;
		case XNOR:
			return calculateXnor();
			break;
		}
	}
	return -1;
}

//calculating functions
int8_t LogicGate::calculateAnd() const
{
	const int8_t result = 1;
	for (uint32_t i = 0; i<_vInputs.size(); ++i)
	{
		const int8_t temp = *_vInputs.at(i);
		if (!(temp == 1) && !(temp == 0))
		{
			return -1;
		}
		else
		{
			if (temp == 0)
			{
				return 0;
			}
		}
	}
	return result;
}

int8_t LogicGate::calculateOr() const
{
	const int8_t result = 0;
	for (uint32_t i = 0; i<_vInputs.size(); ++i)
	{
		const int8_t temp = *_vInputs.at(i);
		if (!(temp == 1) && !(temp == 0))
		{
			return -1;
		}
		else
		{
			if (temp == 1)
			{
				return 1;
			}
		}
	}
	return result;
}

int8_t LogicGate::calculateNot() const
{
	const int8_t in = *_vInputs.at(0);
	if (in == 0 || in == 1)
	{
		if (in == 0)
		{
			return 1;
		}
		else if (in == 1)
		{
			return 0;
		}
	}
	return -1;
}

int8_t LogicGate::calculateXor() const
{
	uint8_t ct = 0;
	for (uint32_t i = 0; i<_vInputs.size(); ++i)
	{
		const int8_t temp = *_vInputs.at(i);
		if (!(temp == 1) && !(temp == 0))
		{
			return -1;
		}
		if (temp == 1)
		{
			++ct;
		}
	}
	if (ct % 2 == 0)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

int8_t LogicGate::calculateNand() const
{
	const int8_t result = 0;
	for (uint32_t i = 0; i<_vInputs.size(); ++i)
	{
		const int8_t temp = *_vInputs.at(i);
		if (!(temp == 1) && !(temp == 0))
		{
			return -1;
		}
		else
		{
			if (temp == 0)
			{
				return 1;
			}
		}
	}
	return result;
}

int8_t LogicGate::calculateNor() const
{
	const int8_t result = 1;
	for (uint32_t i = 0; i<_vInputs.size(); ++i)
	{
		const int8_t temp = *_vInputs.at(i);
		if (!(temp == 1) && !(temp == 0))
		{
			return -1;
		}
		else
		{
			if (temp == 1)
			{
				return 0;
			}
		}
	}
	return result;
}

int8_t LogicGate::calculateXnor() const
{
	uint8_t ct = 0;
	for (uint32_t i = 0; i<_vInputs.size(); ++i)
	{
		const int8_t temp = *_vInputs.at(i);
		if (!(temp == 1) && !(temp == 0))
		{
			return -1;
		}
		if (temp == 1)
		{
			++ct;
		}
	}
	if (ct % 2 == 0)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}