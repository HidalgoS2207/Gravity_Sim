#include "Plane.h"

Plane::Plane(Vertex3D normal_vec, Vertex3D point)
	:
	normal_vec(normal_vec),
	point(point)
{
}

Plane::~Plane()
{
}

Vertex3D& Plane::get_point()
{
	return point;
}

Vertex3D& Plane::get_normal()
{
	return normal_vec;
}
