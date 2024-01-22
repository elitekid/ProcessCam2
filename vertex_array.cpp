#include "vertex_array.h"

VertexArray::VertexArray() : va_id_(0) {}

VertexArray::~VertexArray() {
  if (va_id_ != 0) {
    glDeleteVertexArrays(1, &va_id_);
  }
}

void VertexArray::CreateVertexArray() { glGenVertexArrays(1, &va_id_); }

void VertexArray::DeleteVertexArray() { glDeleteVertexArrays(1, &va_id_); }

void VertexArray::Bind() const { glBindVertexArray(va_id_); }

void VertexArray::Unbind() const { glBindVertexArray(0); }

void VertexArray::AddBuffer(const VertexBuffer& vbo,
                            const VertexBufferLayout& layout) {
  // 버텍스 배열 객체에 버퍼 객체를 연결합니다.

  // 버텍스 배열 객체를 바인딩합니다.
  Bind();

  // 버텍스 버퍼 객체를 바인딩합니다.
  vbo.Bind();

  // 레이아웃에 따라 버퍼의 속성들을 활성화하고 포인터 설정
  const std::vector<VertexBufferElement>& elements = layout.GetElements();
  unsigned int offset = 0;
  for (unsigned int i = 0; i < elements.size(); i++) {
    const VertexBufferElement& element = elements[i];

    // 지정된 버퍼 인덱스에 대한 버텍스 속성 배열을 활성화합니다.
    glEnableVertexAttribArray(i);

    // 지정된 버퍼 인덱스에 대한 버텍스 속성 포인터를 설정합니다.
    // 이는 어떻게 버텍스 데이터를 해석해야 하는지 OpenGL에 알려줍니다.
    glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.GetStride(), (const void*)(uintptr_t)(offset));

    offset += element.count * VertexBufferElement::GetSizeOfType(element.type);
  }

  // 버텍스 버퍼 객체를 언바인드합니다.
  vbo.Unbind();

  // 버텍스 배열 객체를 언바인드합니다.
  Unbind();
}
