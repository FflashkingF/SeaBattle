#include "visitor.hpp"

void VistorCounter::VisitCell(int, int) { ++cnt; }

void VisitorCollect::VisitCell(int row, int col) {
  CellsWithShips.push_back({row, col});
}
