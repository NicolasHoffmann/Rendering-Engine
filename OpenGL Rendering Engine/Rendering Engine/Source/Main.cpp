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

		// Array mit Dreiecks-Eckpunkten
			float points[6] = {
				-0.8f, -0.0f,
				 0.0f,  0.9f,
				 0.0f, -0.7f
			};

		// Buffer
			unsigned int buffer;
			glGenBuffers(1, &buffer); // Generiert eine Anzahl von Buffern und liefert die Adresse als ID zurück


			glBindBuffer(GL_ARRAY_BUFFER, buffer); // Wählt den aktuell zu benutzenden Buffer aus
				glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float) /* alt: sizeof(points) */, points, GL_STATIC_DRAW); // gibt dem (Array-)Buffer eine festgelegte Anzahl an Bytes und füllt ihn mit Daten (NULL = nicht füllen)
				glEnableVertexAttribArray(0); // Ein Vertex-Attribut mit einem bestimmten Index (hier: 0) wird aktiviert
				glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0); // (Index des Attributs (hier: Koordinaten)(Index: 0) ,  wie viele Attribute des Datentyps (hier: float) hat der Vertex (hier: 2) , Datentyp , ist der Inhalt normalisiert , wie viele Byte lang ist ein Vertex (hier: 2 * float-Länge) , am wievielten Byte im Vertex fängt das Attribut an (hier: 0));


		// Ein Loop der durch Schließen des fensters beendet wird
			while (!glfwWindowShouldClose(window)) {

				// Hier wird gerendert
					glClear(GL_COLOR_BUFFER_BIT);
					// --- glColor3f(0.0, 1.0, 0.7);
					// ---glDrawArrays(GL_TRIANGLES, 0, 3);
					// --- glDrawElements(GL_TRIANGLES, 3, )

				// Buffer Swap: Front- und Back-Imagebuffer werden ausgetauscht
					glfwSwapBuffers(window);

				// Ereignisse werden abgestimmt und verarbeitet
					glfwPollEvents();
			}

	}

	glfwTerminate();
	return 0;
}