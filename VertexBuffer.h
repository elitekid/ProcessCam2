#pragma once
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class VertexBuffer
{
public:
	VertexBuffer();
	~VertexBuffer();
	void deleteVertexBuffer();
	void createVertexBuffer(const void* data, unsigned int size);
	void Bind() const;
	void UnBind() const;
private:
	unsigned int vb_id;
};
