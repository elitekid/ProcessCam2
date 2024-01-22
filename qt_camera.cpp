    #include "qt_camera.h"

    void QtCamera::processInput(GLFWwindow* window)
    {
        // 종료키 : ESC, 오른쪽 숫자패드의 "-"
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_KP_SUBTRACT) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);
    }

    void framebuffer_size_callback(GLFWwindow* window, int width, int height)
    {
        glad_glViewport(0, 0, width, height);
    }

    QtCamera::QtCamera(QObject* parent) : QObject(parent), window_(0)
    {
    }

    void QtCamera::ShowCam(int camera_num)
    {
        // 카메라 초기화
        cam_.Init(camera_num);

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
        window_ = glfwCreateWindow(cam_.GetCols(), cam_.GetRows(), "Webcam Output", NULL, NULL);
        if (!window_) {
            glfwTerminate();
            exit(EXIT_FAILURE);
        }

        // 주 모니터 화면
        GLFWmonitor* primary = glfwGetPrimaryMonitor();

        // 전체화면으로 설정
        const GLFWvidmode* mode = glfwGetVideoMode(primary);
        //glfwSetWindowMonitor(window, primary, 0, 0, mode->width, mode->height, mode->refreshRate);
        glfwMakeContextCurrent(window_);
        glfwSetFramebufferSizeCallback(window_, framebuffer_size_callback);
    

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
        cam_geom_store_.SetCameraGeometry(cam_.GetCols(), cam_.GetRows());
        // 박스 스토어 초기화
        box_geom_store_.SetBoxGeometry();
        // 텍스트 스토어 초기화
        text_geom_store_.SetTextGeometry();

        glad_glViewport(0, 0, mode->width, mode->height);

        while (!glfwWindowShouldClose(window_))
        {
            // 기존 버퍼 삭제
            text_geom_store_.DeleteBuffers();

            // 키보드 입력 관리
            processInput(window_);

            // 화면의 한 프레임 얻기
            Mat frame = cam_.GetFrame();
            // 좌우 반전
            cv::flip(frame, frame, 1);

            // 화면 업데이트 하기위한 기존 화면 버퍼 제거
            glad_glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            // 화면정보 업데이트
            frame_info_.UpdateFrame(frame);

            // 캠 화면 그리기
            cam_geom_store_.DrawCam(frame);
            // 사각형 그리기
            box_geom_store_.DrawBox(frame_info_);
            // 텍스트 그리기
            text_geom_store_.DrawColorCode(frame_info_);

            glfwSwapBuffers(window_);
            glfwPollEvents();
        }
        cam_.Stop();
        glfwTerminate();
    }