#pragma once

#include <GL/glew.h>

#define ASSERT(x) if (!(x)) __debugbreak();
#define GLTest(x) glClearError();\
		x;\
		ASSERT(glLogCall(#x, __FILE__, __LINE__))


void glClearError();

bool glLogCall(const char* function, const char* file, int line);
