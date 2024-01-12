#pragma once
#include <iostream>
#include <map>
#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include "gBuffers.h"
#include <filesystem>

// FreeType
#include <ft2build.h>
#include FT_FREETYPE_H

/// FreeType�� ����Ͽ� �ε�� ���ڿ� ���õ� ��� ���� ������ �����ϴ� ����ü
struct Character
{
    glm::ivec2 Size;     // �۸����� ũ�� (�� �� ����)
    glm::ivec2 Bearing;  // ���̽����ο��� �۸����� ����/���� ������

    // ����: ���꽺(Advance)�� 1/64 �ȼ��� ���Դϴ�.
    // (ch.Advance >> 6) // 6��Ʈ ���������� ����Ʈ�Ͽ� �ȼ� ������ ��ȯ (2^6 = 64)
    unsigned int Advance;  // ���� �۸����� �����ϱ� ���� ���� ������

    glm::vec2 top_left;   // ��Ʋ�󽺿��� �� ������ ��ġ - �»�� [0,0]
    glm::vec2 bot_right;  // ��Ʋ�󽺿��� �� ������ ��ġ - ���ϴ� [1,1]
};

class font_atlas
{
public:
    bool atlasCreated = false;   // ��Ʋ�� ���� ���� �÷���
    unsigned int textureID;     // �ؽ�ó �ĺ���
    unsigned int TextureWidth;  // ��Ʋ���� ��ü �ʺ�
    unsigned int TextureHeight; // ��Ʋ���� ��ü ����
    std::map<char, Character> ch_atlas; // ���ڿ� �׿� ���� ������ �����ϴ� ��

    font_atlas();
    ~font_atlas();

    // ��Ʋ�󽺸� �����ϴ� �Լ�
    void create_atlas();

    // ��Ʋ�󽺸� ���ε��ϴ� �Լ�
    void Bind_atlas();

    // ��Ʋ�󽺸� ����ε��ϴ� �Լ�
    void UnBind_atlas();

};
