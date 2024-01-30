#include "index_buffer.h"

IndexBuffer::IndexBuffer() : ib_id_(0), count_(0) {}

IndexBuffer::~IndexBuffer() {
    if (ib_id_ != 0) {
    DeleteIndexBuffer();
    }
}

void IndexBuffer::DeleteIndexBuffer() { 
    glDeleteBuffers(1, &ib_id_);
}

  // 인덱스 버퍼 생성
  //
  // 인덱스 데이터를 인덱스 버퍼에 생성합니다.
void IndexBuffer::CreateIndexBuffer(const unsigned int* indices, unsigned int count) {
    // 인덱스 개수를 설정합니다.
    count_ = count;

    // 인덱스 버퍼 ID를 생성합니다.
    glGenBuffers(1, &ib_id_);

    // 인덱스 버퍼를 바인딩합니다.
    Bind();

    // 인덱스 데이터를 버퍼에 복사합니다.
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), indices,
                 GL_STATIC_DRAW);
}

  // 인덱스 버퍼 바인딩
  //
  // 인덱스 버퍼를 바인딩합니다.
void IndexBuffer::Bind() const { 
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ib_id_); 
}

  // 인덱스 버퍼 언바인딩
  //
  // 인덱스 버퍼를 언바인딩합니다.
void IndexBuffer::Unbind() const { 
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
