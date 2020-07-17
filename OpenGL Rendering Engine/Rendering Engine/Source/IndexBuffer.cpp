

// Include
#include "IndexBuffer.h"
#include "Renderer.h"


IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count) : Count(count){
	GLTest(glGenBuffers(1, &RendererID));
	GLTest(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, RendererID));
	GLTest(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW));
}

IndexBuffer::~IndexBuffer() {
	GLTest(glDeleteBuffers(1, &RendererID));
}

void IndexBuffer::Bind() const {
	GLTest(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, RendererID)); // Wählt diesen Buffer als den aktuell zu benutzenden Buffer aus
}

void IndexBuffer::Unbind() const {
	GLTest(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0)); // Wählt KEINEN Buffer als aktuell zu benutzenden Buffer aus
}