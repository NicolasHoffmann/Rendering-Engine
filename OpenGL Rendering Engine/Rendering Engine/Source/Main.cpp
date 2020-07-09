//GLFW - Documentation. (o. J.). Abgerufen 9. Juli 2020, von https://www.glfw.org/documentation.html
//GLEW: The OpenGL Extension Wrangler Library. (o. J.). Abgerufen 9. Juli 2020, von http://glew.sourceforge.net/basic.html

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	/* width, height, name*/
	window = glfwCreateWindow(640, 480, "Rendering Engine", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		/* Problem: glewInit failed, something is seriously wrong. */
		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
	}
	fprintf(stdout, "GLEW %s wird verwendet \n", glewGetString(GLEW_VERSION));




	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}