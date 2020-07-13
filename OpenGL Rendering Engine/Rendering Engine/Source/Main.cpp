// GLFW - Documentation. (o. J.). Abgerufen 9. Juli 2020, von https://www.glfw.org/documentation.html
// GLEW: The OpenGL Extension Wrangler Library. (o. J.). Abgerufen 9. Juli 2020, von http://glew.sourceforge.net/basic.html

// Include
	#include <GL/glew.h>
	#include <GLFW/glfw3.h>

	#include <iostream>
	#include <fstream>
	#include <string>
	#include <sstream>


struct ShaderProgramSource {
	std::string vertexShaderSource;
	std::string fragmentShaderSource;
};

static ShaderProgramSource ParseShader(const std::string& filepath) {
	std::ifstream stream(filepath);

	enum class ShaderType {
		NONE = -1, 
		VERTEX = 0, 
		FRAGMENT = 1
	};

	std::stringstream stringStream[2];
	std::string line;
	ShaderType type = ShaderType::NONE;

	std::cout << "1" << std::endl;
	while (getline(stream, line)) {
		std::cout << "2" << std::endl;
		if (line.find("#shader") != std::string::npos) {
			if (line.find("vertex") != std::string::npos) {
				type = ShaderType::VERTEX;
			}
			else if (line.find("fragment") != std::string::npos) {
				type = ShaderType::FRAGMENT;
			}
		}
		else {
			stringStream[(int)type] << line << '\n';
		}

	}
	std::cout << "3" << std::endl;

	return { stringStream[0].str(), stringStream[1].str() };
}

// Methode zum Shader-Kompilieren
	static unsigned int CompileShader(unsigned int type, const std::string& source) {
		unsigned int id = glCreateShader(type);
		const char* src = source.c_str(); // gibt die Speicher-Adresse des ersten String-Zeichens zur�ck
		glShaderSource(id, 1, &src, nullptr); // die Quelle des Shaders wird festgelegt (um welchen Shader geht es (id) , Anzahl der Quellcodes , Pointer die auf den String deuten die den Quellcode f�r den Shader beinhalten , String l�ngen werden definiert)
		glCompileShader(id); // Shader mit bestimmter ID wird kompiliert

		int status;
		glGetShaderiv(id, GL_COMPILE_STATUS, &status); // gibt einen Parameter aus einem Shader zur�ck (ID des Shaders , Parameter-Name (hier: der Status der Kompilierung) , Speicher-Adresse f�r den angefragten Parameter)

		// wenn es es ein Problem beim Kompilieren gab
			if (status == GL_FALSE) {
				int length;
				glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
				char* message = (char*)alloca(length * sizeof(char)); // Variable f�r die Message wird mit abgefragter L�nge des Info-Log erstellt

				glGetShaderInfoLog(id, length, &length, message); // gibt das Info Log f�r einen Shader zur�ck (ID des Shaders , gr��e des Char Buffers in den das Info Log gespeichert wird , Speicher-Adresse der L�nge, Zwischenspeicher (Buffer) f�r die Message)
				
				std::cout << "Kompilierungsfehler: " << std::endl;
				std::cout << message << std::endl; // Message wird auf der Konsole ausgegeben

				glDeleteShader(id); // da der Shader nicht kompiliert werden konnte, wird er gel�scht

				return 0;
			}

		return id;
	}

// Quellcode der Shader wird �bergeben und daraus ein Programm generiert
	static unsigned int CreateShaderProgram(const std::string& vertexShader, const std::string& fragmentShader) {
		unsigned int program = glCreateProgram();
		unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader); // ruft die CompileShader-Methode (oben) auf
		unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader); // ruft die CompileShader-Methode (oben) auf

		// Shader-Programm wird erstellt
			glAttachShader(program, vs); // Shader wird zum Programm-Objekt hinzugef�gt
			glAttachShader(program, fs); // Shader wird zum Programm-Objekt hinzugef�gt
			glLinkProgram(program); // Das Programm wird zusammengef�gt und die angeh�ngten Shader werden zu Executables, die auf dem jeweiligen Prozessor laufen
			glValidateProgram(program); // es wird gepr�ft, ob sich die Executables des Programms ausf�ren lassen

		// Shader k�nnen gel�scht werden, da sie nun Teil eines Programms sind
			glDeleteShader(vs);
			glDeleteShader(fs);

		return program;
	}


int main(void) {
	GLFWwindow* window;

	// Bibliothek wird initialisiert
		if (!glfwInit())
			return -1;

	// Fenster mit OpenGL-Kontext wird generiert
		// Breite, H�he, Name
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

		// Array mit Dreiecks-Eckpunkten (X, Y)
			float points[6] = {
				-0.8f, -0.0f,
				 0.0f,  0.9f,
				 0.0f, -0.7f
			};

		// Buffer (Zwischenspeicher)
			unsigned int buffer;
			glGenBuffers(1, &buffer); // Generiert eine Anzahl von Buffern und liefert die Adresse als ID zur�ck


			glBindBuffer(GL_ARRAY_BUFFER, buffer); // W�hlt den aktuell zu benutzenden Buffer aus
				glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float) /* alt: sizeof(points) */, points, GL_STATIC_DRAW); // gibt dem (Array-)Buffer eine festgelegte Anzahl an Bytes und f�llt ihn mit Daten (NULL = nicht f�llen)
				glEnableVertexAttribArray(0); // Ein Vertex-Attribut mit einem bestimmten Index (hier: 0) wird aktiviert
				glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0); // (Index des Attributs (hier: Koordinaten)(Index: 0) ,  wie viele Attribute des Datentyps (hier: float) hat der Vertex (hier: 2) , Datentyp , ist der Inhalt normalisiert , wie viele Byte lang ist ein Vertex (hier: 2 * float-L�nge) , am wievielten Byte im Vertex f�ngt das Attribut an (hier: 0));


		// Shader Programm erstellen
			ShaderProgramSource source = ParseShader("resources/shaders/RedColor.shader");

			std::cout << "VERTEX" << std::endl;
			std::cout << source.vertexShaderSource << std::endl;
			std::cout << "FRAGMENT" << std::endl;
			std::cout << source.fragmentShaderSource << std::endl;

			unsigned int shaderProgram = CreateShaderProgram(source.vertexShaderSource, source.fragmentShaderSource);
			glUseProgram(shaderProgram);

		// Ein Loop der durch Schlie�en des fensters beendet wird
			while (!glfwWindowShouldClose(window)) {

				// Hier wird gerendert
					glClear(GL_COLOR_BUFFER_BIT);

					glDrawArrays(GL_TRIANGLES, 0, 3);
					// --- glDrawElements(GL_TRIANGLES, 3, )

				// Buffer Swap: Front- und Back-Imagebuffer werden ausgetauscht
					glfwSwapBuffers(window);

				// Ereignisse werden abgestimmt und verarbeitet
					glfwPollEvents();
			}
			glDeleteProgram(shaderProgram);

	}

	glfwTerminate();
	return 0;
}