#pragma once

#include <memory>
#include <random>
#include <vector>

#include "../Board/board.hpp"

std::mt19937 rnd(time(0));

class FieldGenerator {
private:
    static std::array<std::array<char, Board::SIZE_OF_BOARD>,
            Board::SIZE_OF_BOARD>
            field;

    static std::vector<std::pair<int, int>> generate_row(int row, int col,
                                                         int cnt_cells);

    static std::vector<std::pair<int, int>> generate_col(int row, int col,
                                                         int cnt_cells);

    static bool verify(std::vector<std::pair<int, int>> ship);

    static void place_ship(std::vector<std::pair<int, int>> ship);

    static std::vector<std::pair<int, int>> get_ship(
            std::vector<std::pair<int, int>> gorizontal,
            std::vector<std::pair<int, int>> vertical, int cnt);

public:
    static std::array<std::array<char, Board::SIZE_OF_BOARD>,
            Board::SIZE_OF_BOARD>
    generate();
};
