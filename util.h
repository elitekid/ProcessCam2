#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <vector>

class Utils {
public:
    // �� �ڵ带 BGR ������ ��ȯ�ϴ� �Լ�
    static void hexToNormalizedFloat(const std::string& hexCode, float& red, float& green, float& blue);

    // ����� ��� �Լ�
    static std::vector<int> findCommonDivisors(int num1, int num2);

    // ��ǥ ����ȭ : ������ ������ǥ -> -1.0f ~ 1.0f ������ ����ȭ
    static void calcNDS(int w, int h, float x, float y, float squareSize, std::vector<float>& vertices);

    // �ٸ� ��ƿ��Ƽ �Լ����� �߰��� �� �ֽ��ϴ�.
};

#endif // UTIL_H
