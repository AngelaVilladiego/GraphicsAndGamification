#include "Triangle.h"

std::vector<GLfloat> Triangle::GetVerticesAtPosition(GLfloat pos_x, GLfloat pos_y, GLfloat pos_z)
{
	return {
		/*		x			y				z		*/	
		pos_x,			pos_y + float(sqrt(3) / 2),		pos_z,
		pos_x - 1.0f,	pos_y - float(sqrt(3) / 2),		pos_z,
		pos_x + 1.0f,	pos_y - float(sqrt(3) / 2),		pos_z
	};
}

