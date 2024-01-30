#include "cam_geom_store.h"

CamGeomStore::CamGeomStore() {}

CamGeomStore::~CamGeomStore() {}

void CamGeomStore::SetCameraGeometry(int width, int height) {
  // 정점 데이터 정의
  float vertices[] = {
      // 위치  // 텍스처 좌표
      1.0f,  1.0f,  0.0f, 1.0f, 0.0f,  // 오른쪽 상단
      1.0f,  -1.0f, 0.0f, 1.0f, 1.0f,  // 오른쪽 하단

      -1.0f, -1.0f, 0.0f, 0.0f, 1.0f,  // 왼쪽 하단
      -1.0f, 1.0f,  0.0f, 0.0f, 0.0f   // 왼쪽 상단
  };

  // 인덱스 데이터 정의
  unsigned int indices[] = {
      0, 1, 3,  // 첫 번째 삼각형
      1, 2, 3   // 두 번째 삼각형
  };

  // Geometry 설정
  unsigned int node_vertices_count = 20;
  unsigned int node_indices_count = 6;

  // 정점 버퍼 레이아웃 정의
  VertexBufferLayout vb_tri;
  vb_tri.AddFloat(3);  // 위치 정보
  vb_tri.AddFloat(2);  // 텍스처 좌표 정보

  // 버퍼 생성
  unsigned int node_vertices_size = node_vertices_count * sizeof(float);
  cam_buffers_.CreateBuffers(vertices, node_vertices_size, indices,
                             node_indices_count, vb_tri, GL_STATIC_DRAW);

  // 쉐이더 생성
  cam_shader_.CreateShaderByPath("glsl/camera_frag_shader.vert", "glsl/camera_frag_shader.frag");

  // 텍스처 초기화
  cam_texture_.Load(width, height);

  // 쉐이더에 텍스처 유니폼 설정
  cam_shader_.SetUniform("textureID_bg", 0);
}

void CamGeomStore::DrawCam(const cv::Mat& frame) {
  // 카메라 프레임 그리기
  Bind();

  // 텍스처 업데이트
  cam_texture_.Update(frame.data);

  // 정점 그리기
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

  // 바인딩 해제
  UnBind();
}

void CamGeomStore::Bind() {
  // 텍스처, 쉐이더, 정점 버퍼 바인딩
  cam_texture_.Bind();
  cam_shader_.Bind();
  cam_buffers_.Bind();
}

void CamGeomStore::UnBind() {
  // 바인딩 해제
  cam_shader_.UnBind();
  cam_buffers_.UnBind();
  cam_texture_.UnBind();
}
