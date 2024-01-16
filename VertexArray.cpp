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
함수의 매개변수는 다음과 같습니다:
VertexBuffer& vb: 정점 데이터가 포함된 버텍스 버퍼 객체에 대한 참조입니다.
Layout은 다음을 포함합니다
const int& index: 이 정점 속성이 연결된 버퍼 인덱스입니다.
const int& size: 정점 속성의 구성 요소 수입니다 (예: xyz 좌표의 경우 3, rgba 색상의 경우 4 등).
const int& stride: 버텍스 버퍼 객체에서 연속적인 정점 간의 거리로, 버퍼가 교차로된 정점 데이터를 포함할 때 유용합니다 (예: xyzrgba, xyznxynzrgba 등).
const int& offset: 버텍스 버퍼 객체에서 정점 속성의 첫 번째 구성 요소의 오프셋입니다.
*/
void VertexArray::AddBuffer(const VertexBuffer& vbo, const VertexBufferLayout& layout)
{
	// 버텍스 배열 객체에 버퍼 객체를 연결합니다.
	// 버텍스 배열 객체를 바인딩합니다.
	Bind();

	// 버텍스 버퍼 객체를 바인딩합니다.
	vbo.Bind();

	const auto& elements = layout.GetElements();
	unsigned int offset = 0;

	for (int i = 0; i < elements.size(); i++)
	{
		const auto& element = elements[i];
		// 지정된 버퍼 인덱스에 대한 버텍스 속성 배열을 활성화합니다.
		glEnableVertexAttribArray(i);

		// 지정된 버퍼 인덱스에 대한 버텍스 속성 포인터를 설정합니다.
		// 이는 어떻게 버텍스 데이터를 해석해야 하는지 OpenGL에 알려줍니다.
		glVertexAttribPointer(i, element.count, element.type,
			element.normalized, layout.GetStride(), (const void*)(uintptr_t)offset);

		offset += element.count * VertexBufferElement::GetSizeOfType(element.type);
	}

	// 버텍스 버퍼 객체를 언바인드합니다.
	vbo.UnBind();

	// 버텍스 배열 객체를 언바인드합니다.
	UnBind();
}
