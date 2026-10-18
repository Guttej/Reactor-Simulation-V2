#include "core.h"
#include <iostream>

double PI = 3.14159;

Core::Core() : shape(Shape::None), volume(0.0), sixFactor{ 0.865, 0.80, 0.861, 0.799, 2.02, 1.04 }, keff(0.0) {}
Core::Core(Shape s, double v) : shape(s), volume(v), sixFactor{ 0.865, 0.80, 0.861, 0.799, 2.02, 1.04 }, keff(0.0) {}

Shape Core::GetShape() const { return this->shape; }
double Core::GetVolume() const { return this->volume; }

void Core::SetShape(Shape s) { this->shape = s; }
void Core::SetVolume(double v) { this->volume = v; }
void Core::AddCoreMaterial(const Material& m, double v) {
	this->coreMaterials.push_back({m, v});
}

void Core::BuildCore() {
	int userIntInput;
	double userDoubleInput;
	bool transitionFlag = false;

	while (transitionFlag != true) {

		std::cout << "Input Core Shape: ";
		std::cin >> userIntInput;
		std::cout << std::endl << std::endl;

		if (userIntInput == 1) {
			this->shape = Shape::Sphere;
			transitionFlag = true;
		}
		else if (userIntInput == 2) {
			this->shape = Shape::Cylinder;
			transitionFlag = true;
		}
		else if (userIntInput == 3) {
			this->shape = Shape::Cube;
			transitionFlag = true;
		}
		else {
			std::cout << "Please enter a valid input." << std::endl;
		}
	}

	transitionFlag = false;

	while (transitionFlag != true) {
		std::cout << "Input Length for Volume Calculation: ";
		std::cin >> userDoubleInput;

		if (this->shape == Shape::Sphere) {
			this->volume = (4.0 / 3.0) * PI * userDoubleInput * userDoubleInput * userDoubleInput;
			transitionFlag = true;
		}
		else if (this->shape == Shape::Cube) {
			this->volume = userDoubleInput * userDoubleInput * userDoubleInput;
			transitionFlag = true;
		}
		// TODO: cylinder assumes height == radius; take R and H separately
		//       once geometric buckling is added
		else if (this->shape == Shape::Cylinder) {
			this->volume = PI * userDoubleInput * userDoubleInput * userDoubleInput;
			transitionFlag = true;
		}
		else {
			std::cout << "Please enter a valid input." << std::endl;
		}
	}

}

void Core::UpdateCore() {
	double tmpDouble = 1.0; 

	// Six Factor Formula
	sixFactor[ThermalUtilization] = ThermalUtilizationFactor();	// Updates core's ThermalUtilization Factor
	sixFactor[Reproduction] = CoreReproductionFactor();			// Updates core's Reproduction Factor
	for (int i = 0; i < NumFactors; ++i) {
		tmpDouble *= sixFactor[i];		// Calculates keff
	}	
	this->keff = tmpDouble;				// Updates keff 
}

double Core::ThermalUtilizationFactor() const {
	double fuelAbsorption = 0.0;
	double totalAbsorption = 0.0;

	for (const CoreMaterial& cm : this->coreMaterials) {
		totalAbsorption += cm.material.SigmaA() * cm.volumeFraction;
	}
	for (const CoreMaterial& cm : this->coreMaterials) {
		if (cm.material.GetRole() == Role::Fuel) {
			fuelAbsorption += cm.material.SigmaA() * cm.volumeFraction;
		}
	}

	if (totalAbsorption == 0.0) {
		return 0.0;
	}
	else {
		return fuelAbsorption / totalAbsorption;
	}
}

double Core::CoreReproductionFactor() const {
	double totalNuSigmaF = 0.0;	// Running total of NuSigmaF of all fuel material 
	double totalSigmaA = 0.0;	// Running total of SigmaA of all fuel material
	for (const CoreMaterial& cm : this->coreMaterials) {
		if (cm.material.GetRole() == Role::Fuel) {	// Checks to see if material is fuel
			totalNuSigmaF += cm.material.NuSigmaF() * cm.volumeFraction;	// Adds current material NuSigmaF to total
			totalSigmaA += cm.material.SigmaA() * cm.volumeFraction;		// Adds current material SigmaA to total
		}
	}

	if (totalSigmaA == 0.0) {
		return 0.0;							// Returns 0 in case of div by zero
	}
	else {
		return totalNuSigmaF / totalSigmaA;	// Returns Reproduction Factor of the core.
	}
}