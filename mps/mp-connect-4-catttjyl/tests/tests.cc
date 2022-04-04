// clang-format off
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
//  Written By : Michael R. Nowak                Environment : ubuntu:latest               //
//  Date ......: 2022/02/07                      Compiler ...: clang-10                    //
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
// clang-format on
/////////////////////////////////////////////////////////////////////////////////////////////
//                             Framework Set-up //
/////////////////////////////////////////////////////////////////////////////////////////////
#ifndef CATCH_CONFIG_MAIN
#  define CATCH_CONFIG_MAIN
#endif

#include "catch.hpp"

/////////////////////////////////////////////////////////////////////////////////////////////
//                                 Includes //
/////////////////////////////////////////////////////////////////////////////////////////////
#include <stdexcept>

#include "board.hpp"

/////////////////////////////////////////////////////////////////////////////////////////////
//                             Helpers/Constants //
/////////////////////////////////////////////////////////////////////////////////////////////
constexpr int kBoardWidth = 7;
constexpr int kBoardHeight = 6;

bool AreEqual(DiskType solution[][kBoardWidth],
              DiskType student[][kBoardWidth]) {
  for (int i = 0; i < kBoardHeight; ++i) {
    for (int j = 0; j < kBoardWidth; ++j) {
      if (solution[i][j] != student[i][j]) return false;
    }
  }
  return true;
}

/////////////////////////////////////////////////////////////////////////////////////////////
//                                Test Cases //
/////////////////////////////////////////////////////////////////////////////////////////////

TEST_CASE("Board initialization", "[board_init]") {
  // SECTION("Can use sections") {}
  // clang-format off
  DiskType solution[kBoardHeight][kBoardWidth] = { 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty} 
  };
  // clang-format on
  Board student;  // NOLINT
  InitBoard(student);
  REQUIRE(AreEqual(solution, student.board));
}

TEST_CASE("BASIC CHECK", "[basic]") {
  Board b;
  InitBoard(b);
  DropDiskToBoard(b, DiskType::kPlayer1, 6);
  SECTION("DROP_DISK_SUCCESSFULLY") {
    REQUIRE(b.board[0][6] == DiskType::kPlayer1);
    // for (int i = 0; i < kBoardHeight; i++) {
    //   for (int j = 0; j < kBoardWidth; j++) {
    //     if (i != 0 && j != 6) {
    //       REQUIRE(CheckForWinner(b, DiskType::kEmpty));
    //     }
    //   }
    // }
  }
  DropDiskToBoard(b, DiskType::kPlayer2, 0);
  DropDiskToBoard(b, DiskType::kPlayer2, 5);
  DropDiskToBoard(b, DiskType::kPlayer1, 6);
  DropDiskToBoard(b, DiskType::kPlayer2, 5);
  DropDiskToBoard(b, DiskType::kPlayer1, 5);
  DropDiskToBoard(b, DiskType::kPlayer2, 6);
  DropDiskToBoard(b, DiskType::kPlayer1, 6);
  DropDiskToBoard(b, DiskType::kPlayer2, 6);
  DropDiskToBoard(b, DiskType::kPlayer1, 6);
  SECTION("INVALID_COLUMN_INPUT") {
    REQUIRE_THROWS_AS(DropDiskToBoard(b, DiskType::kPlayer1, 7),
                      std::runtime_error);
    REQUIRE_THROWS_AS(DropDiskToBoard(b, DiskType::kPlayer1, 6),
                      std::runtime_error);
    REQUIRE_THROWS_AS(DropDiskToBoard(b, DiskType::kPlayer1, -2),
                      std::runtime_error);
  }
  SECTION("OUT_OF_BOUND") {
    REQUIRE(BoardLocationInBounds(2, 4));
    REQUIRE(BoardLocationInBounds(0, 6));
    REQUIRE_FALSE(BoardLocationInBounds(7, 3));
    REQUIRE_FALSE(BoardLocationInBounds(-2, 3));
    REQUIRE_FALSE(BoardLocationInBounds(1, 7));
    REQUIRE_FALSE(BoardLocationInBounds(3, -1));
  }
}

