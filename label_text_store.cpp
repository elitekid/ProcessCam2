#include "label_text_store.h"

label_text_store::label_text_store()
	: total_char_count(0)
{
	// ������
}

label_text_store::~label_text_store()
{
	// �Ҹ���
}

void label_text_store::init()
{
	// ��� �� �ʱ�ȭ
	labels.clear();
	main_font.create_atlas();
	total_char_count = 0;
}

void label_text_store::add_text(const char* label, glm::vec2 label_loc, glm::vec3 label_color,
	float geom_scale, float label_angle, float font_size)
{
	// �ӽ� ��� ����
	label_text temp_label;
	temp_label.label = label;
	temp_label.label_loc = label_loc;
	temp_label.label_color = label_color;
	temp_label.label_angle = label_angle;
	temp_label.label_size = font_size;

	// ���ο� ��Ҹ� ���� ���� Ȯ��
	labels.reserve(labels.size() + 1);

	// ��Ͽ� �߰�
	labels.push_back(temp_label);

	// ���� �� ������Ʈ
	total_char_count = total_char_count + strlen(label);
}

void label_text_store::set_buffers()
{
	// ���� ���̺� ���� ���� (4 ���� �������� �簢���� �����ϴµ�, 2 ���� ��ġ, 2 ���� ����, 2 ���� �ؽ�ó ��ǥ, 1 ���� ���� ID)

	unsigned int label_vertex_count = 4 * 6 * total_char_count;
	float* label_vertices = new float[label_vertex_count];

	// 6 ���� �ε����� �ﰢ���� ����
	unsigned int label_indices_count = 6 * total_char_count;
	unsigned int* label_indices = new unsigned int[label_indices_count];

	unsigned int label_v_index = 0;
	unsigned int label_i_index = 0;

	for (auto& lb : labels)
	{
		// �� ���ڿ� ���� ���� ä���
		get_buffer(lb, label_vertices, label_v_index, label_indices, label_i_index);
	}

	// ���̾ƿ� ����
	VertexBufferLayout label_layout;
	label_layout.AddFloat(2);  // ��ġ
	label_layout.AddFloat(2);  // ����
	label_layout.AddFloat(2);  // �ؽ�ó ��ǥ

	unsigned int label_vertex_size = label_vertex_count * sizeof(float);

	// ���� ����
	label_buffers.createBuffers((void*)label_vertices, label_vertex_size,
		(unsigned int*)label_indices, label_indices_count, label_layout, GL_STATIC_DRAW);

	// ������ ���� �迭 ����
	delete[] label_vertices;
	delete[] label_indices;
}
void label_text_store::clear_buffers()
{
	label_buffers.clearBuffers();
}

