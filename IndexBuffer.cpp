#include "IndexBuffer.h"
IndexBuffer::IndexBuffer()
	:ib_id(0),m_count(0)
{
	// Empty constructor at program start
}

IndexBuffer::~IndexBuffer()
{
	// Check if the index buffer ID is valid
	if (this->ib_id != 0) {
		// Delete the index buffer
		glDeleteBuffers(1, &ib_id);
	}
	// Additional cleanup or logging if needed
}


void IndexBuffer::deleteIndexBuffer()
{
	glDeleteBuffers(1, &ib_id);
}


void IndexBuffer::createIndexBuffer(const unsigned int* indices, unsigned int count)
{
	m_count = count;

	// Generate a new buffer ID for the index buffer
	glGenBuffers(1, &ib_id);

	// Bind the buffer to the GL_ELEMENT_ARRAY_BUFFER target
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ib_id);

	// Copy the index data to the buffer
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), indices, GL_STATIC_DRAW);
}

void IndexBuffer::Bind() const
{
	// Bind the buffer to the GL_ELEMENT_ARRAY_BUFFER target
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ib_id);
}

void IndexBuffer::UnBind() const
{
	// Unbind the buffer from the GL_ELEMENT_ARRAY_BUFFER target
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
