#include "box_geom_store.h"

BoxGeomStore::BoxGeomStore() {}

BoxGeomStore::~BoxGeomStore() {}

void BoxGeomStore::SetBoxGeometry() {
  // 정점 버퍼 레이아웃 정의
  VertexBufferLayout vb_tri;
  vb_tri.AddFloat(3);  // 위치 정보

  // 버퍼 생성
  unsigned int node_vertices_size = vertices_.size() * sizeof(float);
  box_buffers_.CreateBuffers(static_cast<const void*>(vertices_.data()),
                            node_vertices_size, vb_tri, GL_STREAM_DRAW);

  // 쉐이더 생성
  box_shader_.CreateShaderByPath("box_frag_shader.vert", "box_frag_shader.frag");
}

void BoxGeomStore::DrawBox(const FrameInfo& frame_Info) {
  // 박스 그리기
  Bind();

  // 업데이트
  vertices_ = frame_Info.GetVertices();
  unsigned int node_vertices_size = vertices_.size() * sizeof(float);
  box_buffers_.UpdateBuffers(static_cast<const void*>(vertices_.data()),
                            node_vertices_size, GL_STREAM_DRAW);
  glDrawArrays(GL_TRIANGLES, 0, 6 * frame_Info.GetBoxCnt());

  // 바인딩 해제
  UnBind();
}

void BoxGeomStore::Bind() {
  // 쉐이더, 정점 버퍼 바인딩
  box_shader_.Bind();
  box_buffers_.Bind();
}

void BoxGeomStore::UnBind() {
  // 바인딩 해제
  box_shader_.UnBind();
  box_buffers_.UnBind();
}