void label_text_store::paint_text()
{
	// ��� �� �׸���
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
	// ��ġ ��ǥ ����
	glm::vec2 loc = lb.label_loc;
	float x = loc.x;
	float y = loc.y;
	float scale =lb.label_size;
	//float scale = 1.0f;
	glm::vec2 rotated_pt;

	for (int i = 0; lb.label[i] != '\0'; ++i) 
	{
		// �۸��� ���� ��������
		char ch = lb.label[i];

		Character ch_data =	main_font.ch_atlas[ch];

		float xpos = x + (ch_data.Bearing.x * scale); // �»��
		float ypos = y - (ch_data.Size.y - ch_data.Bearing.y) * scale;

		float w = ch_data.Size.x * scale;
		float h = ch_data.Size.y * scale;

		float margin = 0.00001; // �������� �� ���� ���ڿ��� �̼��� ������ ������ ���� ��

		// �� 1
		// Vertices [0,0] // ù ��° ��
		rotated_pt = rotate_pt(loc, glm::vec2(xpos, ypos + h), lb.label_angle);

		vertices[vertex_index + 0] = rotated_pt.x;
		vertices[vertex_index + 1] = rotated_pt.y;

		// �� ����
		vertices[vertex_index + 2] = loc.x;
		vertices[vertex_index + 3] = loc.y;

		// �ؽ�ó �۸��� ��ǥ
		vertices[vertex_index + 4] = ch_data.top_left.x + margin;
		vertices[vertex_index + 5] = ch_data.top_left.y;

		// �ݺ�
		vertex_index = vertex_index + 6;

		//__________________________________________________________________________________________

		// �� 2
		// Vertices [0,1] // �� ��° ��
		rotated_pt = rotate_pt(loc, glm::vec2(xpos, ypos), lb.label_angle);

		vertices[vertex_index + 0] = rotated_pt.x;
		vertices[vertex_index + 1] = rotated_pt.y;

		// �� ����
		vertices[vertex_index + 2] = loc.x;
		vertices[vertex_index + 3] = loc.y;

		// �ؽ�ó �۸��� ��ǥ
		vertices[vertex_index + 4] = ch_data.top_left.x+ margin;
		vertices[vertex_index + 5] = ch_data.bot_right.y;

		// �ݺ�
		vertex_index = vertex_index + 6;

		//__________________________________________________________________________________________

		// �� 3
		// Vertices [1,1] // �� ��° ��
		rotated_pt = rotate_pt(loc, glm::vec2(xpos+w, ypos), lb.label_angle);

		vertices[vertex_index + 0] = rotated_pt.x;
		vertices[vertex_index + 1] = rotated_pt.y;

		// �� ����
		vertices[vertex_index + 2] = loc.x;
		vertices[vertex_index + 3] = loc.y;

		// �ؽ�ó �۸��� ��ǥ
		vertices[vertex_index + 4] = ch_data.bot_right.x - margin;
		vertices[vertex_index + 5] = ch_data.bot_right.y;

		// �ݺ�
		vertex_index = vertex_index + 6;

		//__________________________________________________________________________________________

		// �� 4
		// Vertices [1,0] // �� ��° ��
		rotated_pt = rotate_pt(loc, glm::vec2(xpos + w, ypos+h), lb.label_angle);

		vertices[vertex_index + 0] = rotated_pt.x;
		vertices[vertex_index + 1] = rotated_pt.y;

		// �� ����
		vertices[vertex_index + 2] = loc.x;
		vertices[vertex_index + 3] = loc.y;

		// �ؽ�ó �۸��� ��ǥ
		vertices[vertex_index + 4] = ch_data.bot_right.x - margin;
		vertices[vertex_index + 5] = ch_data.top_left.y;

		// �ݺ�
		vertex_index = vertex_index + 6;

		//__________________________________________________________________________________________
		x += (ch_data.Advance >> 6) * scale;

		//__________________________________________________________________________________________


		// �ε��� ���� ����
		// ��� �ε��� ����
		unsigned int t_id = ((indices_index / 6) * 4);
		// �ﰢ�� 0,1,2
		indices[indices_index + 0] = t_id + 0;
		indices[indices_index + 1] = t_id + 1;
		indices[indices_index + 2] = t_id + 2;

		// �ﰢ�� 2,3,0
		indices[indices_index + 3] = t_id + 2;
		indices[indices_index + 4] = t_id + 3;
		indices[indices_index + 5] = t_id + 0;

		// ����
		indices_index = indices_index + 6;
	}

}


glm::vec2 label_text_store::rotate_pt(glm::vec2& rotate_about, glm::vec2 pt, float& rotation_angle)
{
	// ȸ�� ���� ��ȯ
	glm::vec2 translated_pt = pt - rotate_about;

	// ȸ�� ����
	float radians = (rotation_angle * 3.14159365f) / 180.0f; // ������ �������� ��ȯ
	float cos_theta = cos(radians);
	float sin_theta = sin(radians);

	// ��ȯ�� �𼭸��� ȸ���� ����
	glm::vec2 rotated_pt = glm::vec2((translated_pt.x * cos_theta) - (translated_pt.y * sin_theta),
		(translated_pt.x * sin_theta) + (translated_pt.y * cos_theta));

	return (rotated_pt + rotate_about);
}