// Copyright 2024 elitekid

#ifndef VERTEX_ARRAY_H_
#define VERTEX_ARRAY_H_

#include <glad/glad.h>

#include <vector>
#include <iostream>

#include "vertex_buffer.h"
#include "vertex_buffer_layout.h"

class VertexArray {
 public:
  VertexArray();
  ~VertexArray();
  void CreateVertexArray();
  void DeleteVertexArray();
  void AddBuffer(const VertexBuffer& vbo, const VertexBufferLayout& layout);
  void Bind() const;
  void Unbind() const;

 private:
  unsigned int va_id_;
};

#endif  // VERTEX_ARRAY_H_
