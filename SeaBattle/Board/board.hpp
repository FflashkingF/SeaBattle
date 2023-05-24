#pragma once

#include <stdlib.h>

#include <array>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include "../Visitor/visitor.hpp"
#include "../Help/help.hpp"

namespace Cell {
const char Unknown = '#', Live = 'L';
const char Wounded = 'W', Kill = 'K', Empty = '.';
}  // namespace Cell

class Board {
 public:
  static const int SIZE_OF_BOARD = 10;
  static bool IsExist(int row, int col);
  bool IsEmpty(int row, int col);
 private:
  std::array<std::array<char, SIZE_OF_BOARD>, SIZE_OF_BOARD>
      board;  // (Unknown or Live) or (Wounded or Kill or Epty)
  int dies = 0;

  void KillShip(const std::vector<std::pair<int, int>>& CellsWithShip);

  bool IsShipDie(const std::vector<std::pair<int, int>>& CellsWithShip);

  bool CheckKill(int row, int col);

  bool IsNoContactsBetweenShips();

  bool IsCorrectShips();

  bool Verify();

 public:
  Board();

  bool IsCanAttacked(int row, int col);

  void ClosePrint();

  bool IsItWin();

  bool Try(int row, int col);

  void Input();
};