#pragma once

#ifndef STANDARD_INCLUDES_H
#define STANDARD_INCLUDES_H

#define GLM_ENABLE_EXPERIMENTAL

//include standard headers
#include <vector>
#include <map>
#include <string>
#include <fstream>
#include <iostream>

//windows specific includes and defines
#ifdef _WIN32
#include <Windows.h>
#define M_ASSERT(_cond, _msg) \
	if(!(_cond)) { OutputDebugStringA(_msg); std::abort(); glfwTerminate(); }
#endif

//Open GL/Helper headers
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtc/matrix_transform.hpp> // View / Projection

// Font Includes
#include <ft2build.h>
#include FT_FREETYPE_H

#include  "Resolution.h"
#include "Singleton.h"

using namespace std;

#endif // STANDARD_INCLUDES_H