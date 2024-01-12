#include "VertexBuffer.h"

VertexBuffer::VertexBuffer()
    : vb_id(0)
{
}

VertexBuffer::~VertexBuffer()
{
    // 정점 버퍼 ID가 유효한지 확인
    if (this->vb_id != 0) {
        // 정점 버퍼 삭제
        glDeleteBuffers(1, &vb_id);
    }
    // 추가적인 정리 또는 필요한 경우 로깅
}

void VertexBuffer::deleteVertexBuffer()
{
    // 정점 버퍼 삭제
    glDeleteBuffers(1, &vb_id);
}

void VertexBuffer::createVertexBuffer(const void* data, unsigned int size, GLenum usage)
{
    // 주 생성자
    glGenBuffers(1, &vb_id);
    glBindBuffer(GL_ARRAY_BUFFER, vb_id);
    glBufferData(GL_ARRAY_BUFFER, size, data, usage);
}

void VertexBuffer::updateBuffer(const void* data, unsigned int size, GLenum usage)
{
    // 버퍼 업데이트
    glBindBuffer(GL_ARRAY_BUFFER, vb_id);
    glBufferData(GL_ARRAY_BUFFER, size, data, usage);
}

void VertexBuffer::Bind() const
{
    // 현재의 정점 버퍼를 ID로 바인딩
    glBindBuffer(GL_ARRAY_BUFFER, vb_id);
}

void VertexBuffer::UnBind() const
{
    // 현재 바인딩된 정점 버퍼 객체 언바인드
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
