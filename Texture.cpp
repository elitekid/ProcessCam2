#include "texture.h"

Texture::Texture()
    : texture_id_(0), local_buffer_(nullptr), texture_width_(0), texture_height_(0)
{
}

Texture::~Texture()
{
    if (this->texture_id_ != 0) {
        glDeleteTextures(1, &texture_id_);
    }
}

void Texture::Load(int width, int height)
{
    // 텍스처 생성 및 초기화
    glGenTextures(1, &texture_id_);
    glBindTexture(GL_TEXTURE_2D, texture_id_);

    // 이미지 데이터와 텍스처 형식 설정
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, NULL);

    // 텍스처 필터링 설정
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // texture_width와 texture_height에 저장
    texture_width_ = width;
    texture_height_ = height;
}

void Texture::Update(unsigned char* camera_data)
{
    // 텍스처에 카메라 프레임 데이터 업데이트
    glBindTexture(GL_TEXTURE_2D, texture_id_);
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, texture_width_, texture_height_, GL_BGR, GL_UNSIGNED_BYTE, camera_data);
}

void Texture::Bind(unsigned int slot) const
{
    // 텍스처 슬롯 활성화 및 바인딩
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, texture_id_);
}

void Texture::UnBind()
{
    // 텍스처 바인딩 해제
    glBindTexture(GL_TEXTURE_2D, 0);
}
