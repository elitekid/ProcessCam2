#include "text_geom_store.h"

text_geom_store::text_geom_store()
{
    // 생성자
}

text_geom_store::~text_geom_store()
{
    // 소멸자
}

void text_geom_store::set_text_geometry()
{
    // 텍스트 지오메트리 설정 함수
    // 여러 가지 초기화 및 버퍼 생성 작업 수행

    // 정점 데이터 및 인덱스 초기화
    unsigned int node_vertices_count = 6 * 3;
    float* node_vertices = new float[node_vertices_count];

    unsigned int node_indices_count = 3;
    unsigned int* node_indices = new unsigned int[node_indices_count];

    unsigned int node_vertex_index = 0;
    unsigned int node_indices_index = 0;

    // 간단한 삼각형을 이용한 정점 및 인덱스 생성
    set_simple_triangle(node_vertices, node_vertex_index, node_indices, node_indices_index);

    // 정점 버퍼 레이아웃 정의
    VertexBufferLayout vb_tri;
    vb_tri.AddFloat(3);
    vb_tri.AddFloat(3);

    // 색상 설정
    float red, green, blue;
    Utils::hexToNormalizedFloat(settingManager.getColorCode().toStdString(), red, green, blue);

    // 버퍼 생성
    unsigned int node_vertices_size = node_vertices_count * sizeof(float);
    tri_buffers.createBuffers(node_vertices, node_vertices_size, node_indices, node_indices_count, vb_tri, GL_STATIC_DRAW);

    // 텍스트 쉐이더 생성 및 초기화
    text_shader.create_shader("text_vert_shader.vert", "text_frag_shader.frag");
    text_shader.setUniform("zoomscale", 1.0f);
    text_shader.setUniform("u_Texture", 0);
    text_shader.setUniform("textColor", red, green, blue, 1.0f);
}

void text_geom_store::add_label(std::vector<TextArea>& textAreas, float w, float h, float square)
{
    // 라벨 추가 함수
    // TextArea 객체를 이용하여 라벨의 위치 및 색상 설정

    // 모든 라벨 초기화
    all_labels.init();

    // 각 TextArea에 대한 라벨 추가
    for (const auto& t : textAreas) {
        // NDC 좌표 계산
        float ndcX = ((t.getX() + square / 2.0f - 4.5f) / w) * 2.0f - 1.0f;
        float ndcY = 1.0f - ((t.getY()) / (h - 1.0f)) * 2.0f;

        // 라벨 추가
        all_labels.add_text(t.getHexColor(), glm::vec2(ndcX, ndcY), glm::vec3(0.0f, 1.0f, 1.0f), 1.0f, -90, 0.000015f);
    }

    // 라벨에 대한 버퍼 설정
    all_labels.set_buffers();
}

void text_geom_store::delete_buffers()
{
    // 버퍼 삭제 함수
    // 모든 라벨의 버퍼를 삭제
    all_labels.clear_buffers();
}

void text_geom_store::set_simple_triangle(float* vertices, unsigned int& vertices_index,
    unsigned int* indices, unsigned int& indices_index)
{
    // 간단한 삼각형 정점 및 인덱스 설정 함수
    // 삼각형의 세 꼭지점을 정의하고 인덱스를 설정

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

    // 삼각형의 인덱스 설정
    indices[indices_index + 0] = 0;
    indices[indices_index + 1] = 1;
    indices[indices_index + 2] = 2;
}

void text_geom_store::paint_geometry()
{
    // 지오메트리를 그리는 함수
    // 텍스트 쉐이더를 바인딩하고 라벨을 그린 후 언바인딩
    text_shader.Bind();
    all_labels.paint_text();
    text_shader.UnBind();
}
