#include "cam_geom_store.h"

cam_geom_store::cam_geom_store()
{
}

cam_geom_store::~cam_geom_store()
{
}

void cam_geom_store::set_camera_geometry(int cols, int rows)
{
    // ���� ������ ����
    float vertices[] = {
        // ��ġ                // �ؽ�ó ��ǥ
         1.0f,  1.0f, 0.0f,   1.0f, 0.0f,  // ������ ���
         1.0f, -1.0f, 0.0f,   1.0f, 1.0f,  // ������ �ϴ�

        -1.0f, -1.0f, 0.0f,   0.0f, 1.0f,  // ���� �ϴ�
        -1.0f,  1.0f, 0.0f,   0.0f, 0.0f   // ���� ���
    };

    // �ε��� ������ ����
    unsigned int indices[] = {
        0, 1, 3,   // ù ��° �ﰢ��
        1, 2, 3    // �� ��° �ﰢ��
    };

    // Geometry ����
    unsigned int node_vertices_count = 20;
    unsigned int node_indices_count = 6;

    // ���� ���� ���̾ƿ� ����
    VertexBufferLayout vb_tri;
    vb_tri.AddFloat(3);  // ��ġ ����
    vb_tri.AddFloat(2);  // �ؽ�ó ��ǥ ����

    // ���� ����
    unsigned int node_vertices_size = node_vertices_count * sizeof(float);
    cam_buffers.createBuffers(vertices, node_vertices_size, indices, node_indices_count, vb_tri, GL_STATIC_DRAW);

    // ���̴� ����
    cam_shader.create_shader("camera_frag_shader.vert", "camera_frag_shader.frag");

    // �ؽ�ó �ʱ�ȭ
    cam_texture.load(cols, rows);

    // ���̴��� �ؽ�ó ������ ����
    cam_shader.setUniform("textureID_bg", 0);
}

void cam_geom_store::drawCam(unsigned char* cameraData)
{
    // ī�޶� ������ �׸���
    bind();

    // �ؽ�ó ������Ʈ
    cam_texture.update(cameraData);

    // ���� �׸���
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    // ���ε� ����
    unBind();
}

void cam_geom_store::bind()
{
    // �ؽ�ó, ���̴�, ���� ���� ���ε�
    cam_texture.bind();
    cam_shader.Bind();
    cam_buffers.Bind();
}

void cam_geom_store::unBind()
{
    // ���ε� ����
    cam_shader.UnBind();
    cam_buffers.UnBind();
    cam_texture.unBind();
}
