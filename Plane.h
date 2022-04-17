#pragma once

#include "Vertex3D.h"

class Plane
{
public:
	Plane(Vertex3D normal_vec,Vertex3D point);
	~Plane();

	Vertex3D& get_point();
	Vertex3D& get_normal();
private:
	Vertex3D normal_vec;
	Vertex3D point;
};