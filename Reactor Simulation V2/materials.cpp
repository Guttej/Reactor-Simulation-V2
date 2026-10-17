#include "materials.h"

Material::Material(std::string n, double rho, std::vector<Constituent> parts) : name(n), density(rho), constituents(parts) {
	// N = amount * density * NA / Atomic Mass
	for (Constituent& c : this->constituents) {
		c.atomDensity = c.amount * rho * AVOGADRO / c.nuclide.atomicMass;
	}
}

double Material::AtomDensity(std::string nuclideName) const {
	
	for (Constituent c : this->constituents) {
		if (c.nuclide.name == nuclideName) {
			return c.atomDensity;
		}
	}
}