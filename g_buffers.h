// Copyright 2024 elitekid

#ifndef G_BUFFERS_H_
#define G_BUFFERS_H_

#include "index_buffer.h"
#include "texture.h"
#include "vertex_array.h"
#include "vertex_buffer.h"

class GBuffers {
 public:
  GBuffers();
  ~GBuffers();
  void Bind() const;
  void UnBind() const;
  void ClearBuffers();  // 메서드 이름 대문자로 시작

  void CreateBuffers(const void* vb_data, unsigned int& vb_size,
                     VertexBufferLayout& vb_layout, GLenum usage);
  void CreateBuffers(const void* vb_data, unsigned int& vb_size,
                     const unsigned int* ib_indices, unsigned int& ib_count,
                     VertexBufferLayout& layout, GLenum usage);
  void UpdateBuffers(const void* vb_data, unsigned int& vb_size, GLenum usage);

 private:
  VertexBuffer vbo_;
  VertexArray vao_;
  IndexBuffer ibo_;
};

#endif  // G_BUFFERS_H_
