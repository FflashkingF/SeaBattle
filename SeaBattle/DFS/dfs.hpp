#pragma once
#include <array>
#include "../Visitor/visitor.hpp"
#include "../Board/board.hpp"

class Board;

namespace DFS {
    template <unsigned long SIZE_OF_BOARD>
    void Dfs(Board& board,
                  std::array<std::array<bool, SIZE_OF_BOARD>, SIZE_OF_BOARD>& used,
                  int row, int col, const std::array<int, 4>& drow,
                  const std::array<int, 4>& dcol, Visitor& vis) {
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