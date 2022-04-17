#include "Vertex3D.h"

Vertex3D::Vertex3D()
	:
	x(0.0),
	y(0.0),
	z(0.0)
{}

Vertex3D::~Vertex3D()
{
}

void Vertex3D::reset()
{
	x = 0.0;
	y = 0.0;
	z = 0.0;
}
