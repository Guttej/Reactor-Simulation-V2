#include <iostream>
#include <string> 
#include "core.h"
#include "materials.h"

int main() {

	Material aluminum("aluminum", 2.699, {{ Nuclides::Al27, 1.0 }});

	Material alSiAlloy("Al-Si Alloy", 2.66, { { Nuclides::Al27,0.95 },{ Nuclides::Si, 0.05 } });

	std::cout << aluminum.GetConstituent() << " " << alSiAlloy.GetConstituent();
	return 0;
}