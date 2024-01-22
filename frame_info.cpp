#include "frame_info.h"

FrameInfo::FrameInfo()
    : box_cnt_(0),
      square_size_(20.0f),
      fgbg_(cv::createBackgroundSubtractorMOG2(1000, 128, false)) {
}

FrameInfo::~FrameInfo() {}

// 프레임 정보 업데이트
void FrameInfo::UpdateFrame(const cv::Mat& new_frame) {
    // 새로운 프레임을 저장
    frame_ = new_frame;

    // 기존 프레임 정보를 초기화
    Clear();

    // 전경/배경 분리 적용
    fgbg_->apply(frame_, fgmask_);

    // 정사각형 영역 반복 처리
    uchar* frameData = frame_.data;
    int rows = frame_.rows / square_size_;
    int cols = frame_.cols / square_size_;

    // 정사각형 영역의 데이터 포인터 가져오기
    for (int y = 0; y < frame_.rows; y += square_size_) {
        for (int x = 0; x < frame_.cols; x += square_size_) {
            // 정사각형 영역의 데이터 포인터 가져오기
            uchar* data = frameData + (y * frame_.cols + x) * frame_.channels();

            // 정사각형 영역의 전경/배경 마스크 생성
            cv::Mat subRegion = fgmask_(cv::Rect(x, y, square_size_, square_size_));

            // 전경이 없는 경우 (배경 영역인 경우)
            if (cv::countNonZero(subRegion) == 0) {
                // 색상 정보 추출 및 텍스트 영역 생성
                cv::Vec3b color(data[2], data[1], data[0]);
                char hexColor[8];
                std::snprintf(hexColor, sizeof hexColor, "%02x%02x%02x", color[2], color[1], color[0]);
                text_area_.push_back(TextArea(x, y, hexColor));

                // NDS 계산 및 상자 개수 증가
                Utils::calcNDS(frame_.cols, frame_.rows, x + square_size_ / 2, y + square_size_ / 2, square_size_, vertices_);
                box_cnt_++;
            }
        }
    }
}

void FrameInfo::Clear() {
    box_cnt_ = 0;
    vertices_.clear();
    text_area_.clear();
}

cv::Mat FrameInfo::GetFrame() const {
    return frame_;
}

std::vector<float> FrameInfo::GetVertices() const {
    return vertices_;
}

int FrameInfo::GetBoxCnt() const {
    return box_cnt_;
}

float FrameInfo::GetSquareSize() const {
    return square_size_;
}

std::vector<TextArea> FrameInfo::GetTextAreas() const {
    return text_area_;
}