TEST_CASE("WIN HORIZONTAL", "[horizontal]") {
  Board b;
  InitBoard(b);
  DropDiskToBoard(b, DiskType::kPlayer2, 6);
  DropDiskToBoard(b, DiskType::kPlayer2, 5);
  DropDiskToBoard(b, DiskType::kPlayer2, 4);
  DropDiskToBoard(b, DiskType::kPlayer1, 3);
  DropDiskToBoard(b, DiskType::kPlayer1, 2);
  DropDiskToBoard(b, DiskType::kPlayer1, 1);
  SECTION("zeroth_row") {
    DropDiskToBoard(b, DiskType::kPlayer1, 0);
    REQUIRE(CheckForWinner(b, DiskType::kPlayer1));
    REQUIRE(
        SearchForWinner(b, DiskType::kPlayer1, WinningDirection::kHorizontal));
    REQUIRE_FALSE(CheckForWinner(b, DiskType::kPlayer2));
    DropDiskToBoard(b, DiskType::kPlayer2, 2);
    DropDiskToBoard(b, DiskType::kPlayer2, 5);
    DropDiskToBoard(b, DiskType::kPlayer2, 4);
    DropDiskToBoard(b, DiskType::kPlayer2, 3);
    REQUIRE(CheckForWinner(b, DiskType::kPlayer2));
    REQUIRE(
        SearchForWinner(b, DiskType::kPlayer2, WinningDirection::kHorizontal));
  }
  SECTION("second_row") {
    DropDiskToBoard(b, DiskType::kPlayer1, 6);
    DropDiskToBoard(b, DiskType::kPlayer1, 5);
    DropDiskToBoard(b, DiskType::kPlayer1, 4);
    DropDiskToBoard(b, DiskType::kPlayer1, 3);
    REQUIRE(CheckForWinner(b, DiskType::kPlayer1));
    REQUIRE(
        SearchForWinner(b, DiskType::kPlayer1, WinningDirection::kHorizontal));
  }
  SECTION("chang_row") {
    DropDiskToBoard(b, DiskType::kPlayer1, 0);
    DropDiskToBoard(b, DiskType::kPlayer2, 0);
    REQUIRE(CheckForWinner(b, DiskType::kPlayer1));
    REQUIRE(
        SearchForWinner(b, DiskType::kPlayer1, WinningDirection::kHorizontal));
    REQUIRE_FALSE(CheckForWinner(b, DiskType::kPlayer2));
    DropDiskToBoard(b, DiskType::kPlayer2, 1);
    REQUIRE_FALSE(CheckForWinner(b, DiskType::kPlayer2));
    DropDiskToBoard(b, DiskType::kPlayer2, 2);
    DropDiskToBoard(b, DiskType::kPlayer2, 3);
    REQUIRE(CheckForWinner(b, DiskType::kPlayer2));
    REQUIRE(
        SearchForWinner(b, DiskType::kPlayer2, WinningDirection::kHorizontal));
  }
  SECTION("final_row") {
    DropDiskToBoard(b, DiskType::kPlayer2, 0);
    DropDiskToBoard(b, DiskType::kPlayer2, 6);
    DropDiskToBoard(b, DiskType::kPlayer2, 5);
    DropDiskToBoard(b, DiskType::kPlayer2, 4);
    DropDiskToBoard(b, DiskType::kPlayer1, 3);
    DropDiskToBoard(b, DiskType::kPlayer2, 2);
    DropDiskToBoard(b, DiskType::kPlayer1, 1);
    DropDiskToBoard(b, DiskType::kPlayer2, 2);
    DropDiskToBoard(b, DiskType::kPlayer1, 3);
    DropDiskToBoard(b, DiskType::kPlayer2, 3);
    DropDiskToBoard(b, DiskType::kPlayer1, 5);
    DropDiskToBoard(b, DiskType::kPlayer1, 4);
    DropDiskToBoard(b, DiskType::kPlayer2, 6);
    DropDiskToBoard(b, DiskType::kPlayer1, 6);
    DropDiskToBoard(b, DiskType::kPlayer2, 5);
    DropDiskToBoard(b, DiskType::kPlayer1, 4);
    DropDiskToBoard(b, DiskType::kPlayer2, 5);
    DropDiskToBoard(b, DiskType::kPlayer1, 4);
    DropDiskToBoard(b, DiskType::kPlayer2, 4);
    DropDiskToBoard(b, DiskType::kPlayer1, 3);
    DropDiskToBoard(b, DiskType::kPlayer2, 3);
    DropDiskToBoard(b, DiskType::kPlayer2, 5);
    DropDiskToBoard(b, DiskType::kPlayer1, 6);
    DropDiskToBoard(b, DiskType::kPlayer2, 6);
    REQUIRE(CheckForWinner(b, DiskType::kPlayer2));
    REQUIRE(
        SearchForWinner(b, DiskType::kPlayer2, WinningDirection::kHorizontal));
    REQUIRE_FALSE(CheckForWinner(b, DiskType::kPlayer1));
  }
}

