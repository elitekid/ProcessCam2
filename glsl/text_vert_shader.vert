#version 460 core

uniform float zoomscale;   // 줌 스케일 값
uniform vec4 textColor;    // 텍스트 색상

layout(location = 0) in vec2 position;       // 정점 위치 입력
layout(location = 1) in vec2 origin;         // 텍스트 원점 입력
layout(location = 2) in vec2 textureCoord;   // 텍스처 좌표 입력

out vec4 v_textureColor;  // 텍스트 색상 출력
out vec2 v_textureCoord;  // 텍스처 좌표 출력

void main()
{
    // 줌 스케일 및 회전을 적용한 모델 행렬 생성
    mat4 scalingMatrix = mat4(1.0) * zoomscale;
    scalingMatrix[3][3] = 1.0f;

    // 최종 위치에 변환 행렬을 적용합니다.
    vec4 finalPosition = scalingMatrix * vec4(position, 0.0f, 1.0f);

    // 최종 텍스트 원점에 변환 행렬을 적용합니다.
    vec4 finalTextOrigin = scalingMatrix * vec4(origin, 0.0f, 1.0f);

    // 줌 스케일을 제거하고 위치를 조정합니다.
    vec2 scaled_pt = vec2(finalPosition.x - finalTextOrigin.x, finalPosition.y - finalTextOrigin.y) / zoomscale;

    // 최종 위치를 설정합니다.
    gl_Position = vec4(finalPosition.x + scaled_pt.x, finalPosition.y + scaled_pt.y, 0.0f, 1.0f);

    // 글리프의 텍스처 좌표를 계산합니다.
    v_textureCoord = textureCoord;

    // Fragment Shader로 텍스트 색상을 전달합니다.
    v_textureColor = vec4(textColor);
}
