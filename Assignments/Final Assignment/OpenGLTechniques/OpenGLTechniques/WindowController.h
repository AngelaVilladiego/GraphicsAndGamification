#ifndef WINDOW_CONTROLLER_H
#define WINDOW_CONTROLLER_H

#include "StandardIncludes.h"

class WindowController : public Singleton<WindowController>
{
public:
	//Constructors / Destructors
	WindowController();
	virtual ~WindowController();

	//Accessors
	GLFWwindow* GetWindow(bool fullscreen) { if (m_window == nullptr) { NewWindow(fullscreen); } return m_window; }
	GLFWwindow* GetWindow() { if (m_window == nullptr) { NewWindow(false); } return m_window; }

	//Methods
	void NewWindow(bool fullscreen);
	void SetWindowFullscreen();
	void SetWindowTitle(string title);
	Resolution GetResolution();

private:
	//Members
	GLFWwindow* m_window;
};

#endif // WINDOW_CONTROLLER_H