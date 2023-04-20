#pragma once
#include <string>
#include "board.hpp"

class Player {
 private:
  Board* board;
  std::string name;

 public:

  Player() : board(nullptr) {}

  void SetName(std::string name) { this->name = name; }

  void SetBoard(Board* b) { board = b; }

  bool IsWin() { return board->IsItWin(); }

  std::string GetName() { return name; }

  void Play() {
    Print("\nPlayer " + name + "\n");
    board->ClosePrint();
    while (1) {
      std::string move = GetPlayerInput("Make a move player " + name +
                                        " (for example a1, b2, c4,...)\n");
      int row = move[0] - 'a';
      move = move.substr(1, move.size() - 1);
      int col = std::stoi(move) - 1;
      bool needbreak = !board->Try(row, col);
      board->ClosePrint();
      if (IsWin()) {
        return;
      }
      if (needbreak) {
        Print("\n\nSwap Turn\n\n");
        return;
      } else {
        Print("\nPlay Again player " + name + "\n");
      }
    }
  }
};