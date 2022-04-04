#include "board.hpp"

// you might need additional includes
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

/**************************************************************************/
/* your function definitions                                              */
/**************************************************************************/

void InitBoard(Board& b) {
  for (int i = 0; i < Board::kBoardHeight; i++) {
    for (int j = 0; j < Board::kBoardWidth; j++) {
      b.board[i][j] = DiskType::kEmpty;
    }
  }
}

void DropDiskToBoard(Board& b, DiskType disk, int col) {
  if (col >= Board::kBoardWidth || col < 0) {
    throw std::runtime_error("invald column");
  }
  for (int i = 0; i < Board::kBoardHeight; i++) {
    if (b.board[i][col] == DiskType::kEmpty) {
      b.board[i][col] = disk;
      break;
    }
    if (i == Board::kBoardHeight - 1) {
      throw std::runtime_error("invald column");
    }
  }
}

bool CheckForWinner(Board& b, DiskType disk) {
  if (disk == DiskType::kEmpty) {
    return false;
  }
  bool to_return = false;
  if (SearchForWinner(b, disk, WinningDirection::kHorizontal) ||
      SearchForWinner(b, disk, WinningDirection::kVertical) ||
      SearchForWinner(b, disk, WinningDirection::kRightDiag) ||
      SearchForWinner(b, disk, WinningDirection::kLeftDiag)) {
    to_return = true;
  }
  return to_return;
}

bool SearchForWinner(Board& b, DiskType disk, WinningDirection to_check) {
  bool to_return = false;
  int check = 0;
  if (to_check == WinningDirection::kHorizontal) {
    for (int i = 0; i < Board::kBoardHeight; i++) {
      check = 0;
      for (int j = 0; j < Board::kBoardWidth - 1; j++) {
        if (b.board[i][j] == disk && b.board[i][j + 1] == disk) {
          check++;
          if (check >= 3) to_return = true;
        } else {
          check = 0;
        }
      }
    }
  }
  if (to_check == WinningDirection::kVertical) {
    for (int j = 0; j < Board::kBoardWidth; j++) {
      check = 0;
      for (int i = 0; i < Board::kBoardHeight - 1; i++) {
        if (b.board[i][j] == disk && b.board[i + 1][j] == disk) {
          check++;
          if (check >= 3) to_return = true;
        } else {
          check = 0;
        }
      }
    }
  }
  if (to_check == WinningDirection::kLeftDiag)
    to_return = CheckForLeftDiag(b, disk);
  if (to_check == WinningDirection::kRightDiag)
    to_return = CheckForRightDiag(b, disk);
  if (check >= 3) to_return = true;
  return to_return;
}

bool CheckForRightDiag(Board& b, DiskType disk) {
  bool to_return = false;
  for (int i = 0; i < Board::kBoardHeight - 3; i++) {
    for (int j = 0; j < Board::kBoardWidth - 3; j++) {
      if (b.board[i][j] == disk && b.board[i + 1][j + 1] == disk &&
          b.board[i + 2][j + 2] == disk && b.board[i + 3][j + 3] == disk) {
        to_return = true;
      }
    }
  }
  return to_return;
}

bool CheckForLeftDiag(Board& b, DiskType disk) {
  bool to_return = false;
  for (int i = 0; i < Board::kBoardHeight - 3; i++) {
    for (int j = 3; j < Board::kBoardWidth; j++) {
      if (b.board[i][j] == disk && b.board[i + 1][j - 1] == disk &&
          b.board[i + 2][j - 2] == disk && b.board[i + 3][j - 3] == disk) {
        to_return = true;
      }
    }
  }
  return to_return;
}

bool BoardLocationInBounds(int row, int col) {
  bool to_return = false;
  if (row < Board::kBoardHeight && row >= 0 && col < Board::kBoardWidth &&
      col >= 0) {
    to_return = true;
  }
  return to_return;
}

/**************************************************************************/
/* provided to you                                                        */
/**************************************************************************/
std::string BoardToStr(const Board& b) {
  constexpr int kTotalWidth = Board::kBoardWidth * 11 - Board::kBoardHeight - 1;
  std::stringstream ss;
  ss << std::endl;
  for (int row = Board::kBoardHeight; row > 0; --row) {
    ss << " |";
    for (int col = 0; col < Board::kBoardWidth; ++col) {
      std::string value_here;
      value_here.push_back(static_cast<char>(b.board[row - 1][col]));
      ss << ' ' << CenterStr(value_here, Board::kBoardWidth + 1) << '|';
    }
    ss << std::endl;
    ss << " |" << std::setw(kTotalWidth) << std::setfill('-') << '|'
       << std::endl;
  }
  ss << " |";
  for (int col = 0; col < Board::kBoardWidth; ++col) {
    ss << ' ' << CenterStr(std::to_string(col), Board::kBoardWidth + 1) << '|';
  }
  std::cout << ss.str() << std::endl;
  return ss.str();
}

std::string CenterStr(const std::string& str, int col_width) {
  // quick and easy (but error-prone) implementation
  auto padl = (col_width - str.length()) / 2;
  auto padr = (col_width - str.length()) - padl;
  std::string strf = std::string(padl, ' ') + str + std::string(padr, ' ');
  return strf;
}