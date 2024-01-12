#pragma once
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "VertexBufferLayout.h"

class VertexArray
{
public:
	VertexArray();
	~VertexArray();
	void createVertexArray();
	void deleteVertexArray();
	void AddBuffer(const VertexBuffer& vbo, const VertexBufferLayout& layout);
	void Bind() const;
	void UnBind() const;
private:
	unsigned int va_id;
};