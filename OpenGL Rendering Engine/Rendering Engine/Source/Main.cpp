// GLFW - Documentation. (o. J.). Abgerufen 9. Juli 2020, von https://www.glfw.org/documentation.html
// GLEW: The OpenGL Extension Wrangler Library. (o. J.). Abgerufen 9. Juli 2020, von http://glew.sourceforge.net/basic.html

// Include
	#include <GL/glew.h>
	#include <GLFW/glfw3.h>

	#include <iostream>

	#include "ShaderUtil.h"



int main(void) {
	GLFWwindow* window;

	// Bibliothek wird initialisiert
		if (!glfwInit())
			return -1;

	// Fenster mit OpenGL-Kontext wird generiert
		// Breite, Höhe, Name
			window = glfwCreateWindow(640, 480, "Rendering Engine", NULL, NULL);
			if (!window) {
				glfwTerminate();
				return -1;
			}


	glfwMakeContextCurrent(window);

	GLenum err = glewInit();

	if (GLEW_OK != err) {
		// Es gab einen Fehler mit glewInit(), der ausgegeben wird
			fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
	}

	else {
		// GLEW Version wird auf der Konsole ausgegeben
			fprintf(stdout, "GLEW %s wird verwendet \n", glewGetString(GLEW_VERSION));

		ShaderUtil shaderUtil;
		shaderUtil.Load("shaders/vs.shader", "shaders/fs.shader");

		// Eckpunkte des Dreiecks als Float
			float points[6] = {
				-0.8f, -0.5f,
				0.0f, 0.9f,
				0.5f, -0.7f
			};

		unsigned int buffer;

		glGenBuffers(1, &buffer);
		glBindBuffer(GL_ARRAY_BUFFER, buffer);
		glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), points, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

		// Ein Loop der durch Schließen des fensters beendet wird
			while (!glfwWindowShouldClose(window)) {

				// Hier wird gerendert
					glClear(GL_COLOR_BUFFER_BIT);

					glDrawArrays(GL_TRIANGLES, 0, 3);

				// Buffer Swap: Front- und Back-Imagebuffer werden ausgetauscht
					glfwSwapBuffers(window);

				// Ereignisse werden abgestimmt und verarbeitet
					glfwPollEvents();
			}

			shaderUtil.Delete();

	}

	glfwTerminate();
	return 0;
}