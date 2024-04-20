#include "FPSCounter.h"

FPSCounter::FPSCounter()
{
	m_fps = 0;
	m_frameCount = 0;
	lastTime = glfwGetTime();
}

FPSCounter::~FPSCounter()
{}

void FPSCounter::Tick()
{
	double currentTime = glfwGetTime();
	m_frameCount++;

	if (currentTime - lastTime >= 1.0)
	{
		m_fps = m_frameCount;
		m_frameCount = 0;
		lastTime += 1.0;
	}
}