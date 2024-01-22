// Copyright 2024 Synergy-User

#ifndef VERTEX_BUFFER_H_
#define VERTEX_BUFFER_H_

#include <glad/glad.h>

#include <iostream>

class VertexBuffer {
 public:
  VertexBuffer();
  ~VertexBuffer();
  void DeleteVertexBuffer();
  void CreateVertexBuffer(const void* data, unsigned int size, GLenum usage);
  void UpdateBuffer(const void* data, unsigned int size, GLenum usage);
  void Bind() const;
  void Unbind() const;

 private:
  unsigned int vb_id_;
};

#endif  // VERTEX_BUFFER_H_
