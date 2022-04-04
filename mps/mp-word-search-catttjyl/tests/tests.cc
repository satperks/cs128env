// clang-format off
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
//  Written By : Student Name                    Environment : ubuntu:bionic               //
//  Date ......: 2021/02/10                      Compiler ...: clang-10                    //
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
// clang-format on
/////////////////////////////////////////////////////////////////////////////////////////////
//                             Framework Set-up //
/////////////////////////////////////////////////////////////////////////////////////////////
#include "catch.hpp"

/////////////////////////////////////////////////////////////////////////////////////////////
//                                 Includes //
/////////////////////////////////////////////////////////////////////////////////////////////
#include <stdexcept>

#include "CharPositions.hpp"
#include "WordLocation.hpp"
#include "WordSearchSolver.hpp"

/////////////////////////////////////////////////////////////////////////////////////////////
//                             Helpers/Constants //
/////////////////////////////////////////////////////////////////////////////////////////////
bool operator==(const WordLocation& w1, const WordLocation& w2) {
  if (w1.word == "" && w2.word == "") {
    return true;
  }
  if (w1.word == w2.word &&
      w1.char_positions.size() == w2.char_positions.size()) {
    for (size_t i = 0; i < w1.char_positions.size(); i++) {
      if (w1.char_positions.at(i).character ==
              w2.char_positions.at(i).character &&
          w1.char_positions.at(i).col == w2.char_positions.at(i).col &&
          w1.char_positions.at(i).row == w2.char_positions.at(i).row) {
        return true;
      }
    }
  }
  return false;
}
/////////////////////////////////////////////////////////////////////////////////////////////
//                                Test Cases //
/////////////////////////////////////////////////////////////////////////////////////////////

// TEST_CASE("BASIC CHECK", "[BASIC]") {
//   std::vector<std::vector<char>> puzzle{{'d', 'e', 'a', 'o', 'u'},
//                                         {'h', 'e', 'l', 'l', 'o'},
//                                         {'c', 'a', 'l', 'o', 'm'},
//                                         {'a', 'e', 't', 'a', 'u'},
//                                         {'t', 'e', 't', 'o', 'u'}};
//   WordSearchSolver wss(puzzle);
// }

TEST_CASE("CHECK HORIZONTAL", "[HORIZONTAL]") {
  SECTION("upper_left_loop") {
    std::vector<std::vector<char>> puzzle{{'d', 'e', 'd', 'o', 'u'},
                                          {'h', 'e', 'l', 'l', 'o'},
                                          {'c', 'a', 'l', 'o', 'm'},
                                          {'a', 'e', 't', 'a', 'u'},
                                          {'t', 'e', 't', 'o', 'u'}};
    WordSearchSolver wss(puzzle);
    std::vector<CharPositions> char_position = {
        {'d', 0, 0}, {'e', 0, 1}, {'d', 0, 2}};
    WordLocation correct = {"ded", char_position};
    REQUIRE(wss.FindWord("ded") == correct);
    REQUIRE(wss.FindWord("ded", CheckDirection::kHorizontal) == correct);
  }
  SECTION("lower_right_duplicate") {
    std::vector<std::vector<char>> puzzle{{'h', 'e', 'a', 'o', 'u'},
                                          {'r', 'e', 'j', 'c', 'o'},
                                          {'l', 'a', 'l', 'o', 'm'},
                                          {'l', 'e', 't', 'a', 'u'},
                                          {'o', 'e', 't', 'o', 'u'},
                                          {'k', 'i', 'a', 'k', 'f'},
                                          {'a', 'f', 'g', 'e', 'k'},
                                          {'c', 'b', 'b', 'y', 'u'}};
    WordSearchSolver wss(puzzle);
    std::vector<CharPositions> char_position = {
        {'b', 7, 1}, {'b', 7, 2}, {'y', 7, 3}, {'u', 7, 4}};
    WordLocation correct = {"bbyu", char_position};
    REQUIRE(wss.FindWord("bbyu") == correct);
    REQUIRE(wss.FindWord("bbyu", CheckDirection::kHorizontal) == correct);
  }
  SECTION("change_line") {
    std::vector<std::vector<char>> puzzle{{'h', 'e', 'a', 'o'},
                                          {'h', 'e', 'j', 'c'},
                                          {'l', 'a', 'l', 'o'},
                                          {'l', 'e', 'r', 'a'},
                                          {'o', 'e', 't', 'o'},
                                          {'k', 'o', 'h', 'k'},
                                          {'p', 'v', 'h', 'q'}};
    WordSearchSolver wss(puzzle);
    REQUIRE(wss.FindWord("raoe") == WordLocation{});
    REQUIRE(wss.FindWord("raoe", CheckDirection::kHorizontal) ==
            WordLocation{});
  }
}

