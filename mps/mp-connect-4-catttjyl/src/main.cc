#include <iostream>

#include "board.hpp"

int main() {
  Board b;
  InitBoard(b);
  DropDiskToBoard(b, DiskType::kPlayer2, 6);
  DropDiskToBoard(b, DiskType::kPlayer2, 5);
  DropDiskToBoard(b, DiskType::kPlayer2, 4);
  DropDiskToBoard(b, DiskType::kPlayer1, 3);
  DropDiskToBoard(b, DiskType::kPlayer1, 2);
  DropDiskToBoard(b, DiskType::kPlayer1, 1);

  DropDiskToBoard(b, DiskType::kPlayer1, 0);

  DropDiskToBoard(b, DiskType::kPlayer1, 1);
  DropDiskToBoard(b, DiskType::kPlayer2, 2);
  DropDiskToBoard(b, DiskType::kPlayer1, 2);
  DropDiskToBoard(b, DiskType::kPlayer2, 3);
  DropDiskToBoard(b, DiskType::kPlayer2, 3);
  DropDiskToBoard(b, DiskType::kPlayer1, 3);

  DropDiskToBoard(b, DiskType::kPlayer2, 4);
  DropDiskToBoard(b, DiskType::kPlayer2, 5);

  std::cout << "cheack for player1" << std::endl;
  if (CheckForWinner(b, DiskType::kPlayer1)) {
    std::cout << "player1 wins" << std::endl;
  } else {
    std::cout << "player1 loses" << std::endl;
  }
  std::cout << "cheack for player2" << std::endl;
  if (CheckForWinner(b, DiskType::kPlayer2)) {
    std::cout << "player2 wins" << std::endl;
  } else {
    std::cout << "player2 loses" << std::endl;
  }
  // if (!CheckForWinner(b, DiskType::kEmpty)) {
  //   std::cout << "invalid check" << std::endl;
  // }
  BoardToStr(b);
}