#pragma once

#include <vector>
#include "../Board/board.hpp"
#include "../Board/dfs.hpp"

namespace KillChecker {
    void KillShip(Board &board, const std::vector<std::pair<int, int>> &CellsWithShip) {
        for (auto i: CellsWithShip) {
            int row = i.first;
            int col = i.second;
            board.KillCell(row, col);
        }
    }

    bool IsShipDie(Board &board, const std::vector<std::pair<int, int>> &CellsWithShip) {
        for (auto i: CellsWithShip) {
            int row = i.first;
            int col = i.second;
            if (board.IsAlive(row, col)) {
                return false;
            }
        }
        return true;
    }

    bool CheckKill(Board &board, int row, int col) {
        std::array<int, 4> drow = {1, -1, 0, 0};
        std::array<int, 4> dcol = {0, 0, 1, -1};
        std::array<std::array<bool, Board::SIZE_OF_BOARD>, Board::SIZE_OF_BOARD> used;
        fill(used, false);
        VisitorCollect vis;
        DFS::Dfs(board, used, row, col, drow, dcol, vis);
        if (!IsShipDie(board, vis.CellsWithShips)) return false;
        KillShip(board, vis.CellsWithShips);
        return true;
    }
}