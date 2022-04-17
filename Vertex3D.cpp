#include "Vertex3D.h"

Vertex3D::Vertex3D()
	:
	x(0.0),
	y(0.0),
	z(0.0)
{}

Vertex3D::Vertex3D(const Vertex3D & v)
{
	this->x = v.x;
	this->y = v.y;
	this->z = v.z;
}

Vertex3D::~Vertex3D()
{
}

void Vertex3D::reset()
{
	x = 0.0;
	y = 0.0;
	z = 0.0;
}

void Vertex3D::set_values(double x, double y, double z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}
