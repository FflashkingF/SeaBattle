#include "player.hpp"
#include <ctype.h>

int to_row(char ch) { return ch - 'a'; }

bool Player::IsInputCorrect(const std::string& move) {
  bool bad = true;
  if (!('a' <= move[0] && move[0] <= 'j')) {
    return false;
  }
  if (move.size() == 2 && std::isdigit(move[1])) {
    bad = false;
  } else if (move.size() == 3 && move[1] == '1' && move[2] == '0') {
    bad = false;
  }
  if (bad) {
    return false;
  }
  int row = to_row(move[0]);
  int col = std::stoi(move.substr(1, move.size() - 1)) - 1;
  if (board->IsCanAttacked(row, col)) {
    return true;
  } else {
    return false;
  }
}

Player::Player() : board(nullptr) {}

void Player::SetName(std::string name) { this->name = name; }

void Player::SetBoard(std::shared_ptr<Board> b) { board = b; }

bool Player::IsWin() { return board->IsItWin(); }

std::string Player::GetName() { return name; }

void Player::Play() {
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

    int row = to_row(move[0]);
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
