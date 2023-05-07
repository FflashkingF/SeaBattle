#include "board.hpp"
#include "../DFS/dfs.hpp"
#include "../KillChecker/killchecker.hpp"

bool Board::IsExist(int row, int col) {
  return 0 <= row && row < SIZE_OF_BOARD && 0 <= col && col < SIZE_OF_BOARD;
}
bool Board::IsEmpty(int row, int col) {
  return board[row][col] == Cell::Unknown || board[row][col] == Cell::Empty;
}
bool Board::IsAlive(int row, int col) {
    return board[row][col] == Cell::Live;
}
void Board::KillCell(int row, int col) {
    board[row][col] = Cell::Kill;
}

bool Board::IsNoContactsBetweenShips() {
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

bool Board::IsCorrectShips() {
  std::array<int, 4> drow = {1, -1, 0, 0};
  std::array<int, 4> dcol = {0, 0, 1, -1};
  std::array<std::array<bool, SIZE_OF_BOARD>, SIZE_OF_BOARD> used;
  fill(used, false);
  const std::map<int, int> right = {{4, 1}, {3, 2}, {2, 3}, {1, 4}};
  std::map<int, int> now;
  for (int row = 0; row < SIZE_OF_BOARD; ++row) {
    for (int col = 0; col < SIZE_OF_BOARD; ++col) {
      if (!IsEmpty(row, col) && !used[row][col]) {
        VistorCounter vis;
        DFS::Dfs(*this, used, row, col, drow, dcol, vis);
        ++now[vis.cnt];
      }
    }
  }
  return now == right;
}

bool Board::Verify() {
  if (!IsNoContactsBetweenShips()) {
    return false;
  }
  if (!IsCorrectShips()) {
    return false;
  }
  return true;
}

Board::Board() { fill(board, Cell::Unknown); }

bool Board::IsCanAttacked(int row, int col) {
  return board[row][col] == Cell::Unknown || board[row][col] == Cell::Live;
}

void Board::ClosePrint() {
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

bool Board::IsItWin() { return dies == SIZE_OF_BOARD; }

bool Board::Try(int row, int col) {
  if (board[row][col] == Cell::Live) {
    board[row][col] = Cell::Wounded;
    if (KillChecker::CheckKill(*this, row, col)) {
      ++dies;
      Print("\nKILL\n");
    } else {
      Print("\nWounded\n");
    }
    return true;
  }
  // board[row][col] == Cell::Unknown
  board[row][col] = Cell::Empty;
  Print("\nMiss\n");
  return false;
}

void Board::Input() {
  while (true) {
    for (int i = 0; i < SIZE_OF_BOARD; ++i) {
      for (int j = 0; j < SIZE_OF_BOARD; ++j) {
        std::cin >> board[i][j];
        if (board[i][j] != '#' && board[i][j] != 'L') {
          goto stop;
        }
      }
    }
    if (Verify()) {
      system("clear");
      break;
    } else {
    stop:
      std::cin.clear();
      fflush(stdin);
      Print("BadInput\n");
      Print("TryAgain\n");
    }
  }
}
