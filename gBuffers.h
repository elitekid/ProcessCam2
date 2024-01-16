#pragma once
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Texture.h"

class gBuffers
{
public:
	gBuffers();
	~gBuffers();
	void Bind()const;
	void UnBind()const;
	void clearBuffers();

	void createBuffers(const void* vb_data, unsigned int& vb_size, VertexBufferLayout& vb_layout, GLenum usage);
	void createBuffers(const void* vb_data, unsigned int& vb_size, const unsigned int* ib_indices, unsigned int& ib_count, VertexBufferLayout& layout, GLenum usage);
	void updateBuffers(const void* vb_data, unsigned int& vb_size, GLenum usage);
	VertexBuffer vbo;
	VertexArray vao;
	IndexBuffer ibo;
private:

};
