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
		(float)_screenResolution.m_width / (float)_screenResolution.m_height, 
		0.1f, //display range
		1000.f);


	// Camera matrix
	m_view = glm::lookAt(
		glm::vec3(0, 0, 50),		// camera position in world space
		glm::vec3(0, 0, 0),			// camera looks at origin
		glm::vec3(0, 1, 0)			// head is up
	);
}

Camera::~Camera()
{
}
