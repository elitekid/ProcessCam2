#include "texture.h"

Texture::Texture()
    : texture_id(0), local_buffer(nullptr), texture_width(0), texture_height(0)
{
}

Texture::~Texture()
{
    // 로컬 버퍼 메모리 해제
    if (local_buffer)
        stbi_image_free(local_buffer);

    // 텍스처 OpenGL 자원 해제
    glDeleteTextures(1, &texture_id);
}

void Texture::load(int cameraWidth, int cameraHeight)
{
    // 텍스처 생성 및 초기화
    glGenTextures(1, &texture_id);
    glBindTexture(GL_TEXTURE_2D, texture_id);

    // 이미지 데이터와 텍스처 형식 설정
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, cameraWidth, cameraHeight, 0, GL_BGR, GL_UNSIGNED_BYTE, NULL);

    // 텍스처 필터링 설정
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // texture_width와 texture_height에 저장
    texture_width = cameraWidth;
    texture_height = cameraHeight;
}

void Texture::update(unsigned char* cameraData)
{
    // 텍스처에 카메라 프레임 데이터 업데이트
    glBindTexture(GL_TEXTURE_2D, texture_id);
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, texture_width, texture_height, GL_BGR, GL_UNSIGNED_BYTE, cameraData);
}

void Texture::bind(unsigned int slot) const
{
    // 텍스처 슬롯 활성화 및 바인딩
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, texture_id);
}

void Texture::unBind()
{
    // 텍스처 바인딩 해제
    glBindTexture(GL_TEXTURE_2D, 0);
}
