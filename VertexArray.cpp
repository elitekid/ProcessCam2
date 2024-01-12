#include "VertexArray.h"
VertexArray::VertexArray()
	:va_id(0)
{
	// Empty constructor at program start
}

VertexArray::~VertexArray()
{
	// Check if the vertex array ID is valid
	if (this->va_id != 0) {
		// Delete the vertex array
		glDeleteVertexArrays(1, &va_id);
	}
	// Additional cleanup or logging if needed
}

void VertexArray::deleteVertexArray()
{
	// Main Constructor: generates a unique vertex array object ID.
	glDeleteVertexArrays(1, &va_id);
}

void VertexArray::createVertexArray()
{
	// Main Constructor: generates a unique vertex array object ID.
	glGenVertexArrays(1, &va_id);
}

void VertexArray::Bind() const
{
	// Binds the vertex array object for use with subsequent OpenGL calls.
	glBindVertexArray(va_id);
}

void VertexArray::UnBind() const
{
	// Unbinds the currently bound vertex array object.
	glBindVertexArray(0);
}


/*
�Լ��� �Ű������� ������ �����ϴ�:
VertexBuffer& vb: ���� �����Ͱ� ���Ե� ���ؽ� ���� ��ü�� ���� �����Դϴ�.
Layout�� ������ �����մϴ�
const int& index: �� ���� �Ӽ��� ����� ���� �ε����Դϴ�.
const int& size: ���� �Ӽ��� ���� ��� ���Դϴ� (��: xyz ��ǥ�� ��� 3, rgba ������ ��� 4 ��).
const int& stride: ���ؽ� ���� ��ü���� �������� ���� ���� �Ÿ���, ���۰� �����ε� ���� �����͸� ������ �� �����մϴ� (��: xyzrgba, xyznxynzrgba ��).
const int& offset: ���ؽ� ���� ��ü���� ���� �Ӽ��� ù ��° ���� ����� �������Դϴ�.
*/
void VertexArray::AddBuffer(const VertexBuffer& vbo, const VertexBufferLayout& layout)
{
	// ���ؽ� �迭 ��ü�� ���� ��ü�� �����մϴ�.
	// ���ؽ� �迭 ��ü�� ���ε��մϴ�.
	Bind();

	// ���ؽ� ���� ��ü�� ���ε��մϴ�.
	vbo.Bind();

	const auto& elements = layout.GetElements();
	unsigned int offset = 0;

	for (int i = 0; i < elements.size(); i++)
	{
		const auto& element = elements[i];
		// ������ ���� �ε����� ���� ���ؽ� �Ӽ� �迭�� Ȱ��ȭ�մϴ�.
		glEnableVertexAttribArray(i);

		// ������ ���� �ε����� ���� ���ؽ� �Ӽ� �����͸� �����մϴ�.
		// �̴� ��� ���ؽ� �����͸� �ؼ��ؾ� �ϴ��� OpenGL�� �˷��ݴϴ�.
		glVertexAttribPointer(i, element.count, element.type,
			element.normalized, layout.GetStride(), (const void*)(uintptr_t)offset);

		offset += element.count * VertexBufferElement::GetSizeOfType(element.type);
	}

	// ���ؽ� ���� ��ü�� ����ε��մϴ�.
	vbo.UnBind();

	// ���ؽ� �迭 ��ü�� ����ε��մϴ�.
	UnBind();
}
