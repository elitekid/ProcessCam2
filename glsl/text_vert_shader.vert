#version 460 core

uniform float zoomscale;   // �� ������ ��
uniform vec4 textColor;    // �ؽ�Ʈ ����

layout(location = 0) in vec2 position;       // ���� ��ġ �Է�
layout(location = 1) in vec2 origin;         // �ؽ�Ʈ ���� �Է�
layout(location = 2) in vec2 textureCoord;   // �ؽ�ó ��ǥ �Է�

out vec4 v_textureColor;  // �ؽ�Ʈ ���� ���
out vec2 v_textureCoord;  // �ؽ�ó ��ǥ ���

void main()
{
    // �� ������ �� ȸ���� ������ �� ��� ����
    mat4 scalingMatrix = mat4(1.0) * zoomscale;
    scalingMatrix[3][3] = 1.0f;

    // ���� ��ġ�� ��ȯ ����� �����մϴ�.
    vec4 finalPosition = scalingMatrix * vec4(position, 0.0f, 1.0f);

    // ���� �ؽ�Ʈ ������ ��ȯ ����� �����մϴ�.
    vec4 finalTextOrigin = scalingMatrix * vec4(origin, 0.0f, 1.0f);

    // �� �������� �����ϰ� ��ġ�� �����մϴ�.
    vec2 scaled_pt = vec2(finalPosition.x - finalTextOrigin.x, finalPosition.y - finalTextOrigin.y) / zoomscale;

    // ���� ��ġ�� �����մϴ�.
    gl_Position = vec4(finalPosition.x + scaled_pt.x, finalPosition.y + scaled_pt.y, 0.0f, 1.0f);

    // �۸����� �ؽ�ó ��ǥ�� ����մϴ�.
    v_textureCoord = textureCoord;

    // Fragment Shader�� �ؽ�Ʈ ������ �����մϴ�.
    v_textureColor = vec4(textColor);
}
