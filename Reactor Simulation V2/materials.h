#pragma once

#include <string>
#include <vector>

// Constants
const double AVOGADRO = 6.022e23;			// atoms/mole
const double BARN_TO_CM2 = 1.0e-24;			// 1 barn = 1e-24 cm^2

struct Nuclide {
	std::string name;		// Name of the nuclide
	double atomicMass;		// gram atomic weight, g/mole
	double sigmaA;			// microscopic absorption cross section (barns)
	double sigmaF;			// microscopic fission cross section (barns)
	double sigmaS;			// microscopic scattering cross section (barns)
	double nu;				// Average neutrons released per fission
};

// Nuclide data library: thermal (0.0253 eV) values.
// U-235, U-238, Xe-135, Sm-149, Fe, Al, Si values are from DOE-HDBK-1019.
// Xe-135 and Sm-149 scattering is negligible next to absorption and is set to 0.
//                            name       atomicMass  sigmaA     sigmaF  sigmaS  nu
namespace Nuclides {
	const Nuclide H1		{ "H-1",	1.008,		0.332,		0.0,	20.5,	0.0 };
	const Nuclide H2		{ "H-2",	2.014,		0.00052,	0.0,	3.39,	0.0 };
	const Nuclide O16		{ "O-16",	15.995,		0.00019,	0.0,	3.76,	0.0 };
	const Nuclide B10		{ "B-10",	10.013,		3840.0,		0.0,	2.2,	0.0 };
	const Nuclide C12		{ "C-12",	12.011,		0.0035,		0.0,	4.7,	0.0 };
	const Nuclide Al27		{ "Al-27",	26.9815,	0.23,		0.0,	1.49,	0.0 };
	const Nuclide Si		{ "Si",		28.0855,	0.16,		0.0,	2.20,	0.0 };
	const Nuclide Fe		{ "Fe",		55.847,		2.56,		0.0,	11.35,	0.0 };
	const Nuclide Zr		{ "Zr",		91.224,		0.185,		0.0,	6.4,	0.0 };
	const Nuclide U235		{ "U-235",	235.044,	694.0,		582.0,	15.0,	2.42 };
	const Nuclide U238		{ "U-238",	238.051,	2.71,		0.0,	9.3,	0.0 };
	const Nuclide Xe135		{ "Xe-135",	134.907,	2.6e6,		0.0,	0.0,	0.0 };
	const Nuclide Sm149		{ "Sm-149",	148.917,	4.1e4,		0.0,	0.0,	0.0 };
}

struct Constituent {
	Nuclide nuclide;
	double amount;				// weight fraction
	double atomDensity = 0.0;	// N, atoms/cm^3 (calculated by Material)
};

class Material {
private:
	std::string name;
	double density;								// g/cm^3
	std::vector<Constituent> constituents;

public:
	Material(std::string n, double rho, std::vector<Constituent> parts);

	double SigmaA() const;
	double SigmaS() const;
	double SigmaF() const;
	double NuSigmaF() const;
	double MeanFreePathA() const;
	double MeanFreePathS() const;

	double AtomDensity(std::string nuclideName) const;
};