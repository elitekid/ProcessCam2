#include "VertexBuffer.h"

VertexBuffer::VertexBuffer()
    : vb_id(0)
{
}

VertexBuffer::~VertexBuffer()
{
    // ���� ���� ID�� ��ȿ���� Ȯ��
    if (this->vb_id != 0) {
        // ���� ���� ����
        glDeleteBuffers(1, &vb_id);
    }
    // �߰����� ���� �Ǵ� �ʿ��� ��� �α�
}

void VertexBuffer::deleteVertexBuffer()
{
    // ���� ���� ����
    glDeleteBuffers(1, &vb_id);
}

void VertexBuffer::createVertexBuffer(const void* data, unsigned int size, GLenum usage)
{
    // �� ������
    glGenBuffers(1, &vb_id);
    glBindBuffer(GL_ARRAY_BUFFER, vb_id);
    glBufferData(GL_ARRAY_BUFFER, size, data, usage);
}

void VertexBuffer::updateBuffer(const void* data, unsigned int size, GLenum usage)
{
    // ���� ������Ʈ
    glBindBuffer(GL_ARRAY_BUFFER, vb_id);
    glBufferData(GL_ARRAY_BUFFER, size, data, usage);
}

void VertexBuffer::Bind() const
{
    // ������ ���� ���۸� ID�� ���ε�
    glBindBuffer(GL_ARRAY_BUFFER, vb_id);
}

void VertexBuffer::UnBind() const
{
    // ���� ���ε��� ���� ���� ��ü ����ε�
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
