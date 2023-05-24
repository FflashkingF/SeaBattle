#pragma once
#include <memory>

#include "../Board/board.hpp"
#include "../Help/help.hpp"
#include "../Player/player.hpp"

class Game {
 private:
  Player first_player, second_player;

  std::shared_ptr<Board> Ident(Player& player, std::string who);

 public:
  Game() = default;

  void StartGame();
};