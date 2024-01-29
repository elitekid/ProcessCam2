#ifndef SHADER_H
#define SHADER_H

//#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include <filesystem>
#include <fstream>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/mat4x4.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <iostream>
#include <string>
#include <unordered_map>

class Shader {
 public:
  // 멤버 변수
  unsigned int id_;
  std::unordered_map<std::string, int> uniform_locations_;

  // 생성자/소멸자
  Shader();
  ~Shader();

  void deleteProgram();

  // 셰이더 생성
  void CreateShaderByPath(const char* vertex_path, const char* fragment_path);

  // 셰이더 ID
  unsigned int GetShaderId() const;

  // 셰이더 사용
  void Bind();
  void UnBind();

  // 유니폼 설정
  void SetUniform(const std::string& name, float x, float y);
  void SetUniform(const std::string& name, float x, float y, float z);
  void SetUniform(const std::string& name, float x, float y, float z, float w);
  void SetUniform(const std::string& name, float x);
  void SetUniform(const std::string& name, int x);
  void SetUniform(const std::string& name, glm::mat3 x, bool transpose);
  void SetUniform(const std::string& name, glm::mat4 x, bool transpose);
  void SetUniform(const std::string& name, glm::vec4 x);
  void SetUniform(const std::string& name, glm::vec3 x);
  void SetUniform(const std::string& name, glm::vec2 x);
  void SetUniform(int location, unsigned int texture_id);

 private:
  // 셰이더 소스 로드
  std::string LoadShaderSource(const char* path);

  // 셰이더 생성
  unsigned int CreateShader(GLenum type, const char* source);

  // 셰이더 링크
  void LinkShaders(unsigned int vertex_shader, unsigned int fragment_shader);

  // 유니폼 위치 검색
  int GetUniformLocation(const std::string& name);
};

#endif  // SHADER_H