#include "camera.h"

Camera::Camera() : status_(true)
{
}
Camera::~Camera()
{
}
    // 초기화 함수 구현
void Camera::Init(int cam_num) {
    Stop(); // 이미 카메라가 열려 있다면 중지

    cap_.open(cam_num, cv::CAP_DSHOW);
    double codec = 0x47504A4D; // MJPG

    cap_.set(cv::CAP_PROP_FOURCC, codec);
    //cap.open("C:/Users/SYNERGY-USER/Downloads/abc/bear.mp4", cv::CAP_V4L2);
    cap_.set(cv::CAP_PROP_FPS, 24);
    cap_.set(cv::CAP_PROP_FRAME_WIDTH, 2560);
    cap_.set(cv::CAP_PROP_FRAME_HEIGHT, 1440);

    status_ = false;
}

cv::Mat Camera::GetFrame()
{
    if (cap_.isOpened()) {
        status_ = cap_.read(frame_);
    }

    if (status_) {
        return frame_;
    }
    return cv::Mat();
}

void Camera::Stop()
{
    cap_.release();
}

int Camera::GetCols() const {
    return cap_.isOpened() ? static_cast< int >( cap_.get(cv::CAP_PROP_FRAME_WIDTH) ) : 0;
}

int Camera::GetRows() const {
    return cap_.isOpened() ? static_cast< int >( cap_.get(cv::CAP_PROP_FRAME_HEIGHT) ) : 0;
}
