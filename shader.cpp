#include "shader.h"

Shader::Shader() : id_(0), uniform_locations_() {}

Shader::~Shader() {
  if (this->id_ != 0) {
    glDeleteProgram(this->id_);
  }
}

void Shader::CreateShaderByPath(const char* vertex_path,
                                const char* fragment_path) {
  // 버텍스 셰이더를 생성합니다.
  unsigned int vertexShader = CreateShader(GL_VERTEX_SHADER, vertex_path);

  // 프레그먼트 셰이더를 생성합니다.
  unsigned int fragmentShader = CreateShader(GL_FRAGMENT_SHADER, fragment_path);

  // 생성한 셰이더들을 프로그램으로 연결합니다.
  LinkShaders(vertexShader, fragmentShader);

  // 셰이더를 더 이상 사용하지 않으므로 자원을 해제합니다.
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);
}

unsigned int Shader::GetShaderId() const {
	return id_;
}

// Load shader source from file and return as string
std::string Shader::LoadShaderSource(const char* path) {
  std::string temp =
      "";  // Temporary string to store each line of the shader source
  std::string src = "";  // Final string to store the entire shader source

  std::ifstream in_file;  // Input file stream for reading from file

  // std::filesystem::path original_dir = std::filesystem::current_path();
  // std::filesystem::current_path("C:/Users/HFXMSZ/OneDrive - LR/
  // Documents/Programming/Other
  // programs/Cpp_projects/Truss_static_analysis_cpp/Truss_static_analysis_cpp/src/geometry_store/shaders/");

  // Open the file with the given file name
  in_file.open(path);

  // std::filesystem::current_path(original_dir);

  if (in_file.is_open())  // Check if file was successfully opened
  {
    while (std::getline(in_file, temp))  // Read each line from file
      src += temp + "\n";  // Append each line to the final shader source string
                           // with a newline character
  } else {
    std::cout << "ERROR::SHADER::COULD_NOT_OPEN_FILE: " << path
              << "\n";  // Print error message if file could not be opened
  }

  in_file.close();  // Close the file

  //// Replace the #version directive in the shader source with a default
  ///version number
  // src.replace(src.find("#version"), 12, "#version 330"); // Replace with
  // desired version number

  return src;  // Return the final shader source string
}

// 파일 경로로부터 셰이더 소스를 읽어오고 셰이더를 컴파일합니다.
unsigned int Shader::CreateShader(GLenum type, const char* source) {
  char infoLog[512];
  int success;

  // 주어진 유형의 셰이더 객체를 생성합니다.
  unsigned int shader = glCreateShader(type);

  // 파일에서 셰이더 소스를 읽어옵니다.
  std::string str_src = this->LoadShaderSource(source);
  const char* src = str_src.c_str();

  // 셰이더 소스를 설정하고 컴파일합니다.
  glShaderSource(shader, 1, &src, NULL);
  glCompileShader(shader);

  // 셰이더 컴파일 상태를 확인합니다.
  glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(shader, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::COULD_NOT_COMPILE_SHADER: " << source << "\n";
    std::cout << infoLog << "\n";
  }

  return shader;  // 컴파일된 셰이더 객체를 반환합니다.
}

