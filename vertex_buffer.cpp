#include "vertex_buffer.h"

VertexBuffer::VertexBuffer() : vb_id_(0) {}

VertexBuffer::~VertexBuffer() {
  if (vb_id_ != 0) {
    glDeleteBuffers(1, &vb_id_);
  }
}

void VertexBuffer::DeleteVertexBuffer() { glDeleteBuffers(1, &vb_id_); }

void VertexBuffer::CreateVertexBuffer(const void* data, unsigned int size,
                                      GLenum usage) {
  // 주 생성자
  glGenBuffers(1, &vb_id_);
  Bind();
  glBufferData(GL_ARRAY_BUFFER, size, data, usage);
}

void VertexBuffer::UpdateBuffer(const void* data, unsigned int size,
                                GLenum usage) {
  // 버퍼 업데이트
  Bind();
  glBufferData(GL_ARRAY_BUFFER, size, data, usage);
}

void VertexBuffer::Bind() const {
  // 현재의 정점 버퍼를 ID로 바인딩
  glBindBuffer(GL_ARRAY_BUFFER, vb_id_);
}

void VertexBuffer::Unbind() const {
  // 현재 바인딩된 정점 버퍼 객체 언바인드
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}
