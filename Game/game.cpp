#include "game.hpp"

#include "../FieldGenerator/generator.hpp"

std::shared_ptr<Board> Game::Ident(Player &player, std::string who) {
    std::string nick = GetPlayerInput(who + " write your nickname:\n");
    player.SetName(nick);
    std::string ask = GetPlayerInput(
            "Write g... to generate board\nor write something other to write board yourself\n");
    ClearCin();
    while (ask[0] == 'g') {
        std::array<std::array<char, Board::SIZE_OF_BOARD>, Board::SIZE_OF_BOARD>
                field = FieldGenerator::generate();
        for (int row = 0; row < Board::SIZE_OF_BOARD; ++row) {
            for (int col = 0; col < Board::SIZE_OF_BOARD; ++col) {
                std::cout << field[row][col];
            }
            std::cout << std::endl;
        }
        Print("Do you like this board?\n");
        ask = GetPlayerInput("Write g... to regenerate this board or w... to write board yourself\nor write something other to accept\n");
        ClearCin();
        if(ask[0] == 'w') {
            break;
        } else if(ask[0] == 'g') {
            continue;
        }
        system("clear");
        return std::shared_ptr<Board>(new Board(field));
    }
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
