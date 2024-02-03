#include "Vec3.h"
#include <math.h>

Vec3::Vec3(float _x, float _y, float _z) 
{
	m_x = _x;
	m_y = _y;
	m_z = _z;
}

Vec3 Vec3::Add(Vec3 _v1, Vec3 _v2) 
{
	return Vec3(_v1.m_x + _v2.m_x, _v1.m_y + _v2.m_y, _v1.m_z + _v2.m_z);
}

Vec3 Vec3::Sub(Vec3 _v1, Vec3 _v2)
{
	return Vec3(_v1.m_x - _v2.m_x, _v1.m_y - _v2.m_y, _v1.m_z - _v2.m_z);
}

Vec3 Vec3::Mul(Vec3 _v, float _scalar) 
{
	return Vec3(_v.m_x * _scalar, _v.m_y * _scalar, _v.m_z * _scalar);
}

Vec3 Vec3::Div(Vec3 _v, float _scalar)
{
	return Vec3(_v.m_x / _scalar, _v.m_y / _scalar, _v.m_z / _scalar);
}

float Vec3::Dist(Vec3 _v1, Vec3 _v2)
{
	return sqrt(pow((_v2.m_x - _v1.m_x), 2.0f) + pow((_v2.m_y - _v1.m_y), 2.0f) + pow((_v2.m_z - _v1.m_z), 2.0f));
}

Vec3 Vec3::Cross(Vec3 _v1, Vec3 _v2)
{
	float crossX = _v1.m_y * _v2.m_z - _v1.m_z * _v2.m_y;
	float crossY = _v1.m_z * _v2.m_x - _v1.m_x * _v2.m_z;
	float crossZ = _v1.m_x * _v2.m_y - _v1.m_y * _v2.m_x;

	return Vec3(crossX, crossY, crossZ);
}

System::String^ Vec3::ToString()
{
	//std::string res = "X = " + std::to_string(m_x) + "; Y = " + std::to_string(m_y) + "; Z = " + std::to_string(m_z);
	return gcnew System::String("X = " + m_x.ToString() + "; Y = " + m_y.ToString() + "; Z = " + m_z.ToString());
}