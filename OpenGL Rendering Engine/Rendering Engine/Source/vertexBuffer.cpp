

// Include
	#include "VertexBuffer.h"
	#include "Renderer.h"


VertexBuffer::VertexBuffer(const void* data, unsigned int size) {
	GLTest(glGenBuffers(1, &RendererID)); // Generiert eine Anzahl von Buffern und liefert die Adresse als ID zurück
	GLTest(glBindBuffer(GL_ARRAY_BUFFER, RendererID)); // Wählt diesen Buffer als den aktuell zu benutzenden Buffer aus
	GLTest(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW)); // gibt dem (Array-)Buffer eine festgelegte Anzahl an Bytes und füllt ihn mit Daten (NULL = nicht füllen)
}

VertexBuffer::~VertexBuffer() {
	GLTest(glDeleteBuffers(1, &RendererID));
}

void VertexBuffer::Bind() const {
	GLTest(glBindBuffer(GL_ARRAY_BUFFER, RendererID)); // Wählt diesen Buffer als den aktuell zu benutzenden Buffer aus
}

void VertexBuffer::Unbind() const {
	GLTest(glBindBuffer(GL_ARRAY_BUFFER, 0)); // Wählt KEINEN Buffer als aktuell zu benutzenden Buffer aus
}