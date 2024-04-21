#include "Vec3ToString.h"
#include <iomanip>

std::string vec3_to_string(const glm::vec3& vec)
{
	std::stringstream stream;
	stream << std::fixed << std::setprecision(6);
	stream << "{vec3(" << (double)vec.x << ", " << (double)vec.y << ", " << (double)vec.z << ")}";
	return stream.str();
}