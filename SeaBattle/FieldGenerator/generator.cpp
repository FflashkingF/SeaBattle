#include "generator.hpp"

std::array<std::array<char, Board::SIZE_OF_BOARD>,
        Board::SIZE_OF_BOARD>
        FieldGenerator::field;

std::vector<std::pair<int, int>> FieldGenerator::generate_row(int row, int col,
                                                              int cnt_cells) {
    std::vector<std::pair<int, int>> ans;
    for (int i = 0; i < cnt_cells; ++i) {
        ans.push_back({row, col + i});
    }
    return ans;
}

std::vector<std::pair<int, int>> FieldGenerator::generate_col(int row, int col,
                                                              int cnt_cells) {
    std::vector<std::pair<int, int>> ans;
    for (int i = 0; i < cnt_cells; ++i) {
        ans.push_back({row + i, col});
    }
    return ans;
}

bool FieldGenerator::verify(std::vector<std::pair<int, int>> ship) {
    std::vector<int> drow, dcol;
    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            drow.push_back(i);
            dcol.push_back(j);
        }
    }
    for (auto [row, col]: ship) {
        if (!Board::IsExist(row, col)) {
            return false;
        }
        for (int i = 0; i < drow.size(); ++i) {
            int newrow = row + drow[i];
            int newcol = col + dcol[i];
            if (Board::IsExist(newrow, newcol) &&
                field[newrow][newcol] != Cell::Unknown) {
                return false;
            }
        }
    }
    return true;
}

void FieldGenerator::place_ship(std::vector<std::pair<int, int>> ship) {
    for (auto [row, col]: ship) {
        field[row][col] = Cell::Live;
    }
}

std::vector<std::pair<int, int>> FieldGenerator::get_ship(
        std::vector<std::pair<int, int>> gorizontal,
        std::vector<std::pair<int, int>> vertical, int cnt) {
    int number = rnd() % (gorizontal.size() + vertical.size());
    std::vector<std::pair<int, int>> ship;
    if (number < gorizontal.size()) {
        ship = generate_row(gorizontal[number].first, gorizontal[number].second,
                            cnt);
    } else {
        number -= gorizontal.size();
        ship = generate_col(vertical[number].first, vertical[number].second, cnt);
    }
    return ship;
}


std::array<std::array<char, Board::SIZE_OF_BOARD>,
        Board::SIZE_OF_BOARD>
FieldGenerator::generate() {
    fill(field, Cell::Unknown);
    std::vector<int> ships = {4, 3, 3, 2, 2, 2, 1, 1, 1, 1};
    for (int now_ship = 0; now_ship < ships.size(); ++now_ship) {
        int cnt = ships[now_ship];
        std::vector<std::pair<int, int>> gorizontal, vertical;
        for (int i = 0; i < Board::SIZE_OF_BOARD; ++i) {
            for (int j = 0; j < Board::SIZE_OF_BOARD; ++j) {
                auto row_of_cells = generate_row(i, j, cnt);
                if (verify(row_of_cells)) {
                    gorizontal.push_back({i, j});
                }
                auto col_of_cells = generate_col(i, j, cnt);
                if (verify(col_of_cells)) {
                    vertical.push_back({i, j});
                }
            }
        }
        if (gorizontal.empty() && vertical.empty()) {
            return generate();
        }
        auto ship = get_ship(gorizontal, vertical, cnt);
        place_ship(ship);
    }
    return field;
}

