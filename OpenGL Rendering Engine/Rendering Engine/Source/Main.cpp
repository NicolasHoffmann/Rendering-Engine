// GLFW - Documentation. (o. J.). Abgerufen 9. Juli 2020, von https://www.glfw.org/documentation.html
// GLEW: The OpenGL Extension Wrangler Library. (o. J.). Abgerufen 9. Juli 2020, von http://glew.sourceforge.net/basic.html
// The Cherno. (2020, Februar 12). OpenGL [Video-Datei]. Abgerufen von https://www.youtube.com/playlist?list=PLlrATfBNZ98foTJPJ_Ev03o2oq3-GGOS2

// Include
	#include <GL/glew.h>
	#include <GLFW/glfw3.h>

	#include <iostream>
	#include <fstream>
	#include <string>
	#include <sstream>

	#define ASSERT(x) if (!(x)) __debugbreak();
	#define GLTest(x) glClearError();\
		x;\
		ASSERT(glLogCall(#x, __FILE__, __LINE__))


static void glClearError() {
	while (glGetError() != GL_NO_ERROR);
}

static bool glLogCall(const char* function, const char* file, int line) {
	while (GLenum error = glGetError()) {
		std::cout << std::endl 
			<< "[OpenGL Fehler] (" << error << ") " << std::endl 
			<< "Funktion: "<< function << std::endl 
			<< "Datei: " << file << std::endl 
			<< "Zeile: " << line << std::endl;
		return false;
	}
	return true;
}

struct ShaderProgramSource {
	std::string vertexShaderSource;
	std::string fragmentShaderSource;
};

/*
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

	while (getline(stream, line)) {
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

	return { stringStream[0].str(), stringStream[1].str() };
}
*/

static ShaderProgramSource ParseShader(const std::string& vertexFilepath, const std::string& fragmentFilepath) {
	std::ifstream vertexStream(vertexFilepath);
	std::ifstream fragmentStream(fragmentFilepath);

	enum class ShaderType {
		NONE = -1,
		VERTEX = 0,
		FRAGMENT = 1
	};

	std::stringstream stringStream[2];
	std::string line;
	ShaderType type = ShaderType::NONE;

	while (getline(vertexStream, line)) {
		stringStream[(int)ShaderType::VERTEX] << line << '\n';
	}

	while (getline(fragmentStream, line)) {
		stringStream[(int)ShaderType::FRAGMENT] << line << '\n';
	}

	return { stringStream[0].str(), stringStream[1].str() };
}

// Methode zum Shader-Kompilieren
	static unsigned int CompileShader(unsigned int type, const std::string& source) {
		unsigned int id = glCreateShader(type);
		const char* src = source.c_str(); // gibt die Speicher-Adresse des ersten String-Zeichens zurück
		GLTest(glShaderSource(id, 1, &src, nullptr)); // die Quelle des Shaders wird festgelegt (um welchen Shader geht es (id) , Anzahl der Quellcodes , Pointer die auf den String deuten die den Quellcode für den Shader beinhalten , String längen werden definiert)
		GLTest(glCompileShader(id)); // Shader mit bestimmter ID wird kompiliert

		int status;
		GLTest(glGetShaderiv(id, GL_COMPILE_STATUS, &status)); // gibt einen Parameter aus einem Shader zurück (ID des Shaders , Parameter-Name (hier: der Status der Kompilierung) , Speicher-Adresse für den angefragten Parameter)

		// wenn es es ein Problem beim Kompilieren gab
			if (status == GL_FALSE) {
				int length;
				GLTest(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
				char* message = (char*)alloca(length * sizeof(char)); // Variable für die Message wird mit abgefragter Länge des Info-Log erstellt

				GLTest(glGetShaderInfoLog(id, length, &length, message)); // gibt das Info Log für einen Shader zurück (ID des Shaders , größe des Char Buffers in den das Info Log gespeichert wird , Speicher-Adresse der Länge, Zwischenspeicher (Buffer) für die Message)
				
				std::cout << "Kompilierungsfehler: " << std::endl;
				std::cout << message << std::endl; // Message wird auf der Konsole ausgegeben

				GLTest(glDeleteShader(id)); // da der Shader nicht kompiliert werden konnte, wird er gelöscht

				return 0;
			}

		return id;
	}

// Quellcode der Shader wird übergeben und daraus ein Programm generiert
	static unsigned int CreateShaderProgram(const std::string& vertexShader, const std::string& fragmentShader) {
		unsigned int program = glCreateProgram();
		unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader); // ruft die CompileShader-Methode (oben) auf
		unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader); // ruft die CompileShader-Methode (oben) auf

		// Shader-Programm wird erstellt
			GLTest(glAttachShader(program, vs)); // Shader wird zum Programm-Objekt hinzugefügt
			GLTest(glAttachShader(program, fs)); // Shader wird zum Programm-Objekt hinzugefügt
			GLTest(glLinkProgram(program)); // Das Programm wird zusammengefügt und die angehängten Shader werden zu Executables, die auf dem jeweiligen Prozessor laufen
			GLTest(glValidateProgram(program)); // es wird geprüft, ob sich die Executables des Programms ausfüren lassen

		// Shader können gelöscht werden, da sie nun Teil eines Programms sind
			GLTest(glDeleteShader(vs));
			GLTest(glDeleteShader(fs));

		return program;
	}





// --------------------- M A I N ------------------------


int main(void) {
	GLFWwindow* window;

	// Bibliothek wird initialisiert: Hat es geklappt?
		if (!glfwInit()) {
			return -1;
		}

	// OpenGL Version wird auf 3.3 gesetzt
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Fenster mit OpenGL-Kontext wird generiert
		// Breite, Höhe, Name
			window = glfwCreateWindow(640, 480, "Rendering Engine", NULL, NULL);
			if (!window) {
				glfwTerminate();
				return -1;
			}

	// Rendering Kontext wird erstellt
		glfwMakeContextCurrent(window);
		glfwSwapInterval(1);






	GLenum err = glewInit();

	if (GLEW_OK != err) {
		// Es gab einen Fehler mit glewInit(), der ausgegeben wird
			fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
	}

	else {
		// GLEW Version wird auf der Konsole ausgegeben
			fprintf(stdout, "GLEW %s wird verwendet \n", glewGetString(GLEW_VERSION));

		// Array mit Quadratss-Eckpunkten (X, Y)
			float points[8] = {
				-0.5f, -0.5f,
				 0.5f, -0.5f,
				 0.5f,	0.5f,
				-0.5f,	0.5f,
			};

		// Array das auf die benötigten Eckpunkte verweist (um es als 2 Dreiecke darzustellen)
			unsigned int index[] = {
				0, 1, 2,
				2, 3, 0
			};

		// Vertex Array Objekt
			unsigned int vertexArrayObject;
			GLTest(glGenVertexArrays(1, &vertexArrayObject));
			GLTest(glBindVertexArray(vertexArrayObject));

		// Buffer (Zwischenspeicher)
			// Vertex-Buffer
				unsigned int vertexBuffer;
				GLTest(glGenBuffers(1, &vertexBuffer)); // Generiert eine Anzahl von Buffern und liefert die Adresse als ID zurück

				GLTest(glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer)); // Wählt den aktuell zu benutzenden Buffer aus
					GLTest(glBufferData(GL_ARRAY_BUFFER, 4 * 2 * sizeof(float), points, GL_STATIC_DRAW)); // gibt dem (Array-)Buffer eine festgelegte Anzahl an Bytes und füllt ihn mit Daten (NULL = nicht füllen)
					GLTest(glEnableVertexAttribArray(0)); // Ein Vertex-Attribut mit einem bestimmten Index (hier: 0) wird aktiviert
					GLTest(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0)); // (Index des Attributs (hier: Koordinaten)(Index: 0) ,  wie viele Attribute des Datentyps (hier: float) hat der Vertex (hier: 2) , Datentyp , ist der Inhalt normalisiert , wie viele Byte lang ist ein Vertex (hier: 2 * float-Länge) , am wievielten Byte im Vertex fängt das Attribut an (hier: 0));

			// Index-Buffer
				unsigned int indexBuffer;
				GLTest(glGenBuffers(1, &indexBuffer));

				GLTest(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer));
				GLTest(glBufferData(GL_ELEMENT_ARRAY_BUFFER, 2 * 3 * sizeof(unsigned int), index, GL_STATIC_DRAW));

		// Shader Programm erstellen
			ShaderProgramSource source = ParseShader(
				"resources/shaders/Color/vertex.shader", 
				"resources/shaders/Color/fragment.shader"
			);

			unsigned int shaderProgram = CreateShaderProgram(source.vertexShaderSource, source.fragmentShaderSource);
			GLTest(glUseProgram(shaderProgram));

		// Farbe festlegen
			float r = 0.0f;
			bool forward = true;

			int location = glGetUniformLocation(shaderProgram, "u_Color");
			// glUniform4f(location, r, 1.0f, 0.7f, 1.0f);

		// Ein Loop der durch Schließen des fensters beendet wird
			while (!glfwWindowShouldClose(window)) {

				// Farbe verändert sich
					if (forward == true) {
						r += 0.05f;

						if (r >= 0.99f) {
							forward = false;
						}	
					}
					else if (forward == false) {
						r -= 0.05f;

						if (r <= 0.01f) {
							forward = true;
						}
					}


				// std::cout << r << std::endl;

				// Hier wird gerendert
					glClear(GL_COLOR_BUFFER_BIT);
					glClearError();

					GLTest(glUseProgram(shaderProgram));

					// neue Farbe wird übergeben
						GLTest(glUniform4f(location, r, 1.0f, 0.7f, 1.0f));

						GLTest(glBindVertexArray(vertexArrayObject));
						GLTest(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer));

					// Elemente werden gezeichnet
						GLTest(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));

				// Buffer Swap: Front- und Back-Imagebuffer werden ausgetauscht
					glfwSwapBuffers(window);

				// Ereignisse werden abgestimmt und verarbeitet
					glfwPollEvents();
			}
			GLTest(glDeleteProgram(shaderProgram));

	}

	glfwTerminate();
	return 0;
}