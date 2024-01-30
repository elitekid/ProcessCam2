#ifndef UTIL_H
#define UTIL_H

#include <iostream>
#include <filesystem>
#include <string>
#include <vector>
#include <windows.h>

class Utils {
public:
    // 헥스 코드를 BGR 값으로 변환하는 함수
    static void hexToNormalizedFloat(const std::string& hex_code, float& red, float& green, float& blue);

    // 공약수 계산 함수
    static std::vector<int> findCommonDivisors(int num1, int num2);

    // 좌표 정규화 : 추출한 절대좌표 -> -1.0f ~ 1.0f 범위로 정규화
    static void calcNDS(int w, int h, float x, float y, float square_size, std::vector<float>& vertices);

    // 폰트 목록 반환
    static std::filesystem::path GetFontPath();

    // 다른 유틸리티 함수들을 추가할 수 있습니다.
};

#endif // UTIL_H
