#include "cam_store.h"

cam_store::cam_store()
{
}

cam_store::~cam_store()
{
}

void cam_store::set_camera_geometry()
{
	float vertices[] = {
		// Positions          // Texture Coordinates
		 1.0f,  1.0f, 0.0f,   1.0f, 0.0f,  // ������ ���
		 1.0f, -1.0f, 0.0f,   1.0f, 1.0f,  // ������ �ϴ�

		-1.0f, -1.0f, 0.0f,   0.0f, 1.0f,  // ���� �ϴ�
		-1.0f,  1.0f, 0.0f,   0.0f, 0.0f   // ���� ���
	};

	unsigned int indices[] = {  // 0���� �����Ѵٴ� ���� ����ϼ���!
		0, 1, 3,   // ù ��° �ﰢ��
		1, 2, 3    // �� ��° �ﰢ��
	};

	// Set the geometry
	unsigned int node_vertices_count = 20;
	unsigned int node_indices_count = 6;

	VertexBufferLayout vb_tri;
	vb_tri.AddFloat(3);
	vb_tri.AddFloat(2);

	// Create the buffers
	unsigned int node_vertices_size = node_vertices_count * sizeof(float);
	cam_buffers.CreateBuffers(vertices, node_vertices_size, indices, node_indices_count, vb_tri);

	// Shader for the Cam
	cam_shader.create_shader("camera_frag_shader.vert", "camera_frag_shader.frag");\
}

void cam_store::drawCam()
{
	// draw Camera Frame
	cam_shader.Bind();
	cam_buffers.Bind();
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	cam_shader.UnBind();
	cam_buffers.UnBind();
}