

// Include
	#include "Renderer.h"
	#include <iostream>

void glClearError() {
	while (glGetError() != GL_NO_ERROR);
}

bool glLogCall(const char* function, const char* file, int line) {
	while (GLenum error = glGetError()) {
		std::cout << std::endl
			<< "[OpenGL Fehler] (" << error << ") " << std::endl
			<< "Funktion: " << function << std::endl
			<< "Datei: " << file << std::endl
			<< "Zeile: " << line << std::endl;
		return false;
	}
	return true;
}