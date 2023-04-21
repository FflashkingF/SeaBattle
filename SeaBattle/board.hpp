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
  static const int SIZE_OF_BOARD = 10;
  std::array<std::array<char, SIZE_OF_BOARD>, SIZE_OF_BOARD>
      board;  // (Unknown or Live) or (Wounded or Kill or Epty)
  int dies = 0;

  bool IsEmpty(int row, int col) {
    return board[row][col] == Cell::Unknown || board[row][col] == Cell::Empty;
  }

  bool IsExist(int row, int col) {
    return 0 <= row && row < SIZE_OF_BOARD && 0 <= col && col < SIZE_OF_BOARD;
  }

  int Dfs(std::array<std::array<bool, SIZE_OF_BOARD>, SIZE_OF_BOARD>& used,
          int row, int col, const std::array<int, 4>& drow,
          const std::array<int, 4>& dcol) {
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

  void DfsForKill(
      std::array<std::array<bool, SIZE_OF_BOARD>, SIZE_OF_BOARD>& used, int row,
      int col, const std::array<int, 4>& drow, const std::array<int, 4>& dcol,
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

  void KillShip(const std::vector<std::pair<int, int>>& CellsWithShip) {
    for (auto i : CellsWithShip) {
      int row = i.first;
      int col = i.second;
      board[row][col] = Cell::Kill;
    }
  }

  bool IsShipDie(const std::vector<std::pair<int, int>>& CellsWithShip) {
    for (auto i : CellsWithShip) {
      int row = i.first;
      int col = i.second;
      if (board[row][col] == Cell::Live) {
        return false;
      }
    }
    return true;
  }

  bool CheckKill(int row, int col) {
    std::array<int, 4> drow = {1, -1, 0, 0};
    std::array<int, 4> dcol = {0, 0, 1, -1};
    std::vector<std::pair<int, int>> CellsWithShip;
    std::array<std::array<bool, SIZE_OF_BOARD>, SIZE_OF_BOARD> used;
    fill(used, false);
    DfsForKill(used, row, col, drow, dcol, CellsWithShip);
    if (!IsShipDie(CellsWithShip)) return false;
    KillShip(CellsWithShip);
    return true;
  }

  bool IsNoContactsBetweenShips() {
    std::array<int, 4> drow = {1, 1, -1, -1};
    std::array<int, 4> dcol = {1, -1, 1, -1};
    for (int row = 0; row < SIZE_OF_BOARD; ++row) {
      for (int col = 0; col < SIZE_OF_BOARD; ++col) {
        if (IsEmpty(row, col)) {
          continue;
        }
        for (int i = 0; i < 4; ++i) {
          int newrow = row + drow[i];
          int newcol = col + dcol[i];
          if (IsExist(newrow, newcol) && !IsEmpty(newrow, newcol)) {
            return false;
          }
        }
      }
    }
    return true;
  }

  bool IsCorrectShips() {
    std::array<int, 4> drow = {1, -1, 0, 0};
    std::array<int, 4> dcol = {0, 0, 1, -1};
    std::array<std::array<bool, SIZE_OF_BOARD>, SIZE_OF_BOARD> used;
    fill(used, false);
    const std::map<int, int> right = {{4, 1}, {3, 2}, {2, 3}, {1, 4}};
    std::map<int, int> now;
    for (int row = 0; row < SIZE_OF_BOARD; ++row) {
      for (int col = 0; col < SIZE_OF_BOARD; ++col) {
        if (!IsEmpty(row, col) && !used[row][col]) {
          ++now[Dfs(used, row, col, drow, dcol)];
        }
      }
    }
    return now == right;
  }

  bool Verify() {
    if (!IsNoContactsBetweenShips()) {
      return false;
    }
    if (!IsCorrectShips()) {
      return false;
    }
    return true;
  }

 public:
  Board() { fill(board, Cell::Unknown); }

  bool IsCanAttacked(int row, int col) {
    return board[row][col] == Cell::Unknown || board[row][col] == Cell::Live;
  }

  void ClosePrint() {
    std::cout << "  ";
    for (int i = 1; i <= SIZE_OF_BOARD; ++i) {
      std::cout << i << ' ';
    }
    std::cout << std::endl;
    for (int i = 0; i < SIZE_OF_BOARD; ++i) {
      std::cout << char('a' + i) << ' ';
      for (int j = 0; j < SIZE_OF_BOARD; ++j) {
        if (board[i][j] == Cell::Live)
          std::cout << Cell::Unknown;
        else
          std::cout << board[i][j];
        std::cout << ' ';
      }
      std::cout << std::endl;
    }
  }

  bool IsItWin() { return dies == SIZE_OF_BOARD; }

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
    while (true) {
      for (int i = 0; i < SIZE_OF_BOARD; ++i) {
        for (int j = 0; j < SIZE_OF_BOARD; ++j) {
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