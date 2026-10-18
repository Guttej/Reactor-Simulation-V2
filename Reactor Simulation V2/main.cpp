#include <iostream>
#include <string> 
#include "core.h"
#include "materials.h"

int main() {
	Material aluminum("aluminum", 2.699, {{ Nuclides::Al27, 1.0 }}, Role::Structure, FractionType::ByWeight);
	Material water("Water", 1.0, { { Nuclides::H1, 2.0 },{ Nuclides::O16, 1.0 } }, Role::Moderator, FractionType::ByAtom);
	Material fuel("Uranium Mixture", 1.0, { { Nuclides::U235, 4.83e21 },{ Nuclides::U238, 4.35e22 } }, Role::Fuel, FractionType::ByAtom);
	
	std::cout << fuel.ReproductionFactor() << std::endl;

	return 0;
}