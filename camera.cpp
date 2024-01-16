#include "camera.h"

Camera::Camera() : status(true)
{
}
Camera::~Camera()
{
}
    // 초기화 함수 구현
void Camera::initialize(int camNum)
{
    stop(); // 이미 카메라가 열려 있다면 중지

    cap.open(camNum, CAP_DSHOW);
    double codec = 0x47504A4D; // MJPG

    cap.set(CAP_PROP_FOURCC, codec);
    //cap.open("C:/Users/SYNERGY-USER/Downloads/abc/bear.mp4", cv::CAP_V4L2);
    cap.set(CAP_PROP_FPS, 24);
    cap.set(CAP_PROP_FRAME_WIDTH, 2560);
    cap.set(CAP_PROP_FRAME_HEIGHT, 1440);

    status = false;
}

Mat Camera::getFrame()
{
    if (cap.isOpened()) {
        status = cap.read(frame);
    }

    if (status) {
        return frame;
    }
    return Mat();
}

void Camera::stop()
{
    cap.release();
}

int Camera::getCols() const {
    return cap.isOpened() ? static_cast< int >( cap.get(CAP_PROP_FRAME_WIDTH) ) : 0;
}

int Camera::getRows() const {
    return cap.isOpened() ? static_cast< int >( cap.get(CAP_PROP_FRAME_HEIGHT) ) : 0;
}