TEST_CASE("CHECK VERTICAL", "[VERTICAL]") {
  SECTION("upper_left_loop") {
    std::vector<std::vector<char>> puzzle{{'h', 'e', 'a', 'o', 'u'},
                                          {'a', 'e', 'j', 'c', 'o'},
                                          {'h', 'a', 'l', 'o', 'm'},
                                          {'h', 'e', 't', 'a', 'u'},
                                          {'o', 'e', 't', 'o', 'u'},
                                          {'k', 'o', 'h', 'k', 'f'}};
    WordSearchSolver wss(puzzle);
    std::vector<CharPositions> char_position = {
        {'h', 0, 0}, {'a', 1, 0}, {'h', 2, 0}, {'h', 3, 0}};
    WordLocation correct = {"hahh", char_position};
    REQUIRE(wss.FindWord("hahh") == correct);
    REQUIRE(wss.FindWord("hahh", CheckDirection::kVertical) == correct);
  }
  SECTION("lower_right_duplicate") {
    std::vector<std::vector<char>> puzzle{{'h', 'e', 'a', 'u'},
                                          {'h', 'e', 'j', 'm'},
                                          {'l', 'a', 'l', 'm'},
                                          {'l', 'e', 'a', 'u'},
                                          {'o', 't', 'o', 'z'},
                                          {'k', 'h', 'k', 'f'}};
    WordSearchSolver wss(puzzle);
    std::vector<CharPositions> char_position = {
        {'m', 2, 3}, {'u', 3, 3}, {'z', 4, 3}, {'f', 5, 3}};
    WordLocation correct = {"muzf", char_position};
    REQUIRE(wss.FindWord("muzf") == correct);
    REQUIRE(wss.FindWord("muzf", CheckDirection::kVertical) == correct);
  }
  SECTION("change_line") {
    std::vector<std::vector<char>> puzzle{{'h', 'e', 'a', 'o', 'u', 's'},
                                          {'h', 'e', 'j', 'c', 'o', 'r'},
                                          {'l', 'a', 'l', 'g', 'o', 'm'},
                                          {'l', 'e', 'p', 'r', 'a', 'u'},
                                          {'o', 'e', 't', 'o', 'q', 'u'},
                                          {'k', 'n', 'h', 'p', 'k', 'f'}};
    WordSearchSolver wss(puzzle);
    REQUIRE(wss.FindWord("thoc") == WordLocation{});
    REQUIRE(wss.FindWord("thoc", CheckDirection::kVertical) == WordLocation{});
  }
}

