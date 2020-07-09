// Jayanam Games. (2018, Mai 5). OpenGL C++ Tutorial : Shaders. Abgerufen 9. Juli 2020, von https://www.patreon.com/posts/opengl-c-shaders-17380566



#pragma once

#include <string>

// Utitlity class to load, compile and attach a vertex- and fragment shader to a program
class ShaderUtil
{

private: 
	unsigned int mProgramId;

	unsigned int GetCompiledShader(unsigned int shader_type, const std::string& shader_source);

public:
	ShaderUtil() {}
	~ShaderUtil() {}

	// Load a vertex and a fragment shader from file
	bool Load(const std::string& vertexShaderFile, const std::string& fragmentShaderFile);

	// Use the program
	void Use();

	// Delete the program
	void Delete();



};

