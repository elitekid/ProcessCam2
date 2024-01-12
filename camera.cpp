#include <windows.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <ft2build.h>
#include FT_FREETYPE_H

#include "opencvwidget.h"
#include "textarea.h"
#include "geom_store.h"
#include "cam_store.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <ppl.h>
#include <omp.h>
#include <tuple>
#include <concurrent_vector.h>

using namespace cv;
using namespace std;
using namespace Concurrency;

GLuint shaderProgram1, shaderProgram2, VBO1, VAO1, EBO1, VBO2, VAO2, textureID_bg, textTexture;
cv::Ptr<cv::BackgroundSubtractorMOG2> fgbg = cv::createBackgroundSubtractorMOG2(1000, 128, false); // param -> history : 클수록 민감도 감소, varThreshold : 작을수록 작은 변화에도 반응, detectShadows: 그림자 검출 
ThreadedCamera cam;
Mat fgmask;

float squareSize = 20.0f;
int i;
int firstRendering = 1;

vector<TextArea> textAreas;
GLFWwindow* window = 0;
geom_store geomStore;
cam_store camStore;

float vertices1[] = {
    // Positions          // Texture Coordinates
     1.0f,  1.0f, 0.0f,   1.0f, 0.0f,  // 오른쪽 상단
     1.0f, -1.0f, 0.0f,   1.0f, 1.0f,  // 오른쪽 하단

    -1.0f, -1.0f, 0.0f,   0.0f, 1.0f,  // 왼쪽 하단
    -1.0f,  1.0f, 0.0f,   0.0f, 0.0f   // 왼쪽 상단
};

unsigned int indices1[] = {  // 0부터 시작한다는 것을 명심하세요!
    0, 1, 3,   // 첫 번째 삼각형
    1, 2, 3    // 두 번째 삼각형
};

std::vector<float> vertices2;

const char* vertexShaderSource1 = R"(
    #version 460 core
    layout (location = 0) in vec3 aPos;
    layout (location = 1) in vec2 aTexCoord;

    out vec2 TexCoord;

    void main()
    {
        gl_Position = vec4(aPos, 1.0);
        TexCoord = aTexCoord;
    }
)";

const char* fragmentShaderSource1 = R"(
    #version 460 core
    out vec4 FragColor;

    in vec2 TexCoord;

    uniform sampler2D textureID_bg;

    void main()
    {
        FragColor = texture(textureID_bg, TexCoord);
    }
)";

const char* vertexShaderSource2 = R"(
    #version 460 core
    layout (location = 0) in vec3 position; // <vec2 pos>
    void main()
    {
        gl_Position = vec4(position, 1.0);
    }  
)";

const char* fragmentShaderSource2 = R"(
    #version 460 core
    out vec4 FragColor;

    void main()
    {
        FragColor = vec4(0.0, 0.0, 0.0, 1.0); // or any other color you want
    }
)";

void countTextArea(cv::Mat& frame) {
    fgbg->apply(frame, fgmask);
    cv::Range range(0, frame.rows / squareSize);
    uchar* frameData = frame.data;
    int rows = frame.rows / squareSize;
    int cols = frame.cols / squareSize;
    double start_t = cv::getTickCount();
    vector<TextArea>& textAreas1 = textAreas;


    for (int y = 0; y < frame.rows; y += squareSize) {
        for (int x = 0; x < frame.cols; x += squareSize) {
            uchar* data = frameData + (y * frame.cols + x) * frame.channels();
            Mat subRegion = fgmask(cv::Rect(x, y, squareSize, squareSize));
            if (cv::countNonZero(subRegion) == 0) {
                Vec3b color(data[2], data[1], data[0]);
                char hexColor[8];
                std::snprintf(hexColor, sizeof hexColor, "%02x%02x%02x", color[2], color[1], color[0]);

                textAreas1.push_back(TextArea(x, y, hexColor));
                Utils::calcNDS(frame.cols, frame.rows, x + squareSize / 2, y + squareSize / 2, squareSize, vertices2);
                i++;
            }
        }
    }
}

