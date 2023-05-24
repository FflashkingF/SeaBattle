#include "game.hpp"
std::shared_ptr<Board> Game::Ident(Player& player, std::string who) {
  std::string nick = GetPlayerInput(who + " write your nickname:\n");
  player.SetName(nick);
  Print("Write your board " + nick + "\n");
  std::shared_ptr<Board> board(new Board());
  board->Input();
  return board;
}

void Game::StartGame() {
  Print("Game start\n");
  std::shared_ptr<Board> b1 = Ident(first_player, "Player1");
  second_player.SetBoard(b1);
  std::shared_ptr<Board> b2 = Ident(second_player, "Player2");
  first_player.SetBoard(b2);
  while (true) {
    first_player.Play();
    if (first_player.IsWin()) {
      Print("\nWinner is player " + first_player.GetName() + "\n");
      break;
    }
    std::swap(first_player, second_player);
  }
}
