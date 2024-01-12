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
	// 멤버 변수
	unsigned int s_id; // OpenGL 프로그램 ID
	std::unordered_map<std::string, int> uniform_location_cache;
	std::string loadShaderSource(const char* fileName); // 파일에서 셰이더 소스를 로드하는 함수
	unsigned int loadShader(GLenum type, const char* fileName); // 주어진 타입의 셰이더를 로드하는 함수
	void linkProgram(unsigned int vertexShader, unsigned int fragmentShader); // 셰이더 프로그램을 링크하는 함수
	int get_uniform_location(const std::string uniform_name);
public:
	// 생성자/소멸자
	shader();
	~shader(); // OpenGL 자원을 정리하는 소멸자

	void create_shader(const char* vertexFile, const char* fragmentFile); // 버텍스와 프래그먼트 셰이더 파일 경로를 받는 함수
	// 셰이더 사용 함수
	void Bind(); // 셰이더 프로그램을 사용하는 함수
	void UnBind(); // 셰이더 프로그램 사용을 중단하는 함수

	// 유니폼 설정 함수
	void setUniform(std::string name, float X, float Y); // 2D float 유니폼 설정 함수
	void setUniform(std::string name, float X, float Y, float Z); // 3D float 유니폼 설정 함수
	void setUniform(std::string name, float X, float Y, float Z, float W); // 4D float 유니폼 설정 함수
	void setUniform(std::string name, float X); // float 유니폼 설정 함수
	void setUniform(std::string name, int X); // 정수 유니폼 설정 함수
	void setUniform(std::string name, glm::mat3 X, bool transpose); // mat3 유니폼 설정 함수
	void setUniform(std::string name, glm::mat4 X, bool transpose);  // mat4 유니폼 설정 함수
	void setUniform(std::string name, glm::vec4 X); // vec4 유니폼 설정 함수
	void setUniform(std::string name, glm::vec3 X); // vec3 유니폼 설정 함수
	void setUniform(std::string name, glm::vec2 X); // vec2 유니폼 설정 함수
	void setUniform(int i, unsigned int tid); // 텍스처 유니폼 설정 함수
	unsigned int get_shader_id() const;
};
