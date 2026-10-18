#include <iostream>
#include <string> 
#include "core.h"
#include "materials.h"

int main() {
	Material aluminum("aluminum", 2.699, {{ Nuclides::Al27, 1.0 }}, FractionType::ByWeight);
	Material alSiAlloy("Al-Si Alloy", 2.66, { { Nuclides::Al27,0.95 },{ Nuclides::Si, 0.05 } }, FractionType::ByWeight);
	Material water("Water", 1.0, { { Nuclides::H1, 2.0 },{ Nuclides::O16, 1.0 } }, FractionType::ByAtom);

	std::cout << alSiAlloy.SigmaA() << " " << alSiAlloy.SigmaS() << " " << alSiAlloy.MeanFreePathA() << " " << alSiAlloy.MeanFreePathS() << std::endl;
	std::cout << water.SigmaA() << std::endl;
	return 0;
}