// 버텍스와 프레그먼트 셰이더를 링크하여 셰이더 프로그램을 생성합니다.
void Shader::LinkShaders(unsigned int vertex_shader,
                         unsigned int fragment_shader) {
  char infoLog[512];
  int success;

  // 셰이더 프로그램 객체를 생성합니다.
  this->id_ = glCreateProgram();

  // 버텍스 셰이더를 셰이더 프로그램에 첨부합니다.
  glAttachShader(this->id_, vertex_shader);

  // 프레그먼트 셰이더를 셰이더 프로그램에 첨부합니다.
  glAttachShader(this->id_, fragment_shader);

  // 셰이더 프로그램을 링크합니다.
  glLinkProgram(this->id_);

  // 셰이더 프로그램 링크 상태를 확인합니다.
  glGetProgramiv(this->id_, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(this->id_, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::COULD_NOT_LINK_PROGRAM"
              << "\n";
    std::cout << infoLog << "\n";
  }

  glUseProgram(0);  // 셰이더 프로그램 언바인드
}

// 셰이더 프로그램에서 uniform 변수의 위치를 가져옵니다.
int Shader::GetUniformLocation(const std::string& name) {
  // 이미 해시 테이블에 해당 이름의 위치가 저장되어 있는지 확인합니다.
  if (uniform_locations_.find(name) != uniform_locations_.end()) {
    return uniform_locations_[name];
  }

  // 위치가 저장되어 있지 않다면 glGetUniformLocation 함수를 호출하여 찾고
  // 저장합니다.
  int uniform_location_id = glGetUniformLocation(this->id_, name.c_str());
  uniform_locations_[name] = uniform_location_id;

  return uniform_location_id;
}

// 셰이더 프로그램을 활성화하여 사용합니다.
void Shader::Bind() { glUseProgram(this->id_); }

// 셰이더 프로그램을 비활성화하여 사용하지 않습니다.
void Shader::UnBind() { glUseProgram(0); }

// 2D float uniform 값을 설정합니다.
void Shader::SetUniform(const std::string& name, float x, float y) {
  Bind();  // 셰이더 프로그램을 사용합니다.

  // 제공된 이름으로부터 uniform 위치를 가져옵니다.
  unsigned int uniformLocation = glGetUniformLocation(this->id_, name.c_str());

  // 2D float uniform에 X 및 Y의 제공된 값으로 설정합니다.
  glUniform2f(uniformLocation, x, y);

  UnBind();  // 셰이더 프로그램을 사용하지 않습니다.
}

// 3D float uniform 값을 설정합니다.
void Shader::SetUniform(const std::string& name, float x, float y, float z) {
  Bind();  // 셰이더 프로그램을 사용합니다.

  // 제공된 이름으로부터 uniform 위치를 가져옵니다.
  int uniformLocation = glGetUniformLocation(this->id_, name.c_str());

  // 3D float uniform에 X, Y 및 Z의 제공된 값으로 설정합니다.
  glUniform3f(uniformLocation, x, y, z);

  UnBind();  // 셰이더 프로그램을 사용하지 않습니다.
}

// 4D float uniform 값을 설정합니다.
void Shader::SetUniform(const std::string& name, float x, float y, float z,
                        float w) {
  Bind();  // 셰이더 프로그램을 사용합니다.

  // 제공된 이름으로부터 uniform 위치를 가져옵니다.
  int uniformLocation = glGetUniformLocation(this->id_, name.c_str());

  // 4D float uniform에 X, Y, Z 및 W의 제공된 값으로 설정합니다.
  glUniform4f(uniformLocation, x, y, z, w);

  UnBind();  // 셰이더 프로그램을 사용하지 않습니다.
}

// 1D float uniform 값을 설정합니다.
void Shader::SetUniform(const std::string& name, float x) {
  Bind();  // 셰이더 프로그램을 사용합니다.

  // 제공된 이름으로부터 uniform 위치를 가져옵니다.
  int uniformLocation = glGetUniformLocation(this->id_, name.c_str());

  // 1D float uniform에 제공된 값으로 설정합니다.
  glUniform1f(uniformLocation, x);

  UnBind();  // 셰이더 프로그램을 사용하지 않습니다.
}

// 1D int uniform 값을 설정합니다.
void Shader::SetUniform(const std::string& name, int x) {
  Bind();  // 셰이더 프로그램을 사용합니다.

  // 제공된 이름으로부터 uniform 위치를 가져옵니다.
  int uniformLocation = glGetUniformLocation(this->id_, name.c_str());

  // 1D int uniform에 제공된 값으로 설정합니다.
  glUniform1i(uniformLocation, x);

  UnBind();  // 셰이더 프로그램을 사용하지 않습니다.
}
// mat3 uniform 값을 설정하는 함수
void Shader::SetUniform(const std::string& name, glm::mat3 x, bool transpose) {
  Bind();  // 셰이더 프로그램을 사용합니다.

  // 제공된 이름으로부터 uniform 위치를 가져옵니다.
  int uniformLocation = glGetUniformLocation(this->id_, name.c_str());

  if (transpose) {
    // transpose 옵션이 활성화되어 있으면 mat3 uniform에 전달된 행렬의
    // 전치(transpose)를 설정합니다.
    glUniformMatrix3fv(uniformLocation, 1, GL_TRUE,
                       glm::value_ptr(glm::transpose(x)));
  } else {
    // transpose 옵션이 비활성화되어 있으면 mat3 uniform에 전달된 행렬을
    // 설정합니다.
    glUniformMatrix3fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(x));
  }

  UnBind();  // 셰이더 프로그램을 사용하지 않습니다.
}

