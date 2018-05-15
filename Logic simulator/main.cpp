#include <cstdio>
#include <iostream>
#include "Circuit.h"

int32_t main()
{
	Circuit circuito;
	circuito.readData();
	circuito.calculate();
	return EXIT_SUCCESS;
}