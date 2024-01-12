#include "texture.h"

Texture::Texture()
    : texture_id(0), local_buffer(nullptr), texture_width(0), texture_height(0)
{
}

Texture::~Texture()
{
    // ���� ���� �޸� ����
    if (local_buffer)
        stbi_image_free(local_buffer);

    // �ؽ�ó OpenGL �ڿ� ����
    glDeleteTextures(1, &texture_id);
}

void Texture::load(int cameraWidth, int cameraHeight)
{
    // �ؽ�ó ���� �� �ʱ�ȭ
    glGenTextures(1, &texture_id);
    glBindTexture(GL_TEXTURE_2D, texture_id);

    // �̹��� �����Ϳ� �ؽ�ó ���� ����
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, cameraWidth, cameraHeight, 0, GL_BGR, GL_UNSIGNED_BYTE, NULL);

    // �ؽ�ó ���͸� ����
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // texture_width�� texture_height�� ����
    texture_width = cameraWidth;
    texture_height = cameraHeight;
}

void Texture::update(unsigned char* cameraData)
{
    // �ؽ�ó�� ī�޶� ������ ������ ������Ʈ
    glBindTexture(GL_TEXTURE_2D, texture_id);
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, texture_width, texture_height, GL_BGR, GL_UNSIGNED_BYTE, cameraData);
}

void Texture::bind(unsigned int slot) const
{
    // �ؽ�ó ���� Ȱ��ȭ �� ���ε�
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, texture_id);
}

void Texture::unBind()
{
    // �ؽ�ó ���ε� ����
    glBindTexture(GL_TEXTURE_2D, 0);
}
