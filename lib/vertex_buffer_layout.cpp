#include "vertex_buffer_layout.h"

VertexBufferLayout::VertexBufferLayout() : stride_(0) {}

// float 타입 요소 추가
void VertexBufferLayout::AddFloat(unsigned int count) {
  Push(GL_FLOAT, count, GL_FALSE);
}

// unsigned int 타입 요소 추가
void VertexBufferLayout::AddUnsignedInt(unsigned int count) {
  Push(GL_UNSIGNED_INT, count, GL_FALSE);
}

// unsigned char 타입 요소 추가
void VertexBufferLayout::AddUnsignedChar(unsigned int count) {
  Push(GL_UNSIGNED_BYTE, count, GL_TRUE);
}

// 요소 추가
//
// 정점 버퍼 레이아웃에 새로운 요소를 추가합니다.
void VertexBufferLayout::Push(unsigned int type, unsigned int count,
                              unsigned char normalized) {
  // 요소를 목록에 추가합니다.
  elements_.push_back({type, count, normalized});
  // stride 값을 새로운 요소의 크기만큼 증가시킵니다.
  stride_ += count * VertexBufferElement::GetSizeOfType(type);
}