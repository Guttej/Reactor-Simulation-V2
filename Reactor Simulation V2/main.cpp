#include <iostream>
#include <string> 
#include "core.h"
#include "materials.h"

int main() {
	
	Nuclide U235 = { "U235", 235.044, 694.0, 582.0, 15.0, 2.42 };

	std::cout << "Name: " << U235.name << " | Atomic Mass: " << U235.atomicMass << std::endl;

	return 0;
}