TEST_CASE("WIN VERTICAL", "[vertical]") {
  Board b;
  InitBoard(b);
  SECTION("zeroth_col") {
    DropDiskToBoard(b, DiskType::kPlayer2, 0);
    DropDiskToBoard(b, DiskType::kPlayer1, 0);
    DropDiskToBoard(b, DiskType::kPlayer2, 0);
    DropDiskToBoard(b, DiskType::kPlayer2, 0);
    DropDiskToBoard(b, DiskType::kPlayer2, 0);
    DropDiskToBoard(b, DiskType::kPlayer2, 0);
    REQUIRE(CheckForWinner(b, DiskType::kPlayer2));
    REQUIRE(
        SearchForWinner(b, DiskType::kPlayer2, WinningDirection::kVertical));
    REQUIRE_FALSE(CheckForWinner(b, DiskType::kPlayer1));
  }
  SECTION("change_col") {
    DropDiskToBoard(b, DiskType::kPlayer2, 1);
    DropDiskToBoard(b, DiskType::kPlayer2, 1);
    DropDiskToBoard(b, DiskType::kPlayer2, 1);
    DropDiskToBoard(b, DiskType::kPlayer1, 1);
    DropDiskToBoard(b, DiskType::kPlayer1, 1);
    REQUIRE_FALSE(CheckForWinner(b, DiskType::kPlayer2));
    DropDiskToBoard(b, DiskType::kPlayer1, 1);
    DropDiskToBoard(b, DiskType::kPlayer1, 2);
    REQUIRE_FALSE(CheckForWinner(b, DiskType::kPlayer1));
    DropDiskToBoard(b, DiskType::kPlayer1, 2);
    DropDiskToBoard(b, DiskType::kPlayer1, 2);
    DropDiskToBoard(b, DiskType::kPlayer1, 2);
    REQUIRE(CheckForWinner(b, DiskType::kPlayer1));
    REQUIRE(
        SearchForWinner(b, DiskType::kPlayer1, WinningDirection::kVertical));
  }
  SECTION("final_col") {
    DropDiskToBoard(b, DiskType::kPlayer2, 6);
    DropDiskToBoard(b, DiskType::kPlayer1, 6);
    DropDiskToBoard(b, DiskType::kPlayer2, 6);
    DropDiskToBoard(b, DiskType::kPlayer2, 6);
    DropDiskToBoard(b, DiskType::kPlayer2, 6);
    DropDiskToBoard(b, DiskType::kPlayer2, 6);
    REQUIRE(CheckForWinner(b, DiskType::kPlayer2));
    REQUIRE(
        SearchForWinner(b, DiskType::kPlayer2, WinningDirection::kVertical));
    REQUIRE_FALSE(CheckForWinner(b, DiskType::kPlayer1));
  }
}

