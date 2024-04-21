#ifndef GESTUREMANAGER_H
#define GESTUREMANAGER_H

#include "StandardIncludes.h"

class GestureManager
{
public:

	// Constructors / Destructors
	GestureManager(int _button);
	GestureManager();
	virtual ~GestureManager();

	// Accessors
	bool IsInProgress() { return m_gestureIsInProgress; }

	// Methods
	glm::vec2 GetGestureVector() { return m_gestureVec; }
	void Tick();
	
private:
	glm::vec2 m_currPos;
	glm::vec2 m_startPos;
	glm::vec2 m_gestureVec;
	bool m_gestureIsInProgress;
	Resolution m_res;
	int m_button;

	glm::vec2 GetMousePosition();
	void StartGesture();
	void EndGesture();
};
#endif // GESTUREMANAGER_H
