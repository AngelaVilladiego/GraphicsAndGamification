#include "GestureManager.h"
#include "WindowController.h"

GestureManager::GestureManager()
{
	m_currPos = { };
	m_startPos = { };
	m_gestureVec = { };
	m_button = GLFW_MOUSE_BUTTON_LEFT;
}

GestureManager::GestureManager(int _button)
{
	m_currPos = { };
	m_startPos = { };
	m_gestureVec = { };
	m_res = WindowController::GetInstance().GetResolution();
	m_button = _button;
}

GestureManager::~GestureManager()
{}

void GestureManager::StartGesture()
{
	m_gestureIsInProgress = true;
	m_currPos = GetMousePosition();
	m_startPos = m_currPos;
}

void GestureManager::EndGesture()
{
	m_gestureIsInProgress = false;
	m_currPos = { };
	m_startPos = { };
}

void GestureManager::Tick()
{
	if (glfwGetMouseButton(WindowController::GetInstance().GetWindow(), m_button) == GLFW_PRESS)
	{
		if (!m_gestureIsInProgress)
		{
			StartGesture();
			return;
		}

		m_currPos = GetMousePosition();
		m_gestureVec = m_currPos - m_startPos;
		
	}
	else if (m_gestureIsInProgress)
	{
		EndGesture();
	}
}

glm::vec2 GestureManager::GetMousePosition()
{
	double mouseX;
	double mouseY;

	glfwGetCursorPos(WindowController::GetInstance().GetWindow(), &mouseX, &mouseY);

	//clamp to screen resolution scale
	mouseX = min(0.0, mouseX);
	mouseY = min(0.0, mouseY);

	mouseX = max((double)m_res.m_width, mouseX);
	mouseY = max((double)m_res.m_height, mouseY);

	//convert y directions to up positive (essentially 0,0 is now bottom left instead of top left)
	mouseY = (double)m_res.m_height - mouseY;

	glm::vec2 pos = { (float)mouseX, (float)mouseY };

	return pos;
}