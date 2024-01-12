#include "text_geom_store.h"

text_geom_store::text_geom_store()
{
    // ������
}

text_geom_store::~text_geom_store()
{
    // �Ҹ���
}

void text_geom_store::set_text_geometry()
{
    // �ؽ�Ʈ ������Ʈ�� ���� �Լ�
    // ���� ���� �ʱ�ȭ �� ���� ���� �۾� ����

    // ���� ������ �� �ε��� �ʱ�ȭ
    unsigned int node_vertices_count = 6 * 3;
    float* node_vertices = new float[node_vertices_count];

    unsigned int node_indices_count = 3;
    unsigned int* node_indices = new unsigned int[node_indices_count];

    unsigned int node_vertex_index = 0;
    unsigned int node_indices_index = 0;

    // ������ �ﰢ���� �̿��� ���� �� �ε��� ����
    set_simple_triangle(node_vertices, node_vertex_index, node_indices, node_indices_index);

    // ���� ���� ���̾ƿ� ����
    VertexBufferLayout vb_tri;
    vb_tri.AddFloat(3);
    vb_tri.AddFloat(3);

    // ���� ����
    float red, green, blue;
    Utils::hexToNormalizedFloat(settingManager.getColorCode().toStdString(), red, green, blue);

    // ���� ����
    unsigned int node_vertices_size = node_vertices_count * sizeof(float);
    tri_buffers.createBuffers(node_vertices, node_vertices_size, node_indices, node_indices_count, vb_tri, GL_STATIC_DRAW);

    // �ؽ�Ʈ ���̴� ���� �� �ʱ�ȭ
    text_shader.create_shader("text_vert_shader.vert", "text_frag_shader.frag");
    text_shader.setUniform("zoomscale", 1.0f);
    text_shader.setUniform("u_Texture", 0);
    text_shader.setUniform("textColor", red, green, blue, 1.0f);
}

void text_geom_store::add_label(std::vector<TextArea>& textAreas, float w, float h, float square)
{
    // �� �߰� �Լ�
    // TextArea ��ü�� �̿��Ͽ� ���� ��ġ �� ���� ����

    // ��� �� �ʱ�ȭ
    all_labels.init();

    // �� TextArea�� ���� �� �߰�
    for (const auto& t : textAreas) {
        // NDC ��ǥ ���
        float ndcX = ((t.getX() + square / 2.0f - 4.5f) / w) * 2.0f - 1.0f;
        float ndcY = 1.0f - ((t.getY()) / (h - 1.0f)) * 2.0f;

        // �� �߰�
        all_labels.add_text(t.getHexColor(), glm::vec2(ndcX, ndcY), glm::vec3(0.0f, 1.0f, 1.0f), 1.0f, -90, 0.000015f);
    }

    // �󺧿� ���� ���� ����
    all_labels.set_buffers();
}

void text_geom_store::delete_buffers()
{
    // ���� ���� �Լ�
    // ��� ���� ���۸� ����
    all_labels.clear_buffers();
}

void text_geom_store::set_simple_triangle(float* vertices, unsigned int& vertices_index,
    unsigned int* indices, unsigned int& indices_index)
{
    // ������ �ﰢ�� ���� �� �ε��� ���� �Լ�
    // �ﰢ���� �� �������� �����ϰ� �ε����� ����

    // Point 1
    vertices[vertices_index + 0] = -0.5;
    vertices[vertices_index + 1] = -0.5;
    vertices[vertices_index + 2] = 0.0f;

    vertices[vertices_index + 3] = 1.0f;
    vertices[vertices_index + 4] = 1.0f;
    vertices[vertices_index + 5] = 1.0f;

    vertices_index = vertices_index + 6;

    // Point 2
    vertices[vertices_index + 0] = 0.5;
    vertices[vertices_index + 1] = -0.5;
    vertices[vertices_index + 2] = 0.0f;

    vertices[vertices_index + 3] = 1.0f;
    vertices[vertices_index + 4] = 1.0f;
    vertices[vertices_index + 5] = 1.0f;

    vertices_index = vertices_index + 6;

    // Point 3
    vertices[vertices_index + 0] = 0.0;
    vertices[vertices_index + 1] = 0.5;
    vertices[vertices_index + 2] = 0.0f;

    vertices[vertices_index + 3] = 1.0f;
    vertices[vertices_index + 4] = 1.0f;
    vertices[vertices_index + 5] = 1.0f;

    vertices_index = vertices_index + 6;

    // �ﰢ���� �ε��� ����
    indices[indices_index + 0] = 0;
    indices[indices_index + 1] = 1;
    indices[indices_index + 2] = 2;
}

void text_geom_store::paint_geometry()
{
    // ������Ʈ���� �׸��� �Լ�
    // �ؽ�Ʈ ���̴��� ���ε��ϰ� ���� �׸� �� ����ε�
    text_shader.Bind();
    all_labels.paint_text();
    text_shader.UnBind();
}