#ifndef VEC3_H
#define VEC3_H

class Vec3
{
public:
	// Constructors / Destructors
	Vec3(float _x, float _y, float _z);

	// Methods
	static Vec3 Add(Vec3 _v1, Vec3 _v2);
	static Vec3 Sub(Vec3 _v1, Vec3 _v2);
	static Vec3 Mul(Vec3 _v, float _scalar);
	static Vec3 Div(Vec3 _v, float _scalar);
	static float Dist(Vec3 _v1, Vec3 _v2);
	static Vec3 Cross(Vec3 _v1, Vec3 _v3);

	System::String^ ToString();

private:
	// Members
	float m_x;
	float m_y;
	float m_z;
};

#endif // VEC3_H