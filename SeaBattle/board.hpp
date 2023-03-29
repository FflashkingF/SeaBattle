#pragma once

#include <stdlib.h>

#include <array>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "help.hpp"

namespace Cell {
const char Unknown = '#', Live = 'L';
const char Wounded = 'W', Kill = 'K', Empty = '.';
}  // namespace Cell

class Board {
 private:
  std::array<std::array<char, 10>, 10>
      board;  // (Unknown or Live) or (Wounded or Kill or Epty)
  int dies = 0;

  bool IsEmpty(int row, int col) {
    return board[row][col] == Cell::Unknown || board[row][col] == Cell::Empty;
  }

  bool IsExist(int row, int col) {
    return 0 <= row && row < 10 && 0 <= col && col < 10;
  }

  int Dfs(std::array<std::array<bool, 10>, 10>& used, int row, int col,
          const std::array<int, 4>& drow, const std::array<int, 4>& dcol) {
    int cnt = 1;
    used[row][col] = 1;
    for (int i = 0; i < 4; ++i) {
      int newrow = row + drow[i];
      int newcol = col + dcol[i];
      if (IsExist(newrow, newcol) && !IsEmpty(newrow, newcol) &&
          !used[newrow][newcol]) {
        cnt += Dfs(used, newrow, newcol, drow, dcol);
      }
    }
    return cnt;
  }

  void DfsForKill(std::array<std::array<bool, 10>, 10>& used, int row, int col,
                  const std::array<int, 4>& drow,
                  const std::array<int, 4>& dcol,
                  std::vector<std::pair<int, int>>& CellsWithShips) {
    used[row][col] = true;
    CellsWithShips.push_back({row, col});
    for (int i = 0; i < 4; ++i) {
      int newrow = row + drow[i];
      int newcol = col + dcol[i];
      if (IsExist(newrow, newcol) && !IsEmpty(newrow, newcol) &&
          !used[newrow][newcol]) {
        DfsForKill(used, newrow, newcol, drow, dcol, CellsWithShips);
      }
    }
  }

  bool CheckKill(int row, int col) {
    std::array<int, 4> drow = {1, -1, 0, 0};
    std::array<int, 4> dcol = {0, 0, 1, -1};
    std::vector<std::pair<int, int>> CellsWithShips;
    std::array<std::array<bool, 10>, 10> used;
    for (int i = 0; i < 10; ++i) used[i].fill(false);
    DfsForKill(used, row, col, drow, dcol, CellsWithShips);
    for (auto i : CellsWithShips) {
      int row = i.first;
      int col = i.second;
      if (board[row][col] == Cell::Live) {
        return false;
      }
    }
    for (auto i : CellsWithShips) {
      int row = i.first;
      int col = i.second;
      board[row][col] = Cell::Kill;
    }
    return true;
  }

  bool Verify() {
    std::array<int, 4> drow = {1, 1, -1, -1};
    std::array<int, 4> dcol = {1, -1, 1, -1};
    for (int row = 0; row < 10; ++row) {
      for (int col = 0; col < 10; ++col) {
        if (!IsEmpty(row, col)) {
          for (int i = 0; i < 4; ++i) {
            int newrow = row + drow[i];
            int newcol = col + dcol[i];
            if (IsExist(newrow, newcol) && !IsEmpty(newrow, newcol)) {
              return false;
            }
          }
        }
      }
    }
    drow = {1, -1, 0, 0};
    dcol = {0, 0, 1, -1};
    std::array<std::array<bool, 10>, 10> used;
    for (int i = 0; i < 10; ++i) used[i].fill(false);
    const std::map<int, int> right = {{4, 1}, {3, 2}, {2, 3}, {1, 4}};
    std::map<int, int> now;
    for (int row = 0; row < 10; ++row) {
      for (int col = 0; col < 10; ++col) {
        if (!IsEmpty(row, col) && !used[row][col]) {
          ++now[Dfs(used, row, col, drow, dcol)];
        }
      }
    }
    if (now != right) {
      return false;
    }
    return true;
  }

 public:
  Board() {
    for (int i = 0; i < 10; ++i) {
      board[i].fill(Cell::Unknown);
    }
  }

  void ClosePrint() {
    std::cout << "  ";
    for (int i = 1; i <= 10; ++i) {
      std::cout << i << ' ';
    }
    std::cout << std::endl;
    for (int i = 0; i < 10; ++i) {
      std::cout << char('a' + i) << ' ';
      for (int j = 0; j < 10; ++j) {
        if (board[i][j] == Cell::Live)
          std::cout << Cell::Unknown;
        else
          std::cout << board[i][j];
        std::cout << ' ';
      }
      std::cout << std::endl;
    }
  }

  bool IsItWin() { return dies == 10; }

  bool Try(int row, int col) {
    if (board[row][col] == Cell::Live) {
      board[row][col] = Cell::Wounded;
      if (CheckKill(row, col)) {
        ++dies;
        Print("\nKILL\n");
      } else {
        Print("\nWounded\n");
      }
      return true;
    } else if (board[row][col] == Cell::Unknown) {
      board[row][col] = Cell::Empty;
      Print("\nMiss\n");
      return false;
    } else {
      Print("else\nEXEPT\nALARMA\nGG\n");
      throw "aboba";  /////////////////////////////////
    }
  }

  void Input() {
    while (1) {
      for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
          std::cin >> board[i][j];
        }
      }
      if (Verify()) {
        system("clear");
        break;
      } else {
        Print("BadInput\n");
        Print("TryAgain\n");
      }
    }
  }
};