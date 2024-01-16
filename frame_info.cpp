#include "frame_info.h"

frame_info::frame_info()
    : boxCnt(0), squareSize(20.0f), fgbg(createBackgroundSubtractorMOG2(1000, 128, false))
{
}

frame_info::~frame_info()
{
}

// 프레임 정보 업데이트
void frame_info::updateFrame(const Mat& newFrame)
{
    // 새로운 프레임을 저장
    frame = newFrame;

    // 기존 프레임 정보를 초기화
    clear();

    // 전경/배경 분리 적용
    fgbg->apply(frame, fgmask);

    // 정사각형 영역 반복 처리
    uchar* frameData = frame.data;
    int rows = frame.rows / squareSize;
    int cols = frame.cols / squareSize;

    // 정사각형 영역의 데이터 포인터 가져오기
    for (int y = 0; y < frame.rows; y += squareSize) {
        for (int x = 0; x < frame.cols; x += squareSize) {
            // 정사각형 영역의 데이터 포인터 가져오기
            uchar* data = frameData + (y * frame.cols + x) * frame.channels();

            // 정사각형 영역의 전경/배경 마스크 생성
            Mat subRegion = fgmask(Rect(x, y, squareSize, squareSize));

            // 전경이 없는 경우 (배경 영역인 경우)
            if (cv::countNonZero(subRegion) == 0) {
                // 색상 정보 추출 및 텍스트 영역 생성
                Vec3b color(data[2], data[1], data[0]);
                char hexColor[8];
                std::snprintf(hexColor, sizeof hexColor, "%02x%02x%02x", color[2], color[1], color[0]);
                textAreas.push_back(TextArea(x, y, hexColor));

                // NDS 계산 및 상자 개수 증가
                Utils::calcNDS(frame.cols, frame.rows, x + squareSize / 2, y + squareSize / 2, squareSize, vertices);
                boxCnt++;
            }
        }
    }
}

Mat frame_info::getFrame() const
{
    return frame;
}

vector<float> frame_info::getVertices() const
{
    return vertices;
}

int frame_info::getBoxCnt() const
{
    return boxCnt;
}

float frame_info::getSquareSize() const
{
    return squareSize;
}

vector<TextArea> frame_info::getTextAreas() const
{
    return textAreas;
}

void frame_info::clear()
{
    boxCnt = 0;
    vertices.clear();
    textAreas.clear();
}

