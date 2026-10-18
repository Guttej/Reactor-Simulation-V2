#include <iostream>
#include <string> 
#include "core.h"

int main() {
	Material aluminum("aluminum", 2.699, {{ Nuclides::Al27, 1.0 }}, Role::Structure, FractionType::ByWeight);
	Material water("Water", 1.0, { { Nuclides::H1, 2.0 },{ Nuclides::O16, 1.0 } }, Role::Moderator, FractionType::ByAtom);
	Material fuel("Uranium Mixture", 19.08, { { Nuclides::U235, 4.83e21 },{ Nuclides::U238, 4.35e22 } }, Role::Fuel, FractionType::ByAtom);
	Material boron("Boron", 1.0, { { Nuclides::B10, 1.0 } }, Role::Poison, FractionType::ByWeight );
	Core core1;
	Core core2;
	Core core3;

	core1.AddCoreMaterial(fuel, 1.0);
	core2.AddCoreMaterial(fuel, 0.8);
	core2.AddCoreMaterial(water, 0.2);
	core3.AddCoreMaterial(fuel, 0.7);
	core3.AddCoreMaterial(water, 0.2);
	core3.AddCoreMaterial(boron, 0.1);

	std::cout << "Core with only fuel: " << core1.ThermalUtilizationFactor() << std::endl;
	std::cout << "Core with fuel and water: " << core2.ThermalUtilizationFactor() << std::endl;
	std::cout << "Core with fuel, water, and poison: " << core3.ThermalUtilizationFactor() << std::endl;
	std::cout << std::endl << std::endl;
	std::cout << "Reproduction Factor Comparisons. Fuel Reproduction Factor: "<< fuel.ReproductionFactor() << std::endl;
	std::cout << "Core 1: " << core1.CoreReproductionFactor() << std::endl;
	std::cout << "Core 2: " << core2.CoreReproductionFactor() << std::endl;
	std::cout << "Core 3: " << core3.CoreReproductionFactor() << std::endl;

	return 0;
}