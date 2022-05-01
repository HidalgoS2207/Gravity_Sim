#include "RotMat.h"

RotMatrix::RotMatrix(RotMatrix::RotAxis ax)
	:
	size(3),
	ax(ax)
{
	for (int i = 0; i < size; i++)
	{
		mat.emplace_back();
		for (int j = 0; j < size; j++)
		{
			mat[i].emplace_back();
		}
	}
}

RotMatrix::~RotMatrix()
{}

void RotMatrix::set_all(double val)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			mat[i][j] = val;
		}
	}
}

void RotMatrix::rotate(Vertex3D& v, double ang)
{
	double rad_ang = (ang * PI) / 180.0;

	set_all(0.0);
	set_angle(rad_ang);

	double res[3] = { 0,0,0 };

	res[0] = (v.x * mat[0][0]) + (v.y * mat[0][1]) + (v.z * mat[0][2]);
	res[1] = (v.x * mat[1][0]) + (v.y * mat[1][1]) + (v.z * mat[1][2]);
	res[2] = (v.x * mat[2][0]) + (v.y * mat[2][1]) + (v.z * mat[2][2]);

	v.x = res[0];
	v.y = res[1];
	v.z = res[2];
}

void RotMatrix::set_angle(double ang)
{
	switch (ax)
	{
	case RotMatrix::RotAxis::rx:
	{
		mat[0][0] = 1.0;
		mat[0][1] = 0;
		mat[0][2] = 0;

		mat[1][0] = 0;
		mat[1][1] = cos(ang);
		mat[1][2] = (-1.0)*sin(ang);

		mat[2][0] = 0;
		mat[2][1] = sin(ang);
		mat[2][2] = cos(ang);
	}
	break;
	case RotMatrix::RotAxis::ry:
	{
		mat[0][0] = cos(ang);
		mat[0][1] = 0;
		mat[0][2] = sin(ang);

		mat[1][0] = 0;
		mat[1][1] = 1;
		mat[1][2] = 0;

		mat[2][0] = (-1.0)*sin(ang);
		mat[2][1] = 0;
		mat[2][2] = cos(ang);
	}
	break;
	case RotMatrix::RotAxis::rz:
	{
		mat[0][0] = cos(ang);
		mat[0][1] = (-1.0)*sin(ang);
		mat[0][2] = 0;

		mat[1][0] = sin(ang);
		mat[1][1] = cos(ang);
		mat[1][2] = 0;

		mat[2][0] = 0;
		mat[2][1] = 0;
		mat[2][2] = 1.0;
	}
	break;
	default:
		break;
	}
}

double RotMatrix::get(int r, int c)
{
	return mat[r][c];
}

void RotMatrix::set_val(int r, int c, double val)
{
	mat[r][c] = val;
}