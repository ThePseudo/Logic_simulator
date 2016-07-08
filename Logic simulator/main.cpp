#include <cstdio>
#include <iostream>
#include "Circuit.h"

int32_t main()
{
	Circuit * circuito = new Circuit;
	circuito->readData();
	cout << sizeof(circuito) << endl;
	return EXIT_SUCCESS;
}