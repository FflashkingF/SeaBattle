#pragma once
#include <memory>
#include <string>

#include "../Board/board.hpp"

class Player {
 private:
  std::shared_ptr<Board> board;
  std::string name;

  bool IsInputCorrect(const std::string& move);

 public:
  Player();

  void SetName(std::string name);

  void SetBoard(std::shared_ptr<Board> b);

  bool IsWin();

  std::string GetName();

  void Play();
};