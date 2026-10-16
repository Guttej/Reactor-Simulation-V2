#pragma once

enum class Shape {
	Sphere,
	Cylinder,
	Cube,
	None
};

class Core
{
private:
	Shape shape;
	double volume;
	double sixFactor[6];
	double keff;

public:
	Core();
	Core(Shape s, double v);

	Shape GetShape() const;
	double GetVolume() const;

	void SetShape(Shape s);
	void SetVolume(double v);

	void BuildCore();
	void UpdateCore();
};