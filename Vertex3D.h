#pragma once

class Vertex3D
{
public:
	Vertex3D();
	Vertex3D(const Vertex3D& v);
	~Vertex3D();

	double x;
	double y;
	double z;

	void reset();
	void set_values(double x,double y, double z);
private:

};