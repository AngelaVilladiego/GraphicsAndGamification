#ifndef FPSCOUNTER_H
#define FPSCOUNTER_H

#include "StandardIncludes.h"

class FPSCounter
{
public:

	// Constructors / Destructors
	FPSCounter();
	virtual ~FPSCounter();

	// Methods
	void Tick();

	// Accessors
	int GetFPS() { return m_fps; }

private:
	int m_fps;
	int m_frameCount;
	double lastTime;
};
#endif // FPSCOUNTER_H