// mat4 uniform 값을 설정하는 함수
void Shader::SetUniform(const std::string& name, glm::mat4 x, bool transpose) {
  Bind();  // 셰이더 프로그램을 사용합니다.

  // 제공된 이름으로부터 uniform 위치를 가져옵니다.
  int uniformLocation = glGetUniformLocation(this->id_, name.c_str());

  if (transpose) {
    // transpose 옵션이 활성화되어 있으면 mat4 uniform에 전달된 행렬의
    // 전치(transpose)를 설정합니다.
    glUniformMatrix4fv(uniformLocation, 1, GL_TRUE,
                       glm::value_ptr(glm::transpose(x)));
  } else {
    // transpose 옵션이 비활성화되어 있으면 mat4 uniform에 전달된 행렬을
    // 설정합니다.
    glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(x));
  }

  UnBind();  // 셰이더 프로그램을 사용하지 않습니다.
}

// vec4 uniform 값을 설정하는 함수
void Shader::SetUniform(const std::string& name, glm::vec4 x) {
  Bind();  // 셰이더 프로그램을 사용합니다.

  // 제공된 이름으로부터 uniform 위치를 가져옵니다.
  int uniformLocation = glGetUniformLocation(this->id_, name.c_str());

  // vec4 uniform에 제공된 값으로 설정합니다.
  glUniform4fv(uniformLocation, 1, glm::value_ptr(x));

  UnBind();  // 셰이더 프로그램을 사용하지 않습니다.
}

// vec3 uniform 값을 설정하는 함수
void Shader::SetUniform(const std::string& name, glm::vec3 x) {
  Bind();  // 셰이더 프로그램을 사용합니다.

  // 제공된 이름으로부터 uniform 위치를 가져옵니다.
  int uniformLocation = glGetUniformLocation(this->id_, name.c_str());

  // vec3 uniform에 제공된 값으로 설정합니다.
  glUniform3fv(uniformLocation, 1, glm::value_ptr(x));

  UnBind();  // 셰이더 프로그램을 사용하지 않습니다.
}

// vec2 uniform 값을 설정하는 함수
void Shader::SetUniform(const std::string& name, glm::vec2 x) {
  Bind();  // 셰이더 프로그램을 사용합니다.

  // 제공된 이름으로부터 uniform 위치를 가져옵니다.
  int uniformLocation = glGetUniformLocation(this->id_, name.c_str());

  // vec2 uniform에 제공된 값으로 설정합니다.
  glUniform2fv(uniformLocation, 1, glm::value_ptr(x));

  UnBind();  // 셰이더 프로그램을 사용하지 않습니다.
}

// 텍스처 uniform 값을 설정하는 함수
void Shader::SetUniform(int i, unsigned int tid) {
  Bind();  // 셰이더 프로그램을 사용합니다.

  // 텍스처 단위 i를 활성화합니다.
  glActiveTexture(GL_TEXTURE0 + i);

  // 제공된 텍스처 ID (tid)를 현재 활성화된 텍스처 단위에 바인딩합니다.
  glBindTexture(GL_TEXTURE_2D, tid);

  // 셰이더 프로그램에게 텍스처 Sampler의 값을 텍스처 단위 인덱스 i로 설정하도록
  // 알립니다.
  glUniform1i(glGetUniformLocation(this->id_, "textureSampler"), i);

  UnBind();  // 셰이더 프로그램을 사용하지 않습니다.
}
