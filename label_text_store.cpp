#include "label_text_store.h"

label_text_store::label_text_store()
	: total_char_count(0)
{
	// 생성자
}

label_text_store::~label_text_store()
{
	// 소멸자
}

void label_text_store::init()
{
	// 모든 라벨 초기화
	labels.clear();
	main_font.create_atlas();
	total_char_count = 0;
}

void label_text_store::add_text(const char* label, glm::vec2 label_loc, glm::vec3 label_color,
	float geom_scale, float label_angle, float font_size)
{
	// 임시 요소 생성
	label_text temp_label;
	temp_label.label = label;
	temp_label.label_loc = label_loc;
	temp_label.label_color = label_color;
	temp_label.label_angle = label_angle;
	temp_label.label_size = font_size;

	// 새로운 요소를 위한 공간 확보
	labels.reserve(labels.size() + 1);

	// 목록에 추가
	labels.push_back(temp_label);

	// 문자 수 업데이트
	total_char_count = total_char_count + strlen(label);
}

void label_text_store::set_buffers()
{
	// 모델의 레이블 정점 정의 (4 개의 정점으로 사각형을 형성하는데, 2 개의 위치, 2 개의 원점, 2 개의 텍스처 좌표, 1 개의 문자 ID)

	unsigned int label_vertex_count = 4 * 6 * total_char_count;
	float* label_vertices = new float[label_vertex_count];

	// 6 개의 인덱스로 삼각형을 형성
	unsigned int label_indices_count = 6 * total_char_count;
	unsigned int* label_indices = new unsigned int[label_indices_count];

	unsigned int label_v_index = 0;
	unsigned int label_i_index = 0;

	for (auto& lb : labels)
	{
		// 각 문자에 대한 버퍼 채우기
		get_buffer(lb, label_vertices, label_v_index, label_indices, label_i_index);
	}

	// 레이아웃 생성
	VertexBufferLayout label_layout;
	label_layout.AddFloat(2);  // 위치
	label_layout.AddFloat(2);  // 원점
	label_layout.AddFloat(2);  // 텍스처 좌표

	unsigned int label_vertex_size = label_vertex_count * sizeof(float);

	// 버퍼 생성
	label_buffers.createBuffers((void*)label_vertices, label_vertex_size,
		(unsigned int*)label_indices, label_indices_count, label_layout, GL_STATIC_DRAW);

	// 힙에서 동적 배열 삭제
	delete[] label_vertices;
	delete[] label_indices;
}
void label_text_store::clear_buffers()
{
	label_buffers.clearBuffers();
}

void label_text_store::paint_text()
{
	// 모든 라벨 그리기
	label_buffers.Bind();

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, main_font.textureID);

	glDrawElements(GL_TRIANGLES, 6 * total_char_count, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);

	label_buffers.UnBind();
}

