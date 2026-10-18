#include "materials.h"
// Constructors
Material::Material(std::string n, double rho, std::vector<Constituent> parts, Role r, FractionType type) : name(n), density(rho), constituents(parts), role(r) {
	if (type == FractionType::ByWeight) {
		// N = amount * density * NA / Atomic Mass
		for (Constituent& c : this->constituents) {
			c.atomDensity = c.amount * this->density * AVOGADRO / c.nuclide.atomicMass;
		}
	}
	else
	{
		double moleculeMass = 0.0;
		for (const Constituent& c : this->constituents) {
			moleculeMass += c.amount * c.nuclide.atomicMass;
		}
		for (Constituent& c : this->constituents) {
			c.atomDensity = c.amount * this->density * AVOGADRO / moleculeMass;
		}
	}
}

// Getters
std::string Material::GetName() const { return this->name; }

double Material::GetDensity() const { return this->density; }

Role Material::GetRole() const { return this->role; }

// Macroscopic Cross Sections (cm^-1)
double Material::SigmaA() const {
	double total = 0.0;
	for (const Constituent& c : this->constituents) {
		total += c.atomDensity * c.nuclide.sigmaA * BARN_TO_CM2;
	}
	return total;
}

double Material::SigmaS() const {
	double total = 0.0;
	for (const Constituent& c : this->constituents) {
		total += c.atomDensity * c.nuclide.sigmaS * BARN_TO_CM2;
	}
	return total;
}

double Material::SigmaF() const {
	double total = 0.0;
	for (const Constituent& c : this->constituents) {
		total += c.atomDensity * c.nuclide.sigmaF * BARN_TO_CM2;
	}
	return total;
}

double Material::NuSigmaF() const {
	double total = 0.0;
	for (const Constituent& c : this->constituents) {
		total += c.atomDensity * c.nuclide.sigmaF * c.nuclide.nu * BARN_TO_CM2;
	}
	return total;
}

// Mean Free Path (cm): Average distance traveled before interaction
double Material::MeanFreePathA() const {
	double total = 1 / SigmaA();
	return total;
}

double Material::MeanFreePathS() const {
	double total = 1 / SigmaS();
	return total;
}

double Material::AtomDensity(std::string nuclideName) const {
	for (const Constituent& c : this->constituents) {
		if (c.nuclide.name == nuclideName) {
			return c.atomDensity;
		}
	}
	return 0.0;
}

double Material::ReproductionFactor() const{
	if (SigmaA() == 0) {
		return 0.0;
	}
	else {
		return NuSigmaF() / SigmaA();
	}
}