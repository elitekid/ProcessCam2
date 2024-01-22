#include "g_buffers.h"

GBuffers::GBuffers() : vbo_(), vao_(), ibo_() {}

GBuffers::~GBuffers() {}

void GBuffers::CreateBuffers(const void* vb_data, unsigned int& vb_size,
                             VertexBufferLayout& vb_layout, GLenum usage) {
  // Vertex Array Object 생성
  vao_.CreateVertexArray();

  // Vertex Buffer 생성
  vbo_.CreateVertexBuffer(vb_data, vb_size, usage);

  // Vertex Array Object에 Vertex Buffer 추가
  vao_.AddBuffer(vbo_, vb_layout);
}

void GBuffers::CreateBuffers(const void* vb_data, unsigned int& vb_size,
                             const unsigned int* ib_indices,
                             unsigned int& ib_count, VertexBufferLayout& layout,
                             GLenum usage) {
  // Vertex Array Object 생성
  vao_.CreateVertexArray();

  // Vertex Buffer 생성
  vbo_.CreateVertexBuffer(vb_data, vb_size, usage);

  // Index Buffer 생성
  ibo_.CreateIndexBuffer(ib_indices, ib_count);

  // Vertex Array Object에 Vertex Buffer 및 Index Buffer 추가
  vao_.AddBuffer(vbo_, layout);
}

void GBuffers::UpdateBuffers(const void* vb_data, unsigned int& vb_size,
                             GLenum usage) {
  vbo_.UpdateBuffer(vb_data, vb_size, usage);
}

void GBuffers::ClearBuffers() {
  // Vertex Array Object, Vertex Buffer, Index Buffer 삭제
  vao_.DeleteVertexArray();
  vbo_.DeleteVertexBuffer();
  ibo_.DeleteIndexBuffer();
}

void GBuffers::Bind() const {
  // Vertex Array Object와 Index Buffer 바인딩
  vao_.Bind();
  ibo_.Bind();
}

void GBuffers::UnBind() const {
  // Vertex Array Object와 Index Buffer 언바인딩
  vao_.Unbind();
  ibo_.Unbind();
}