TEST_CASE("WIN LEFTDIAG", "[leftdiag]") {
  Board b;
  InitBoard(b);
  SECTION("in_between") {
    DropDiskToBoard(b, DiskType::kPlayer2, 5);
    DropDiskToBoard(b, DiskType::kPlayer2, 4);
    DropDiskToBoard(b, DiskType::kPlayer1, 3);
    DropDiskToBoard(b, DiskType::kPlayer2, 2);
    DropDiskToBoard(b, DiskType::kPlayer1, 1);
    DropDiskToBoard(b, DiskType::kPlayer1, 4);
    DropDiskToBoard(b, DiskType::kPlayer2, 3);
    DropDiskToBoard(b, DiskType::kPlayer1, 2);
    DropDiskToBoard(b, DiskType::kPlayer1, 1);
    DropDiskToBoard(b, DiskType::kPlayer1, 3);
    DropDiskToBoard(b, DiskType::kPlayer2, 1);
    DropDiskToBoard(b, DiskType::kPlayer2, 5);
    DropDiskToBoard(b, DiskType::kPlayer1, 2);
    DropDiskToBoard(b, DiskType::kPlayer1, 2);
    DropDiskToBoard(b, DiskType::kPlayer1, 1);
    DropDiskToBoard(b, DiskType::kPlayer1, 1);
    DropDiskToBoard(b, DiskType::kPlayer2, 6);
    DropDiskToBoard(b, DiskType::kPlayer2, 6);
    DropDiskToBoard(b, DiskType::kPlayer2, 6);
    REQUIRE(CheckForWinner(b, DiskType::kPlayer1));
    REQUIRE(
        SearchForWinner(b, DiskType::kPlayer1, WinningDirection::kLeftDiag));
    REQUIRE_FALSE(CheckForWinner(b, DiskType::kPlayer2));
  }
  SECTION("lower_left") {
    DropDiskToBoard(b, DiskType::kPlayer2, 1);
    DropDiskToBoard(b, DiskType::kPlayer1, 0);
    DropDiskToBoard(b, DiskType::kPlayer2, 2);
    DropDiskToBoard(b, DiskType::kPlayer2, 0);
    DropDiskToBoard(b, DiskType::kPlayer1, 3);
    DropDiskToBoard(b, DiskType::kPlayer1, 2);
    DropDiskToBoard(b, DiskType::kPlayer1, 1);
    DropDiskToBoard(b, DiskType::kPlayer1, 1);
    DropDiskToBoard(b, DiskType::kPlayer1, 0);
    DropDiskToBoard(b, DiskType::kPlayer1, 0);
    REQUIRE(CheckForWinner(b, DiskType::kPlayer1));
    REQUIRE(
        SearchForWinner(b, DiskType::kPlayer1, WinningDirection::kLeftDiag));
    REQUIRE_FALSE(CheckForWinner(b, DiskType::kPlayer2));
  }
  SECTION("upper_left") {
    DropDiskToBoard(b, DiskType::kPlayer2, 1);
    DropDiskToBoard(b, DiskType::kPlayer1, 0);
    DropDiskToBoard(b, DiskType::kPlayer2, 2);
    DropDiskToBoard(b, DiskType::kPlayer2, 0);
    DropDiskToBoard(b, DiskType::kPlayer1, 3);
    DropDiskToBoard(b, DiskType::kPlayer1, 2);
    DropDiskToBoard(b, DiskType::kPlayer1, 1);
    DropDiskToBoard(b, DiskType::kPlayer1, 1);
    DropDiskToBoard(b, DiskType::kPlayer1, 0);
    DropDiskToBoard(b, DiskType::kPlayer2, 0);
    DropDiskToBoard(b, DiskType::kPlayer1, 0);
    DropDiskToBoard(b, DiskType::kPlayer2, 0);
    DropDiskToBoard(b, DiskType::kPlayer2, 1);
    DropDiskToBoard(b, DiskType::kPlayer2, 1);
    DropDiskToBoard(b, DiskType::kPlayer1, 3);
    DropDiskToBoard(b, DiskType::kPlayer2, 3);
    DropDiskToBoard(b, DiskType::kPlayer2, 2);
    DropDiskToBoard(b, DiskType::kPlayer2, 2);
    REQUIRE(CheckForWinner(b, DiskType::kPlayer2));
    REQUIRE(
        SearchForWinner(b, DiskType::kPlayer2, WinningDirection::kLeftDiag));
    REQUIRE_FALSE(CheckForWinner(b, DiskType::kPlayer1));
    DropDiskToBoard(b, DiskType::kPlayer2, 3);
    REQUIRE(CheckForWinner(b, DiskType::kPlayer2));
  }
  SECTION("lower_right") {
    DropDiskToBoard(b, DiskType::kPlayer1, 6);
    DropDiskToBoard(b, DiskType::kPlayer2, 5);
    DropDiskToBoard(b, DiskType::kPlayer2, 4);
    DropDiskToBoard(b, DiskType::kPlayer1, 3);
    DropDiskToBoard(b, DiskType::kPlayer1, 5);
    DropDiskToBoard(b, DiskType::kPlayer2, 4);
    DropDiskToBoard(b, DiskType::kPlayer1, 4);
    DropDiskToBoard(b, DiskType::kPlayer1, 3);
    DropDiskToBoard(b, DiskType::kPlayer2, 3);
    DropDiskToBoard(b, DiskType::kPlayer1, 3);
    REQUIRE(CheckForWinner(b, DiskType::kPlayer1));
    REQUIRE(
        SearchForWinner(b, DiskType::kPlayer1, WinningDirection::kLeftDiag));
    REQUIRE_FALSE(CheckForWinner(b, DiskType::kPlayer2));
    DropDiskToBoard(b, DiskType::kPlayer1, 2);
    DropDiskToBoard(b, DiskType::kPlayer1, 2);
    DropDiskToBoard(b, DiskType::kPlayer1, 2);
    DropDiskToBoard(b, DiskType::kPlayer2, 2);
    REQUIRE(CheckForWinner(b, DiskType::kPlayer2));
  }
  SECTION("upper_right") {
    DropDiskToBoard(b, DiskType::kPlayer1, 6);
    DropDiskToBoard(b, DiskType::kPlayer2, 5);
    DropDiskToBoard(b, DiskType::kPlayer2, 4);
    DropDiskToBoard(b, DiskType::kPlayer1, 3);
    DropDiskToBoard(b, DiskType::kPlayer2, 5);
    DropDiskToBoard(b, DiskType::kPlayer2, 4);
    DropDiskToBoard(b, DiskType::kPlayer1, 4);
    DropDiskToBoard(b, DiskType::kPlayer1, 3);
    DropDiskToBoard(b, DiskType::kPlayer2, 3);
    DropDiskToBoard(b, DiskType::kPlayer1, 3);
    DropDiskToBoard(b, DiskType::kPlayer1, 3);
    DropDiskToBoard(b, DiskType::kPlayer2, 3);
    DropDiskToBoard(b, DiskType::kPlayer2, 4);
    DropDiskToBoard(b, DiskType::kPlayer2, 4);
    DropDiskToBoard(b, DiskType::kPlayer1, 5);
    DropDiskToBoard(b, DiskType::kPlayer2, 5);
    DropDiskToBoard(b, DiskType::kPlayer2, 4);
    DropDiskToBoard(b, DiskType::kPlayer2, 6);
    DropDiskToBoard(b, DiskType::kPlayer2, 6);
    REQUIRE(CheckForWinner(b, DiskType::kPlayer2));
    REQUIRE(
        SearchForWinner(b, DiskType::kPlayer2, WinningDirection::kLeftDiag));
    REQUIRE_FALSE(CheckForWinner(b, DiskType::kPlayer1));
  }
}

