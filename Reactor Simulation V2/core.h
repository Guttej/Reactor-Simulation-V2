#pragma once
#include "materials.h"

enum class Shape {
	Sphere,
	Cylinder,
	Cube,
	None
};

struct CoreMaterial
{
	Material material;
	double volumeFraction;
};

class Core
{
public:
	enum SixFactor {
		FastNonLeakage,
		ResonanceEscape,
		ThermalNonLeakage,
		ThermalUtilization,
		Reproduction,
		FastFission,
		NumFactors
	};

private:
	Shape shape;
	double volume;
	double sixFactor[6];
	double keff;
	std::vector<CoreMaterial> coreMaterials;

public:
	// Constructors
	Core();
	Core(Shape s, double v);

	// Getters
	Shape GetShape() const;
	double GetVolume() const;
	
	// Setters
	void SetShape(Shape s);
	void SetVolume(double v);
	void AddCoreMaterial(const Material& m, double v);

	void BuildCore();
	void UpdateCore();

	double ThermalUtilizationFactor() const;
	double CoreReproductionFactor() const;
	double CoreSlowingDownPower() const;
};