#include "Camera.h"

Camera::Camera()
{
	m_projection = {};
	m_view = {};
}

Camera::Camera(Resolution _screenResolution)
{
	//Projection matrix
	m_projection = glm::perspective(glm::radians(45.0f), // 45deg FOV
									(float)_screenResolution.m_width/(float)_screenResolution.m_height, // 4:3 ratio
									0.1f, //display range : 0.1 unit <-> 100 units
									1000.f);

	// For an ortho camera:
	//glm::mat4 Projection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, 0.0f, 100.0f); // In world coordinates

	// Camera matrix
	m_view = glm::lookAt(
		glm::vec3(100, 100, 100),	// camera position in world space
		glm::vec3(0, 0, 0),			// camera looks at origin
		glm::vec3(0, 1, 0)			// head is up (set to 0 -1 0 to look upside down)
	);
}

Camera::~Camera()
{
}
