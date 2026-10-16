#include <iostream>
#include <string> 
#include "core.h"

int main() {
	Core core;
	
	core.UpdateCore();

	std::cout << "The core's volume is: " << core.GetVolume() << "m^3." << std::endl;
	return 0;
}