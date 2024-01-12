#include "VertexBuffer.h"
VertexBuffer::VertexBuffer()
    :vb_id(0)
{
    // Empty constructor at program start
}

VertexBuffer::~VertexBuffer()
{
    // Check if the vertex buffer ID is valid
    if (this->vb_id != 0) {
        // Delete the vertex buffer
        glDeleteBuffers(1, &vb_id);
    }
    // Additional cleanup or logging if needed
}

void VertexBuffer::deleteVertexBuffer()
{
    glDeleteBuffers(1, &vb_id);
}

void VertexBuffer::createVertexBuffer(const void* data, unsigned int size)
{
    // Main Constructor
    glGenBuffers(1, &vb_id);
    glBindBuffer(GL_ARRAY_BUFFER, vb_id);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

void VertexBuffer::Bind() const
{
    // Bind this vertex buffer with its id
    glBindBuffer(GL_ARRAY_BUFFER, vb_id);
}

void VertexBuffer::UnBind() const
{
    // Unbinds the currently bound vertex buffer object.
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}