TEST_CASE("CHECK RIGHT_DIAG", "[RIGHTDIAG]") {
  SECTION("upper_left_loop") {
    std::vector<std::vector<char>> puzzle{{'d', 'e', 'a', 'o', 'u'},
                                          {'h', 'e', 'l', 'l', 'o'},
                                          {'c', 'a', 'd', 'o', 'm'},
                                          {'a', 'e', 't', 'a', 'u'},
                                          {'t', 'e', 't', 'o', 'u'},
                                          {'i', 'k', 'h', 'g', 's'}};
    WordSearchSolver wss(puzzle);
    std::vector<CharPositions> char_position = {
        {'d', 0, 0}, {'e', 1, 1}, {'d', 2, 2}};
    WordLocation correct = {"ded", char_position};
    REQUIRE(wss.FindWord("ded") == correct);
    REQUIRE(wss.FindWord("ded", CheckDirection::kRightDiag) == correct);
  }
  SECTION("lower_right_duplicate") {
    std::vector<std::vector<char>> puzzle{{'d', 'e', 'a', 'o', 'u', 'z', 'w'},
                                          {'h', 'e', 'l', 'l', 'o', 'j', 'i'},
                                          {'c', 'a', 'd', 'o', 'm', 'o', 'f'},
                                          {'a', 'e', 't', 'a', 'u', 'g', 's'},
                                          {'t', 'e', 't', 't', 'u', 'd', 'k'},
                                          {'i', 'k', 'h', 'g', 's', 'm', 'j'},
                                          {'f', 'e', 'n', 'z', 'm', 'e', 'l'},
                                          {'c', 'q', 'd', 'b', 's', 'l', 'w'}};
    WordSearchSolver wss(puzzle);
    std::vector<CharPositions> char_position = {
        {'t', 4, 3}, {'s', 5, 4}, {'e', 6, 5}, {'w', 7, 6}};
    WordLocation correct = {"tsew", char_position};
    REQUIRE(wss.FindWord("tsew") == correct);
    REQUIRE(wss.FindWord("tsew", CheckDirection::kRightDiag) == correct);
  }
}

TEST_CASE("CHECK LEFT_DIAG", "[LEFTDIAG]") {
  SECTION("upper_left_loop") {
    std::vector<std::vector<char>> puzzle{{'d', 'e', 'z', 'o'},
                                          {'h', 'e', 'l', 'o'},
                                          {'z', 'a', 'o', 'm'},
                                          {'a', 't', 'a', 'u'},
                                          {'e', 't', 'o', 'u'},
                                          {'w', 'e', 'f', 'g'},
                                          {'c', 'q', 'n', 'r'}};
    WordSearchSolver wss(puzzle);
    std::vector<CharPositions> char_position = {
        {'z', 2, 0}, {'e', 1, 1}, {'z', 2, 0}};
    WordLocation correct = {"zez", char_position};
    REQUIRE(wss.FindWord("zez") == correct);
    REQUIRE(wss.FindWord("zez", CheckDirection::kLeftDiag) == correct);
  }
  SECTION("lower_right_duplicate") {
    std::vector<std::vector<char>> puzzle{{'d', 'e', 'z', 'o', 'q', 'i', 'd'},
                                          {'h', 'e', 'l', 'o', 'a', 't', 'f'},
                                          {'z', 'a', 'o', 'm', 'w', 'f', 'n'},
                                          {'a', 't', 'a', 'u', 's', 'a', 'k'},
                                          {'e', 't', 'o', 'v', 'u', 'o', 'p'},
                                          {'w', 'e', 'y', 'g', 'x', 'm', 'l'}};
    WordSearchSolver wss(puzzle);
    std::vector<CharPositions> char_position = {
        {'f', 2, 5}, {'s', 3, 4}, {'v', 4, 3}, {'y', 5, 2}};
    WordLocation correct = {"fsvy", char_position};
    REQUIRE(wss.FindWord("fsvy") == correct);
    REQUIRE(wss.FindWord("fsvy", CheckDirection::kLeftDiag) == correct);
  }
  SECTION("incomplete") {
    std::vector<std::vector<char>> puzzle{{'d', 'e', 'z', 'o', 'q', 'i'},
                                          {'h', 'e', 'l', 'o', 'a', 'f'},
                                          {'z', 'a', 'b', 'm', 'f', 'n'},
                                          {'a', 'p', 'a', 's', 'a', 'k'},
                                          {'e', 't', 'v', 'u', 'o', 'p'},
                                          {'w', 'y', 'g', 'x', 'm', 'l'}};
    WordSearchSolver wss(puzzle);
    REQUIRE(wss.FindWord("qobt") == WordLocation{});
    REQUIRE(wss.FindWord("qobt", CheckDirection::kRightDiag) == WordLocation{});
  }
}

/////////////////////////////////////////////////////////////////////////////////////////////