void cameraToTexture(cv::Mat& frame) {
    if (!frame.empty()) {
        glad_glActiveTexture(GL_TEXTURE0);
        glad_glBindTexture(GL_TEXTURE_2D, textureID_bg);  // textureID_bg는 카메라 프레임을 업데이트한 OpenGL 텍스쳐의 ID여야 합니다.

        if (firstRendering) {
            glad_glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, frame.cols, frame.rows, 0, GL_BGR, GL_UNSIGNED_BYTE, frame.data);
            firstRendering = 0;
        }
        else {
            glad_glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, frame.cols, frame.rows, GL_BGR, GL_UNSIGNED_BYTE, frame.data);
        }
    }
}

GLuint compileShader(GLenum shaderType, const char* sourceCode) {
    GLuint shader = glad_glCreateShader(shaderType);
    glad_glShaderSource(shader, 1, &sourceCode, NULL);
    glad_glCompileShader(shader);

    GLint success;
    glad_glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[1024];
        glad_glGetShaderInfoLog(shader, sizeof(infoLog), NULL, infoLog);
        std::cerr << "Shader compilation failed: " << infoLog << std::endl;
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    return shader;
}

GLuint createshaderProgram(const char* vertexShaderCode, const char* fragmentShaderCode) {
    GLuint vertexShader = compileShader(GL_VERTEX_SHADER, vertexShaderCode);
    GLuint fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentShaderCode);

    GLuint program = glad_glCreateProgram();
    glad_glAttachShader(program, vertexShader);
    glad_glAttachShader(program, fragmentShader);
    glad_glLinkProgram(program);

    GLint success;
    glad_glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        char infoLog[1024];
        glad_glGetProgramInfoLog(program, sizeof(infoLog), NULL, infoLog);
        std::cerr << "Shader program linking failed: " << infoLog << std::endl;
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glad_glDeleteShader(vertexShader);
    glad_glDeleteShader(fragmentShader);

    return program;
}

void createBuffers1() {
    glad_glGenVertexArrays(1, &VAO1);
    glad_glGenBuffers(1, &VBO1);
    glad_glGenBuffers(1, &EBO1);

    glad_glBindVertexArray(VAO1);
    glad_glBindBuffer(GL_ARRAY_BUFFER, VBO1);
    glad_glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO1);

    glad_glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_STATIC_DRAW);
    glad_glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices1), indices1, GL_STATIC_DRAW);

    // Position attribute
    glad_glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glad_glEnableVertexAttribArray(0);

    // Texture attribute
    glad_glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glad_glEnableVertexAttribArray(1);
}

void createBuffers2() {
    glad_glGenVertexArrays(1, &VAO2);
    glad_glGenBuffers(1, &VBO2);

    glad_glBindVertexArray(VAO2);
    glad_glBindBuffer(GL_ARRAY_BUFFER, VBO2);

    glad_glBufferData(GL_ARRAY_BUFFER, vertices2.size() * sizeof(float), vertices2.data(), GL_STATIC_DRAW);

    // Position attribute
    glad_glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glad_glEnableVertexAttribArray(0);
}

void createTexture() {
    glad_glGenTextures(1, &textureID_bg);
    glad_glBindTexture(GL_TEXTURE_2D, textureID_bg);

    // Set texture parameters
    glad_glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glad_glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glad_glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glad_glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void processInput(GLFWwindow* window)
{
    // 종료키 : ESC, 오른쪽 숫자패드의 "-"
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_KP_SUBTRACT) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glad_glViewport(0, 0, width, height);
}

CamObj::CamObj(QObject* parent) : QObject(parent)
{
}