TEST_CASE("WIN RIGHTDIAG", "[rightdiag]") {
  Board b;
  InitBoard(b);
  SECTION("in_between") {
    DropDiskToBoard(b, DiskType::kPlayer2, 5);
    DropDiskToBoard(b, DiskType::kPlayer2, 4);
    DropDiskToBoard(b, DiskType::kPlayer1, 3);
    DropDiskToBoard(b, DiskType::kPlayer2, 2);
    DropDiskToBoard(b, DiskType::kPlayer1, 1);
    DropDiskToBoard(b, DiskType::kPlayer1, 2);
    DropDiskToBoard(b, DiskType::kPlayer1, 3);
    DropDiskToBoard(b, DiskType::kPlayer1, 4);
    DropDiskToBoard(b, DiskType::kPlayer2, 5);
    DropDiskToBoard(b, DiskType::kPlayer1, 3);
    DropDiskToBoard(b, DiskType::kPlayer1, 4);
    DropDiskToBoard(b, DiskType::kPlayer1, 5);
    DropDiskToBoard(b, DiskType::kPlayer2, 1);
    DropDiskToBoard(b, DiskType::kPlayer2, 2);
    DropDiskToBoard(b, DiskType::kPlayer2, 4);
    DropDiskToBoard(b, DiskType::kPlayer2, 3);
    DropDiskToBoard(b, DiskType::kPlayer2, 4);
    REQUIRE(CheckForWinner(b, DiskType::kPlayer2));
    REQUIRE(
        SearchForWinner(b, DiskType::kPlayer2, WinningDirection::kRightDiag));
    REQUIRE_FALSE(CheckForWinner(b, DiskType::kPlayer1));
  }
  SECTION("lower_left") {
    DropDiskToBoard(b, DiskType::kPlayer1, 0);
    DropDiskToBoard(b, DiskType::kPlayer2, 1);
    DropDiskToBoard(b, DiskType::kPlayer2, 2);
    DropDiskToBoard(b, DiskType::kPlayer1, 3);
    DropDiskToBoard(b, DiskType::kPlayer1, 1);
    DropDiskToBoard(b, DiskType::kPlayer2, 2);
    DropDiskToBoard(b, DiskType::kPlayer2, 3);
    DropDiskToBoard(b, DiskType::kPlayer1, 2);
    DropDiskToBoard(b, DiskType::kPlayer1, 3);
    DropDiskToBoard(b, DiskType::kPlayer1, 3);
    REQUIRE(CheckForWinner(b, DiskType::kPlayer1));
    REQUIRE(
        SearchForWinner(b, DiskType::kPlayer1, WinningDirection::kRightDiag));
    REQUIRE_FALSE(CheckForWinner(b, DiskType::kPlayer2));
  }
  SECTION("upper_left") {
    DropDiskToBoard(b, DiskType::kPlayer1, 0);
    DropDiskToBoard(b, DiskType::kPlayer2, 1);
    DropDiskToBoard(b, DiskType::kPlayer2, 2);
    DropDiskToBoard(b, DiskType::kPlayer1, 3);
    DropDiskToBoard(b, DiskType::kPlayer1, 1);
    DropDiskToBoard(b, DiskType::kPlayer2, 2);
    DropDiskToBoard(b, DiskType::kPlayer2, 3);
    DropDiskToBoard(b, DiskType::kPlayer1, 2);
    DropDiskToBoard(b, DiskType::kPlayer1, 3);
    DropDiskToBoard(b, DiskType::kPlayer2, 3);
    DropDiskToBoard(b, DiskType::kPlayer2, 0);
    DropDiskToBoard(b, DiskType::kPlayer2, 0);
    DropDiskToBoard(b, DiskType::kPlayer2, 1);
    DropDiskToBoard(b, DiskType::kPlayer2, 1);
    DropDiskToBoard(b, DiskType::kPlayer1, 2);
    DropDiskToBoard(b, DiskType::kPlayer2, 2);
    DropDiskToBoard(b, DiskType::kPlayer1, 3);
    DropDiskToBoard(b, DiskType::kPlayer2, 3);
    REQUIRE(CheckForWinner(b, DiskType::kPlayer2));
    REQUIRE(
        SearchForWinner(b, DiskType::kPlayer2, WinningDirection::kRightDiag));
    REQUIRE_FALSE(CheckForWinner(b, DiskType::kPlayer1));
  }
  SECTION("lower_right") {
    DropDiskToBoard(b, DiskType::kPlayer1, 3);
    DropDiskToBoard(b, DiskType::kPlayer2, 4);
    DropDiskToBoard(b, DiskType::kPlayer2, 5);
    DropDiskToBoard(b, DiskType::kPlayer1, 6);
    DropDiskToBoard(b, DiskType::kPlayer1, 4);
    DropDiskToBoard(b, DiskType::kPlayer2, 6);
    DropDiskToBoard(b, DiskType::kPlayer2, 6);
    DropDiskToBoard(b, DiskType::kPlayer1, 5);
    DropDiskToBoard(b, DiskType::kPlayer1, 5);
    DropDiskToBoard(b, DiskType::kPlayer1, 6);
    REQUIRE(CheckForWinner(b, DiskType::kPlayer1));
    REQUIRE(
        SearchForWinner(b, DiskType::kPlayer1, WinningDirection::kRightDiag));
    REQUIRE_FALSE(CheckForWinner(b, DiskType::kPlayer2));
  }
  SECTION("upper_right") {
    DropDiskToBoard(b, DiskType::kPlayer1, 3);
    DropDiskToBoard(b, DiskType::kPlayer2, 4);
    DropDiskToBoard(b, DiskType::kPlayer2, 5);
    DropDiskToBoard(b, DiskType::kPlayer1, 6);
    DropDiskToBoard(b, DiskType::kPlayer1, 4);
    DropDiskToBoard(b, DiskType::kPlayer2, 6);
    DropDiskToBoard(b, DiskType::kPlayer2, 6);
    DropDiskToBoard(b, DiskType::kPlayer1, 5);
    DropDiskToBoard(b, DiskType::kPlayer1, 5);
    DropDiskToBoard(b, DiskType::kPlayer2, 6);
    DropDiskToBoard(b, DiskType::kPlayer1, 6);
    DropDiskToBoard(b, DiskType::kPlayer2, 6);
    DropDiskToBoard(b, DiskType::kPlayer1, 2);
    DropDiskToBoard(b, DiskType::kPlayer2, 1);
    DropDiskToBoard(b, DiskType::kPlayer2, 3);
    DropDiskToBoard(b, DiskType::kPlayer2, 3);
    DropDiskToBoard(b, DiskType::kPlayer1, 4);
    DropDiskToBoard(b, DiskType::kPlayer2, 4);
    DropDiskToBoard(b, DiskType::kPlayer1, 5);
    DropDiskToBoard(b, DiskType::kPlayer2, 5);
    REQUIRE(CheckForWinner(b, DiskType::kPlayer2));
    REQUIRE(
        SearchForWinner(b, DiskType::kPlayer2, WinningDirection::kRightDiag));
    REQUIRE_FALSE(CheckForWinner(b, DiskType::kPlayer1));
  }
}

