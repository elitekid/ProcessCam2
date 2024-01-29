#include "util.h"

void Utils::hexToNormalizedFloat(const std::string & hex_code, float& red, float& green, float& blue) {
    // HEX 문자열을 2자리씩 끊어서 16진수로 변환
    std::string redHex = hex_code.substr(0, 2);
    std::string greenHex = hex_code.substr(2, 2);
    std::string blueHex = hex_code.substr(4, 2);

    // 16진수를 정수로 변환하여 0~255 범위로 저장
    int redInt = std::stoi(redHex, nullptr, 16);
    int greenInt = std::stoi(greenHex, nullptr, 16);
    int blueInt = std::stoi(blueHex, nullptr, 16);

    // 정규화하여 0.0 ~ 1.0 범위로 저장
    red = static_cast<float>(redInt) / 255.0f;
    green = static_cast<float>(greenInt) / 255.0f;
    blue = static_cast<float>(blueInt) / 255.0f;
}

std::vector<int> Utils::findCommonDivisors(int num1, int num2) {
    std::vector<int> commonDivisors;

    // 두 숫자 중 작은 숫자까지만 반복하여 공약수를 찾습니다.
    int smallerNum = (num1 < num2) ? num1 : num2;
    for (int i = 1; i <= smallerNum; ++i) {
        if (num1 % i == 0 && num2 % i == 0) {
            commonDivisors.push_back(i);
        }
    }

    return commonDivisors;
}

void Utils::calcNDS(int w, int h, float x, float y, float square_size, std::vector<float>& vertices) {
    // 정사각형의 중심 좌표 (20, 20)를 NDC로 매핑
    float ndcX = (x / w) * 2.0f - 1.0f;
    float ndcY = 1.0f - (y / h) * 2.0f;

    // 정사각형의 크기를 NDC로 매핑
    float ndcSizeX = (square_size / w) * 2.0f;
    float ndcSizeY = (square_size / h) * 2.0f;

    // 정사각형의 꼭지점 좌표 계산
    float topLeftX = ndcX - (ndcSizeX / 2.0f);
    float topLeftY = ndcY + (ndcSizeY / 2.0f);

    float bottomRightX = ndcX + (ndcSizeX / 2.0f);
    float bottomRightY = ndcY - (ndcSizeY / 2.0f);

    // 좌표만 넣기
    vertices.insert(vertices.end(), {
        topLeftX, topLeftY, 0.0f,  // 왼쪽 상단
        bottomRightX, topLeftY, 0.0f,  // 오른쪽 상단
        bottomRightX, bottomRightY, 0.0f,   // 오른쪽 하단

        topLeftX, topLeftY, 0.0f,   // 왼쪽 상단
        bottomRightX, bottomRightY, 0.0f,   // 오른쪽 하단
        topLeftX, bottomRightY, 0.0f   // 왼쪽 하단
     });
}

std::filesystem::path Utils::GetFontPath() {
    std::string folderPath = "fonts/";

    // 현재 작업 디렉토리의 절대 경로를 얻어옵니다.
    std::filesystem::path currentPath = std::filesystem::current_path();

    // 상대 경로를 절대 경로로 변환합니다.
    std::filesystem::path fontPath = currentPath / folderPath;

    return fontPath;
}