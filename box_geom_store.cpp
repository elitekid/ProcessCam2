#include "box_geom_store.h"

box_geom_store::box_geom_store()
{
}

box_geom_store::~box_geom_store()
{
}

void box_geom_store::set_box_geometry()
{
    // ���� ���� ���̾ƿ� ����
    VertexBufferLayout vb_tri;
    vb_tri.AddFloat(3);  // ��ġ ����

    // ���� ����
    unsigned int node_vertices_size = vertices.size() * sizeof(float);
    box_buffers.createBuffers(static_cast<const void*>(vertices.data()), node_vertices_size, vb_tri, GL_STREAM_DRAW);

    // ���̴� ����
    box_shader.create_shader("box_frag_shader.vert", "box_frag_shader.frag");
}

void box_geom_store::drawBox(unsigned char* cameraData, int numberOfBox, std::vector<float> updatedVertices)
{
    // �ڽ� �׸���
    bind();

    // ������Ʈ
    vertices = updatedVertices;
    unsigned int node_vertices_size = vertices.size() * sizeof(float);
    box_buffers.updateBuffers(static_cast<const void*>(vertices.data()), node_vertices_size, GL_STREAM_DRAW);
    glDrawArrays(GL_TRIANGLES, 0, 6 * numberOfBox);

    // ���ε� ����
    unBind();
}

void box_geom_store::bind()
{
    // ���̴�, ���� ���� ���ε�
    box_shader.Bind();
    box_buffers.Bind();
}

void box_geom_store::unBind()
{
    // ���ε� ����
    box_shader.UnBind();
    box_buffers.UnBind();
}
