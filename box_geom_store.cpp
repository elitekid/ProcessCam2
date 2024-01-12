#include "box_geom_store.h"

box_geom_store::box_geom_store()
{
}

box_geom_store::~box_geom_store()
{
}

void box_geom_store::set_box_geometry()
{
    // 정점 버퍼 레이아웃 정의
    VertexBufferLayout vb_tri;
    vb_tri.AddFloat(3);  // 위치 정보

    // 버퍼 생성
    unsigned int node_vertices_size = vertices.size() * sizeof(float);
    box_buffers.createBuffers(static_cast<const void*>(vertices.data()), node_vertices_size, vb_tri, GL_STREAM_DRAW);

    // 쉐이더 생성
    box_shader.create_shader("box_frag_shader.vert", "box_frag_shader.frag");
}

void box_geom_store::drawBox(unsigned char* cameraData, int numberOfBox, std::vector<float> updatedVertices)
{
    // 박스 그리기
    bind();

    // 업데이트
    vertices = updatedVertices;
    unsigned int node_vertices_size = vertices.size() * sizeof(float);
    box_buffers.updateBuffers(static_cast<const void*>(vertices.data()), node_vertices_size, GL_STREAM_DRAW);
    glDrawArrays(GL_TRIANGLES, 0, 6 * numberOfBox);

    // 바인딩 해제
    unBind();
}

void box_geom_store::bind()
{
    // 쉐이더, 정점 버퍼 바인딩
    box_shader.Bind();
    box_buffers.Bind();
}

void box_geom_store::unBind()
{
    // 바인딩 해제
    box_shader.UnBind();
    box_buffers.UnBind();
}
