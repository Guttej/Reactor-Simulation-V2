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

	for (int i = 0; i < 6; ++i) {
		tmpDouble *= sixFactor[i];
	}
	this->keff = tmpDouble;
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
