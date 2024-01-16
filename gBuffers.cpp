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
    // Vertex Array Object 생성
    vao.createVertexArray();

    // Vertex Buffer 생성
    vbo.createVertexBuffer(vb_data, vb_size, usage);

    // Vertex Array Object에 Vertex Buffer 추가
    vao.AddBuffer(vbo, vb_layout);
}

void gBuffers::createBuffers(const void* vb_data, unsigned int& vb_size, const unsigned int* ib_indices, unsigned int& ib_count, VertexBufferLayout& layout, GLenum usage)  // 변경된 부분
{
    // Vertex Array Object 생성
    vao.createVertexArray();

    // Vertex Buffer 생성
    vbo.createVertexBuffer(vb_data, vb_size, usage);

    // Index Buffer 생성
    ibo.createIndexBuffer(ib_indices, ib_count);

    // Vertex Array Object에 Vertex Buffer 및 Index Buffer 추가
    vao.AddBuffer(vbo, layout);  // 변경된 부분
}

void gBuffers::updateBuffers(const void* vb_data, unsigned int& vb_size, GLenum usage)  // 변경된 부분
{
    vbo.updateBuffer(vb_data, vb_size, usage);
}


void gBuffers::clearBuffers()
{
    // Vertex Array Object, Vertex Buffer, Index Buffer 삭제
    vao.deleteVertexArray();
    vbo.deleteVertexBuffer();
    ibo.deleteIndexBuffer();
}

void gBuffers::Bind() const
{
    // Vertex Array Object와 Index Buffer 바인딩
    vao.Bind();
    ibo.Bind();
}

void gBuffers::UnBind() const
{
    // Vertex Array Object와 Index Buffer 언바인딩
    vao.UnBind();
    ibo.UnBind();
}
