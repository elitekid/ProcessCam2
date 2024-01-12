#include "util.h"

void Utils::hexToNormalizedFloat(const std::string & hexCode, float& red, float& green, float& blue) {
    // HEX ���ڿ��� 2�ڸ��� ��� 16������ ��ȯ
    std::string redHex = hexCode.substr(0, 2);
    std::string greenHex = hexCode.substr(2, 2);
    std::string blueHex = hexCode.substr(4, 2);

    // 16������ ������ ��ȯ�Ͽ� 0~255 ������ ����
    int redInt = std::stoi(redHex, nullptr, 16);
    int greenInt = std::stoi(greenHex, nullptr, 16);
    int blueInt = std::stoi(blueHex, nullptr, 16);

    // ����ȭ�Ͽ� 0.0 ~ 1.0 ������ ����
    red = static_cast<float>(redInt) / 255.0f;
    green = static_cast<float>(greenInt) / 255.0f;
    blue = static_cast<float>(blueInt) / 255.0f;
}

std::vector<int> Utils::findCommonDivisors(int num1, int num2) {
    std::vector<int> commonDivisors;

    // �� ���� �� ���� ���ڱ����� �ݺ��Ͽ� ������� ã���ϴ�.
    int smallerNum = (num1 < num2) ? num1 : num2;
    for (int i = 1; i <= smallerNum; ++i) {
        if (num1 % i == 0 && num2 % i == 0) {
            commonDivisors.push_back(i);
        }
    }

    return commonDivisors;
}

void Utils::calcNDS(int w, int h, float x, float y, float squareSize, std::vector<float>& vertices) {
    // ���簢���� �߽� ��ǥ (20, 20)�� NDC�� ����
    float ndcX = (x / w) * 2.0f - 1.0f;
    float ndcY = 1.0f - (y / h) * 2.0f;

    // ���簢���� ũ�⸦ NDC�� ����
    float ndcSizeX = (squareSize / w) * 2.0f;
    float ndcSizeY = (squareSize / h) * 2.0f;

    // ���簢���� ������ ��ǥ ���
    float topLeftX = ndcX - (ndcSizeX / 2.0f);
    float topLeftY = ndcY + (ndcSizeY / 2.0f);

    float bottomRightX = ndcX + (ndcSizeX / 2.0f);
    float bottomRightY = ndcY - (ndcSizeY / 2.0f);

    // ��ǥ�� �ֱ�
    vertices.insert(vertices.end(), {
        topLeftX, topLeftY, 0.0f,  // ���� ���
        bottomRightX, topLeftY, 0.0f,  // ������ ���
        bottomRightX, bottomRightY, 0.0f,   // ������ �ϴ�

        topLeftX, topLeftY, 0.0f,   // ���� ���
        bottomRightX, bottomRightY, 0.0f,   // ������ �ϴ�
        topLeftX, bottomRightY, 0.0f   // ���� �ϴ�
     });
}