TEST_CASE("WIN IN MULTIPLE WAYS", "[winwinwin]") {
  Board b;
  InitBoard(b);
  DropDiskToBoard(b, DiskType::kPlayer2, 6);
  DropDiskToBoard(b, DiskType::kPlayer2, 5);
  DropDiskToBoard(b, DiskType::kPlayer2, 4);
  DropDiskToBoard(b, DiskType::kPlayer1, 3);
  DropDiskToBoard(b, DiskType::kPlayer1, 2);
  DropDiskToBoard(b, DiskType::kPlayer1, 1);
  SECTION("horizontal_rightdiag") {
    DropDiskToBoard(b, DiskType::kPlayer1, 0);
    REQUIRE(
        SearchForWinner(b, DiskType::kPlayer1, WinningDirection::kHorizontal));
    REQUIRE(CheckForWinner(b, DiskType::kPlayer1));
    DropDiskToBoard(b, DiskType::kPlayer1, 1);
    DropDiskToBoard(b, DiskType::kPlayer2, 2);
    DropDiskToBoard(b, DiskType::kPlayer1, 2);
    DropDiskToBoard(b, DiskType::kPlayer2, 3);
    DropDiskToBoard(b, DiskType::kPlayer2, 3);
    DropDiskToBoard(b, DiskType::kPlayer1, 3);
    REQUIRE(
        SearchForWinner(b, DiskType::kPlayer1, WinningDirection::kRightDiag));
    REQUIRE(CheckForWinner(b, DiskType::kPlayer1));
    DropDiskToBoard(b, DiskType::kPlayer2, 4);
    DropDiskToBoard(b, DiskType::kPlayer2, 5);
    REQUIRE(CheckForWinner(b, DiskType::kPlayer2));
    REQUIRE(
        SearchForWinner(b, DiskType::kPlayer2, WinningDirection::kHorizontal));
  }
  SECTION("horizontal_vertical") {
    DropDiskToBoard(b, DiskType::kPlayer1, 0);
    DropDiskToBoard(b, DiskType::kPlayer1, 0);
    DropDiskToBoard(b, DiskType::kPlayer1, 0);
    DropDiskToBoard(b, DiskType::kPlayer1, 0);
    REQUIRE(CheckForWinner(b, DiskType::kPlayer1));
  }
  SECTION("left_right") {
    DropDiskToBoard(b, DiskType::kPlayer1, 2);
    DropDiskToBoard(b, DiskType::kPlayer2, 3);
    DropDiskToBoard(b, DiskType::kPlayer1, 3);
    DropDiskToBoard(b, DiskType::kPlayer1, 4);
    DropDiskToBoard(b, DiskType::kPlayer2, 4);
    DropDiskToBoard(b, DiskType::kPlayer1, 4);
    DropDiskToBoard(b, DiskType::kPlayer2, 2);
    DropDiskToBoard(b, DiskType::kPlayer1, 2);
    DropDiskToBoard(b, DiskType::kPlayer1, 1);
    DropDiskToBoard(b, DiskType::kPlayer1, 1);
    DropDiskToBoard(b, DiskType::kPlayer2, 1);
    REQUIRE(CheckForWinner(b, DiskType::kPlayer2));
    DropDiskToBoard(b, DiskType::kPlayer1, 1);
    REQUIRE(CheckForWinner(b, DiskType::kPlayer1));
  }
}

