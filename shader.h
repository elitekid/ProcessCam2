#pragma once

#include<iostream>
#include<fstream>
#include<string>
#include<unordered_map>
#include <filesystem>

#include<glad\glad.h>
#include<GLFW\glfw3.h>

#include<glm\glm.hpp>
#include<glm\vec2.hpp>
#include<glm\vec3.hpp>
#include<glm\vec4.hpp>
#include<glm\mat4x4.hpp>
#include<glm\gtc\type_ptr.hpp>

class shader
{
private:
	// ��� ����
	unsigned int s_id; // OpenGL ���α׷� ID
	std::unordered_map<std::string, int> uniform_location_cache;
	std::string loadShaderSource(const char* fileName); // ���Ͽ��� ���̴� �ҽ��� �ε��ϴ� �Լ�
	unsigned int loadShader(GLenum type, const char* fileName); // �־��� Ÿ���� ���̴��� �ε��ϴ� �Լ�
	void linkProgram(unsigned int vertexShader, unsigned int fragmentShader); // ���̴� ���α׷��� ��ũ�ϴ� �Լ�
	int get_uniform_location(const std::string uniform_name);
public:
	// ������/�Ҹ���
	shader();
	~shader(); // OpenGL �ڿ��� �����ϴ� �Ҹ���

	void create_shader(const char* vertexFile, const char* fragmentFile); // ���ؽ��� �����׸�Ʈ ���̴� ���� ��θ� �޴� �Լ�
	// ���̴� ��� �Լ�
	void Bind(); // ���̴� ���α׷��� ����ϴ� �Լ�
	void UnBind(); // ���̴� ���α׷� ����� �ߴ��ϴ� �Լ�

	// ������ ���� �Լ�
	void setUniform(std::string name, float X, float Y); // 2D float ������ ���� �Լ�
	void setUniform(std::string name, float X, float Y, float Z); // 3D float ������ ���� �Լ�
	void setUniform(std::string name, float X, float Y, float Z, float W); // 4D float ������ ���� �Լ�
	void setUniform(std::string name, float X); // float ������ ���� �Լ�
	void setUniform(std::string name, int X); // ���� ������ ���� �Լ�
	void setUniform(std::string name, glm::mat3 X, bool transpose); // mat3 ������ ���� �Լ�
	void setUniform(std::string name, glm::mat4 X, bool transpose);  // mat4 ������ ���� �Լ�
	void setUniform(std::string name, glm::vec4 X); // vec4 ������ ���� �Լ�
	void setUniform(std::string name, glm::vec3 X); // vec3 ������ ���� �Լ�
	void setUniform(std::string name, glm::vec2 X); // vec2 ������ ���� �Լ�
	void setUniform(int i, unsigned int tid); // �ؽ�ó ������ ���� �Լ�
	unsigned int get_shader_id() const;
};
