#include "materials.h"

Material::Material(std::string n, double rho, std::vector<Constituent> parts) : name(n), density(rho), constituents(parts) {
	// N = amount * density * NA / Atomic Mass
	for (Constituent& c : this->constituents) {
		c.atomDensity = c.amount * rho * AVOGADRO / c.nuclide.atomicMass;
	}
}

double Material::AtomDensity(std::string nuclideName) const {
	
	for (const Constituent& c : this->constituents) {
		if (c.nuclide.name == nuclideName) {
			return c.atomDensity;
		}
	}

	return 0.0;
}

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

double Material::MeanFreePathA() const {
	double total = 1 / SigmaA();
	return total;
}

double Material::MeanFreePathS() const {
	double total = 1 / SigmaS();
	return total;
}