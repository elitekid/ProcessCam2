#include <windows.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "opencvwidget.h"
#include "textarea.h"
#include "text_geom_store.h"
#include "box_geom_store.h"
#include "cam_geom_store.h"
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

cv::Ptr<cv::BackgroundSubtractorMOG2> fgbg = cv::createBackgroundSubtractorMOG2(1000, 128, false); // param -> history : 클수록 민감도 감소, varThreshold : 작을수록 작은 변화에도 반응, detectShadows: 그림자 검출 
ThreadedCamera cam;
Mat fgmask;

float squareSize = 20.0f;
int i;

vector<TextArea> textAreas;
GLFWwindow* window = 0;
text_geom_store textGeomStore;
box_geom_store boxGeomStore;
cam_geom_store camGeomStore;

std::vector<float> vertices2;

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
    window = glfwCreateWindow(cam.getCols(), cam.getRows(), "Webcam Output", NULL, NULL);
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

    camGeomStore.set_camera_geometry(cam.getCols(), cam.getRows());
    boxGeomStore.set_box_geometry();
    textGeomStore.set_text_geometry();

    glad_glViewport(0, 0, mode->width, mode->height);

    while (!glfwWindowShouldClose(window))
    {
        // 기존 버퍼 삭제
        textGeomStore.delete_buffers();

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

        // 캠 화면 그리기
        camGeomStore.drawCam(frame.data);

        // 사각형 그리기
        boxGeomStore.drawBox(frame.data, i, vertices2);

        // 사각형에 화면 해당 영역의 색상값 텍스트 출력
        textGeomStore.add_label(textAreas, frame.cols, frame.rows, squareSize);
        textGeomStore.paint_geometry();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    cam.stop();
    glfwTerminate();
}