#include "Camera.h"

Camera::Camera()
{
	m_projection = glm::mat4();
	m_view = glm::mat4();
	m_position = { };
	m_lookAt = glm::vec3();
	m_rotation = glm::vec3();
	m_angle = 0;
}

Camera::Camera(Resolution _screenResolution)
{
	m_position = { 0, 0, 5 };
	m_lookAt = { 0, 0, 0 };
	m_rotation = { 0, 0, 0 };
	m_angle = 0;

	//Projection matrix
	m_projection = glm::perspective(glm::radians(45.0f), // 45deg FOV
		(float)_screenResolution.m_width / (float)_screenResolution.m_height, // 4:3 ratio
		0.1f, //display range : 0.1 unit <-> 100 units
		1000.0f);

	// Camera matrix
	m_view = glm::lookAt(
		m_position,					// camera position in world space
		m_lookAt,					// camera looks at origin
		glm::vec3(0, 1, 0)			// head is up (set to 0 -1 0 to look upside down)
	);
}

Camera::~Camera()
{
}