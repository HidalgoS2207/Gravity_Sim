#pragma once

#include <vector>

#include "Vertex3D.h"

constexpr auto PI = 3.14159265358979323846;

class RotMatrix
{
public:
	enum RotAxis
	{
		rx,
		ry,
		rz
	};
public:
	RotMatrix(RotMatrix::RotAxis ax);
	~RotMatrix();

	double get(int r, int c);
	void set_val(int r, int c,double val);

	void rotate(Vertex3D& v, double ang);
private:
	void set_angle(double ang);
	void set_all(double val);

	std::vector< std::vector<double> > mat;

	int size;

	const RotAxis ax;
};


