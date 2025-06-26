#include <iostream>
#include <random>

int main() {
    std::random_device rd;                          // Источник случайности
    std::mt19937 gen(rd());                         // Генератор псевдослучайных чисел
    std::uniform_real_distribution<float> dist(0.0f, 1.0f); // Диапазон от 0.0 до 1.0 (не включая 1.0)

    for (int i = 0; i < 5; ++i) {
        float randomValue = dist(gen);
        std::cout << randomValue << std::endl;
    }

    return 0;
}