TEST_CASE("PLAY EVEN", "[noWinner]") {
  Board b;
  InitBoard(b);
  DropDiskToBoard(b, DiskType::kPlayer1, 6);
  DropDiskToBoard(b, DiskType::kPlayer2, 5);
  DropDiskToBoard(b, DiskType::kPlayer1, 6);
  DropDiskToBoard(b, DiskType::kPlayer2, 5);
  DropDiskToBoard(b, DiskType::kPlayer2, 6);
  DropDiskToBoard(b, DiskType::kPlayer1, 6);
  DropDiskToBoard(b, DiskType::kPlayer2, 6);
  DropDiskToBoard(b, DiskType::kPlayer1, 6);
  DropDiskToBoard(b, DiskType::kPlayer1, 0);
  DropDiskToBoard(b, DiskType::kPlayer2, 3);
  DropDiskToBoard(b, DiskType::kPlayer1, 4);
  DropDiskToBoard(b, DiskType::kPlayer1, 2);
  DropDiskToBoard(b, DiskType::kPlayer2, 1);
  DropDiskToBoard(b, DiskType::kPlayer2, 0);
  DropDiskToBoard(b, DiskType::kPlayer1, 1);
  DropDiskToBoard(b, DiskType::kPlayer2, 2);
  DropDiskToBoard(b, DiskType::kPlayer1, 2);
  DropDiskToBoard(b, DiskType::kPlayer2, 2);
  DropDiskToBoard(b, DiskType::kPlayer1, 4);
  DropDiskToBoard(b, DiskType::kPlayer2, 4);
  DropDiskToBoard(b, DiskType::kPlayer1, 1);
  DropDiskToBoard(b, DiskType::kPlayer2, 1);
  DropDiskToBoard(b, DiskType::kPlayer1, 4);
  DropDiskToBoard(b, DiskType::kPlayer2, 4);
  DropDiskToBoard(b, DiskType::kPlayer1, 1);
  DropDiskToBoard(b, DiskType::kPlayer2, 1);
  DropDiskToBoard(b, DiskType::kPlayer1, 4);
  DropDiskToBoard(b, DiskType::kPlayer2, 5);
  DropDiskToBoard(b, DiskType::kPlayer1, 2);
  DropDiskToBoard(b, DiskType::kPlayer2, 3);
  DropDiskToBoard(b, DiskType::kPlayer1, 3);
  DropDiskToBoard(b, DiskType::kPlayer2, 0);
  DropDiskToBoard(b, DiskType::kPlayer1, 5);
  DropDiskToBoard(b, DiskType::kPlayer1, 0);
  DropDiskToBoard(b, DiskType::kPlayer2, 3);
  DropDiskToBoard(b, DiskType::kPlayer2, 0);
  DropDiskToBoard(b, DiskType::kPlayer2, 5);
  DropDiskToBoard(b, DiskType::kPlayer1, 3);
  DropDiskToBoard(b, DiskType::kPlayer1, 0);
  DropDiskToBoard(b, DiskType::kPlayer1, 2);
  DropDiskToBoard(b, DiskType::kPlayer2, 3);
  DropDiskToBoard(b, DiskType::kPlayer1, 5);
  REQUIRE_FALSE(CheckForWinner(b, DiskType::kPlayer1));
  REQUIRE_FALSE(CheckForWinner(b, DiskType::kPlayer2));
}

/////////////////////////////////////////////////////////////////////////////////////////////