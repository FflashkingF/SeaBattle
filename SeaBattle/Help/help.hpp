#pragma once
#include <array>
#include <iostream>
#include <string>

void Print(std::string output);

std::string GetPlayerInput(std::string prompt);

template <typename T, size_t ROW, size_t COL>
void fill(std::array<std::array<T, COL>, ROW>& arr, const T& value) {
    for (size_t i = 0; i < ROW; ++i) {
        arr[i].fill(value);
    }
}

void ClearCin();