#include "gBuffers.h"

gBuffers::gBuffers()
    : vbo(), vao(), ibo()
{
}

gBuffers::~gBuffers()
{
}

void gBuffers::createBuffers(const void* vb_data, unsigned int& vb_size, VertexBufferLayout& vb_layout, GLenum usage)
{
    // Vertex Array Object ����
    vao.createVertexArray();

    // Vertex Buffer ����
    vbo.createVertexBuffer(vb_data, vb_size, usage);

    // Vertex Array Object�� Vertex Buffer �߰�
    vao.AddBuffer(vbo, vb_layout);
}

void gBuffers::createBuffers(const void* vb_data, unsigned int& vb_size, const unsigned int* ib_indices, unsigned int& ib_count, VertexBufferLayout& layout, GLenum usage)  // ����� �κ�
{
    // Vertex Array Object ����
    vao.createVertexArray();

    // Vertex Buffer ����
    vbo.createVertexBuffer(vb_data, vb_size, usage);

    // Index Buffer ����
    ibo.createIndexBuffer(ib_indices, ib_count);

    // Vertex Array Object�� Vertex Buffer �� Index Buffer �߰�
    vao.AddBuffer(vbo, layout);  // ����� �κ�
}

void gBuffers::updateBuffers(const void* vb_data, unsigned int& vb_size, GLenum usage)  // ����� �κ�
{
    vbo.updateBuffer(vb_data, vb_size, usage);
}


void gBuffers::clearBuffers()
{
    // Vertex Array Object, Vertex Buffer, Index Buffer ����
    vao.deleteVertexArray();
    vbo.deleteVertexBuffer();
    ibo.deleteIndexBuffer();
}

void gBuffers::Bind() const
{
    // Vertex Array Object�� Index Buffer ���ε�
    vao.Bind();
    ibo.Bind();
}

void gBuffers::UnBind() const
{
    // Vertex Array Object�� Index Buffer ����ε�
    vao.UnBind();
    ibo.UnBind();
}
