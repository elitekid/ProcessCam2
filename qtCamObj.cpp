    #include "qtCamObj.h"

    void QtCamObj::processInput(GLFWwindow* window)
    {
        // 종료키 : ESC, 오른쪽 숫자패드의 "-"
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_KP_SUBTRACT) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);
    }

    void framebuffer_size_callback(GLFWwindow* window, int width, int height)
    {
        glad_glViewport(0, 0, width, height);
    }

    QtCamObj::QtCamObj(QObject* parent) : QObject(parent), window(0)
    {
    }

    void QtCamObj::showCam(int camNum, QString colorCode)
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

        // 캠 화면 스토어 초기화
        camGeomStore.setCameraGeometry(cam.getCols(), cam.getRows());
        // 박스 스토어 초기화
        boxGeomStore.setBoxGeometry();
        // 텍스트 스토어 초기화
        textGeomStore.setTextGeometry();

        glad_glViewport(0, 0, mode->width, mode->height);

        while (!glfwWindowShouldClose(window))
        {
            // 기존 버퍼 삭제
            textGeomStore.deleteBuffers();

            // 키보드 입력 관리
            processInput(window);

            // 화면의 한 프레임 얻기
            Mat frame = cam.getFrame();
            // 좌우 반전
            cv::flip(frame, frame, 1);

            // 화면 업데이트 하기위한 기존 화면 버퍼 제거
            glad_glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            // 화면정보 업데이트
            frameInfo.updateFrame(frame);

            // 캠 화면 그리기
            camGeomStore.drawCam(frame);
            // 사각형 그리기
            boxGeomStore.drawBox(frameInfo);
            // 텍스트 그리기
            textGeomStore.drawText(frameInfo);

            glfwSwapBuffers(window);
            glfwPollEvents();
        }
        cam.stop();
        glfwTerminate();
    }