void CamObj::showCam(int camNum, QString colorCode)
{
    // 카메라 초기화
    cam.initialize(camNum);

    // glfw 초기화
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        exit(EXIT_FAILURE);
    }

    // OPENGL 버전 설정
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_SAMPLES, 4);

    // 화면 생성
    window = glfwCreateWindow(1280, 720, "Webcam Output", NULL, NULL);
    if (!window) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    // 주 모니터 화면
    GLFWmonitor* primary = glfwGetPrimaryMonitor();

    // 전체화면으로 설정
    const GLFWvidmode* mode = glfwGetVideoMode(primary);
    //glfwSetWindowMonitor(window, primary, 0, 0, mode->width, mode->height, mode->refreshRate);
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    

    // GLAD 로드
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        glfwTerminate();
        return;
    }
    gladLoadGL();

    glad_glEnable(GL_BLEND);
    glad_glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glad_glEnable(GL_MULTISAMPLE);

    // 멀티샘플 앤티앨리어싱 속성 설정
    glad_glHint(GL_MULTISAMPLE_FILTER_HINT_NV, GL_NICEST);

    // 멀티샘플 앤티앨리어싱을 원하는 프레임버퍼로 설정
    glad_glEnable(GL_MULTISAMPLE_ARB);

    // 쉐이더 프로그램 준비
    //shaderProgram1 = createshaderProgram(vertexShaderSource1, fragmentShaderSource1);
    //glad_glBindTexture(GL_TEXTURE_2D, textureID_bg);
    //glad_glUseProgram(shaderProgram1);
    //glad_glUniform1i(glad_glGetUniformLocation(shaderProgram1, "textureID_bg"), 0);
    //createBuffers1();

    shaderProgram2 = createshaderProgram(vertexShaderSource2, fragmentShaderSource2);
    glad_glUseProgram(shaderProgram2);
    createBuffers2();

    createTexture();

    camStore.set_camera_geometry();
    geomStore.set_geometry();

    glad_glViewport(0, 0, mode->width, mode->height);

    while (!glfwWindowShouldClose(window))
    {
        // 기존 버퍼 삭제
        geomStore.delete_buffers();

        // 키보드 입력 관리
        processInput(window);

        // 화면의 한 프레임 얻기
        Mat frame = cam.grabFrame();
        // 좌우 반전
        cv::flip(frame, frame, 1);

        // 화면 업데이트 하기위한 기존 화면 버퍼 제거
        glad_glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        // 화면을 채울 사각형 그릴 준비
        // i : 그릴 사각형 갯수 vertices2 : GPU에 넘길 사각형 좌표값의 배열
        i = 0;  // 초기화
        vertices2.clear();  // 초기화
        textAreas.clear();

        countTextArea(frame);   // i, vertices2 계산
        
        // 카메라 화면 텍스쳐로 맵핑
        cameraToTexture(frame);

        // 카메라 화면 그리기
        //glad_glUseProgram(shaderProgram1);
        //glad_glBindVertexArray(VAO1);
        //glad_glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        camStore.drawCam();

        // 사각형 그리기
        glad_glUseProgram(shaderProgram2);
        glad_glBindVertexArray(VAO2);
        glad_glBindBuffer(GL_ARRAY_BUFFER, VBO2);
        glad_glBufferData(GL_ARRAY_BUFFER, vertices2.size() * sizeof(float), vertices2.data(), GL_STATIC_DRAW);
        glad_glDrawArrays(GL_TRIANGLES, 0, 6 * i);

        // 사각형에 화면 해당 영역의 색상값 텍스트 출력
        geomStore.add_label(textAreas, frame.cols, frame.rows, squareSize);
        geomStore.paint_geometry();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // 메모리 해제
    glad_glDeleteTextures(1, &textureID_bg);
    glad_glDeleteTextures(1, &textTexture);
    glad_glDeleteVertexArrays(1, &VAO1);
    glad_glDeleteVertexArrays(1, &VAO2);
    glad_glDeleteBuffers(1, &VBO1);
    glad_glDeleteBuffers(1, &EBO1);
    glad_glDeleteBuffers(1, &VBO2);
    glad_glDeleteProgram(shaderProgram1);
    glad_glDeleteProgram(shaderProgram2);
    firstRendering = 1;
    cam.stop();
    glfwTerminate();
}