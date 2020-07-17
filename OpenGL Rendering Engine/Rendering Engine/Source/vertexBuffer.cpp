

// Include
	#include "VertexBuffer.h"
	#include "Renderer.h"


VertexBuffer::VertexBuffer(const void* data, unsigned int size) {
	GLTest(glGenBuffers(1, &RendererID)); // Generiert eine Anzahl von Buffern und liefert die Adresse als ID zur�ck
	GLTest(glBindBuffer(GL_ARRAY_BUFFER, RendererID)); // W�hlt diesen Buffer als den aktuell zu benutzenden Buffer aus
	GLTest(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW)); // gibt dem (Array-)Buffer eine festgelegte Anzahl an Bytes und f�llt ihn mit Daten (NULL = nicht f�llen)
}

VertexBuffer::~VertexBuffer() {
	GLTest(glDeleteBuffers(1, &RendererID));
}

void VertexBuffer::Bind() const {
	GLTest(glBindBuffer(GL_ARRAY_BUFFER, RendererID)); // W�hlt diesen Buffer als den aktuell zu benutzenden Buffer aus
}

void VertexBuffer::Unbind() const {
	GLTest(glBindBuffer(GL_ARRAY_BUFFER, 0)); // W�hlt KEINEN Buffer als aktuell zu benutzenden Buffer aus
}