// GLFW - Documentation. (o. J.). Abgerufen 9. Juli 2020, von https://www.glfw.org/documentation.html
// GLEW: The OpenGL Extension Wrangler Library. (o. J.). Abgerufen 9. Juli 2020, von http://glew.sourceforge.net/basic.html

// Include
	#include <GL/glew.h>
	#include <GLFW/glfw3.h>

	#include <iostream>



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

	// Rendering Kontext wird erstellt
		glfwMakeContextCurrent(window);

	GLenum err = glewInit();

	if (GLEW_OK != err) {
		// Es gab einen Fehler mit glewInit(), der ausgegeben wird
			fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
	}

	else {
		// GLEW Version wird auf der Konsole ausgegeben
			fprintf(stdout, "GLEW %s wird verwendet \n", glewGetString(GLEW_VERSION));


		// Ein Loop der durch Schließen des fensters beendet wird
			while (!glfwWindowShouldClose(window)) {

				// Hier wird gerendert
					glClear(GL_COLOR_BUFFER_BIT);

					glColor3f(0.0, 1.0, 0.7);

					glBegin(GL_TRIANGLES);
					glVertex2f(0.8f, -0.0f);
					glVertex2f(0.0f, 0.9f);
					glVertex2f(0.0f, -0.7f);
					glEnd();

					glBegin(GL_TRIANGLES);
					glVertex2f(-0.8f, -0.0f);
					glVertex2f(0.0f, 0.9f);
					glVertex2f(0.0f, -0.7f);
					glEnd();

				// Buffer Swap: Front- und Back-Imagebuffer werden ausgetauscht
					glfwSwapBuffers(window);

				// Ereignisse werden abgestimmt und verarbeitet
					glfwPollEvents();
			}

	}

	glfwTerminate();
	return 0;
}