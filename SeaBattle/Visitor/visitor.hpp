#pragma once

#include <vector>

struct Visitor {
  virtual void VisitCell(int row, int col) = 0;
  virtual ~Visitor() = default;
};

struct VistorCounter : Visitor {
  int cnt = 0;

  void VisitCell(int, int) override;
};

struct VisitorCollect : Visitor {
  std::vector<std::pair<int, int>> CellsWithShips;

  void VisitCell(int row, int col) override;
};

