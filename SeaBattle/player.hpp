#pragma once
#include <memory>
#include <string>

#include "board.hpp"

class Player {
 private:
  std::shared_ptr<Board> board;
  std::string name;

  bool IsInputCorrect(const std::string& move) {
    bool bad = true;
    if (!('a' <= move[0] && move[0] <= 'j')) {
      return false;
    }
    if (move.size() == 2 && '1' <= move[1] && move[1] <= '9') {
      bad = false;
    } else if (move.size() == 3 && move[1] == '1' && move[2] == '0') {
      bad = false;
    }
    if (bad) {
      return false;
    }
    int row = move[0] - 'a';
    int col = std::stoi(move.substr(1, move.size() - 1)) - 1;
    if(board->IsCanAttacked(row, col)) {
      return true;
    }
    else {
      return false;
    }
  }

 public:
  Player() : board(nullptr) {}

  void SetName(std::string name) { this->name = name; }

  void SetBoard(std::shared_ptr<Board> b) { board = b; }

  bool IsWin() { return board->IsItWin(); }

  std::string GetName() { return name; }

  void Play() {
    Print("\nPlayer " + name + "\n");
    board->ClosePrint();
    while (true) {
      std::string move;
      while (true) {
        move = GetPlayerInput("Make a move player " + name +
                              " (for example a1, b2, c4,...)\n");
        if (IsInputCorrect(move)) {
          break;
        } else {
          Print("INCORRECT INPUT TRY AGAIN\n");
        }
      }

      int row = move[0] - 'a';
      int col = std::stoi(move.substr(1, move.size() - 1)) - 1;
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