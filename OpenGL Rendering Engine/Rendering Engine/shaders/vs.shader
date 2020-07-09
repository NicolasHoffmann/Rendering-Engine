// Jayanam Games. (2018, Mai 5). OpenGL C++ Tutorial : Shaders. Abgerufen 9. Juli 2020, von https://www.patreon.com/posts/opengl-c-shaders-17380566


#version 400

in vec4 position;

void main()
{
   gl_Position = position;
}