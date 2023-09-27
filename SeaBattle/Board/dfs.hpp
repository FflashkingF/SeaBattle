#pragma once
#include <array>
#include "../Visitor/visitor.hpp"
#include "../Board/board.hpp"

namespace DFS {
    template <size_t SIZE_OF_BOARD, size_t CNT_DIRECTIONS>
    void Dfs(Board& board,
                  std::array<std::array<bool, SIZE_OF_BOARD>, SIZE_OF_BOARD>& used,
                  int row, int col, const std::array<int, CNT_DIRECTIONS>& drow,
                  const std::array<int, CNT_DIRECTIONS>& dcol, Visitor& vis) {
        vis.VisitCell(row, col);
        used[row][col] = true;
        for (int i = 0; i < 4; ++i) {
            int newrow = row + drow[i];
            int newcol = col + dcol[i];
            if (board.IsExist(newrow, newcol) && !board.IsEmpty(newrow, newcol) &&
                !used[newrow][newcol]) {
                Dfs(board, used, newrow, newcol, drow, dcol, vis);
            }
        }
    }
}