void label_text_store::get_buffer(label_text& lb,
	float* vertices, unsigned int& vertex_index, unsigned int* indices, unsigned int& indices_index)
{
	// 위치 좌표 저장
	glm::vec2 loc = lb.label_loc;
	float x = loc.x;
	float y = loc.y;
	float scale =lb.label_size;
	//float scale = 1.0f;
	glm::vec2 rotated_pt;

	for (int i = 0; lb.label[i] != '\0'; ++i) 
	{
		// 글리프 정보 가져오기
		char ch = lb.label[i];

		Character ch_data =	main_font.ch_atlas[ch];

		float xpos = x + (ch_data.Bearing.x * scale); // 좌상단
		float ypos = y - (ch_data.Size.y - ch_data.Bearing.y) * scale;

		float w = ch_data.Size.x * scale;
		float h = ch_data.Size.y * scale;

		float margin = 0.00001; // 렌더링할 때 다음 문자와의 미세한 오버랩 방지를 위한 값

		// 점 1
		// Vertices [0,0] // 첫 번째 점
		rotated_pt = rotate_pt(loc, glm::vec2(xpos, ypos + h), lb.label_angle);

		vertices[vertex_index + 0] = rotated_pt.x;
		vertices[vertex_index + 1] = rotated_pt.y;

		// 라벨 원점
		vertices[vertex_index + 2] = loc.x;
		vertices[vertex_index + 3] = loc.y;

		// 텍스처 글리프 좌표
		vertices[vertex_index + 4] = ch_data.top_left.x + margin;
		vertices[vertex_index + 5] = ch_data.top_left.y;

		// 반복
		vertex_index = vertex_index + 6;

		//__________________________________________________________________________________________

		// 점 2
		// Vertices [0,1] // 두 번째 점
		rotated_pt = rotate_pt(loc, glm::vec2(xpos, ypos), lb.label_angle);

		vertices[vertex_index + 0] = rotated_pt.x;
		vertices[vertex_index + 1] = rotated_pt.y;

		// 라벨 원점
		vertices[vertex_index + 2] = loc.x;
		vertices[vertex_index + 3] = loc.y;

		// 텍스처 글리프 좌표
		vertices[vertex_index + 4] = ch_data.top_left.x+ margin;
		vertices[vertex_index + 5] = ch_data.bot_right.y;

		// 반복
		vertex_index = vertex_index + 6;

		//__________________________________________________________________________________________

		// 점 3
		// Vertices [1,1] // 세 번째 점
		rotated_pt = rotate_pt(loc, glm::vec2(xpos+w, ypos), lb.label_angle);

		vertices[vertex_index + 0] = rotated_pt.x;
		vertices[vertex_index + 1] = rotated_pt.y;

		// 라벨 원점
		vertices[vertex_index + 2] = loc.x;
		vertices[vertex_index + 3] = loc.y;

		// 텍스처 글리프 좌표
		vertices[vertex_index + 4] = ch_data.bot_right.x - margin;
		vertices[vertex_index + 5] = ch_data.bot_right.y;

		// 반복
		vertex_index = vertex_index + 6;

		//__________________________________________________________________________________________

		// 점 4
		// Vertices [1,0] // 네 번째 점
		rotated_pt = rotate_pt(loc, glm::vec2(xpos + w, ypos+h), lb.label_angle);

		vertices[vertex_index + 0] = rotated_pt.x;
		vertices[vertex_index + 1] = rotated_pt.y;

		// 라벨 원점
		vertices[vertex_index + 2] = loc.x;
		vertices[vertex_index + 3] = loc.y;

		// 텍스처 글리프 좌표
		vertices[vertex_index + 4] = ch_data.bot_right.x - margin;
		vertices[vertex_index + 5] = ch_data.top_left.y;

		// 반복
		vertex_index = vertex_index + 6;

		//__________________________________________________________________________________________
		x += (ch_data.Advance >> 6) * scale;

		//__________________________________________________________________________________________


		// 인덱스 버퍼 수정
		// 노드 인덱스 설정
		unsigned int t_id = ((indices_index / 6) * 4);
		// 삼각형 0,1,2
		indices[indices_index + 0] = t_id + 0;
		indices[indices_index + 1] = t_id + 1;
		indices[indices_index + 2] = t_id + 2;

		// 삼각형 2,3,0
		indices[indices_index + 3] = t_id + 2;
		indices[indices_index + 4] = t_id + 3;
		indices[indices_index + 5] = t_id + 0;

		// 증가
		indices_index = indices_index + 6;
	}

}


glm::vec2 label_text_store::rotate_pt(glm::vec2& rotate_about, glm::vec2 pt, float& rotation_angle)
{
	// 회전 지점 반환
	glm::vec2 translated_pt = pt - rotate_about;

	// 회전 적용
	float radians = (rotation_angle * 3.14159365f) / 180.0f; // 각도를 라디안으로 변환
	float cos_theta = cos(radians);
	float sin_theta = sin(radians);

	// 변환된 모서리의 회전된 지점
	glm::vec2 rotated_pt = glm::vec2((translated_pt.x * cos_theta) - (translated_pt.y * sin_theta),
		(translated_pt.x * sin_theta) + (translated_pt.y * cos_theta));

	return (rotated_pt + rotate_about);
}