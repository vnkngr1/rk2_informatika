#ifndef TASK1_H
#define TASK1_H

#include <iostream>
#include <string>
#include <algorithm>

// Функция для побитовой операции AND
std::string bitwiseAND(const std::string &a, const std::string &b) {
    std::string result = "";
    for (int i = 0; i < a.size(); ++i) {
        if (a[i] == '1' && b[i] == '1') {
            result += '1';
        } else {
            result += '0';
        }
    }
    return result;
}

// Функция для сложения двоичных чисел
std::string binaryAddition(const std::string &a, const std::string &b) {
    std::string result = "";
    int carry = 0; // перенос
    int i = a.size() - 1, j = b.size() - 1;

    while (i >= 0 || j >= 0 || carry > 0) {
        int bitA = (i >= 0) ? a[i] - '0' : 0;
        int bitB = (j >= 0) ? b[j] - '0' : 0;

        int sum = bitA + bitB + carry;
        result += (sum % 2) + '0'; // записываем текущий бит результата
        carry = sum / 2;          // вычисляем перенос

        --i;
        --j;
    }

    std::reverse(result.begin(), result.end()); // переворачиваем строку результата
    return result;
}

int task1() {
    // Двоичные числа
    std::string A = "101101";
    std::string B = "110011";

    // Уравниваем длины строк (добавляем ведущие нули)
    while (A.size() < B.size()) A = "0" + A;
    while (B.size() < A.size()) B = "0" + B;

    // 1. Побитовая операция AND
    std::string andResult = bitwiseAND(A, B);
    std::cout << "Результат операции AND: " << andResult << std::endl;

    // 2. Сложение чисел
    std::string sumResult = binaryAddition(A, B);
    std::cout << "Результат сложения: " << sumResult << std::endl;

    return 0;
}

#endif //TASK1_H
