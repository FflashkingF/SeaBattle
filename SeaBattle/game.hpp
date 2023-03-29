#pragma once

#include "board.hpp"
#include "player.hpp"
#include "help.hpp"

class Game {
 private:
  Player first_player, second_player;

  Board* Ident(Player& player, std::string who) {
    std::string nick = GetPlayerInput(who + " write your nickname:\n");
    player.SetName(nick);
    Print("Write your board " + nick + "\n");
    Board* board = new Board();
    board->Input();
    return board;
  }

 public:
 
  Game() {}

  void StartGame() {
    Print("Game start\n");
    Board* b1 = Ident(first_player, "Player1");
    second_player.SetBoard(b1);
    Board* b2 = Ident(second_player, "Player2");
    first_player.SetBoard(b2);
    while(1) {
      first_player.Play();
      if(first_player.IsWin()) {
        Print("\nWinner is player " + first_player.GetName() + "\n");
        break;
      }
      std::swap(first_player, second_player);
    }
  }
};