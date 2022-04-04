#include "WordSearchSolver.hpp"

#include <iostream>
#include <string>
#include <vector>

bool WordSearchSolver::LocationInBounds(size_t row, size_t col) const {
  return ((row < puzzle_height_) && (col < puzzle_width_));
}

WordSearchSolver::WordSearchSolver(
    const std::vector<std::vector<char>>& puzzle):
    puzzle_(puzzle) {
  puzzle_height_ = puzzle.size();
  puzzle_width_ = puzzle.at(0).size();
}

WordLocation WordSearchSolver::FindWord(const std::string& word) {
  if (FindWord(word, CheckDirection::kHorizontal).word == word)
    return FindWord(word, CheckDirection::kHorizontal);
  if (FindWord(word, CheckDirection::kVertical).word == word)
    return FindWord(word, CheckDirection::kVertical);
  if (FindWord(word, CheckDirection::kLeftDiag).word == word)
    return FindWord(word, CheckDirection::kLeftDiag);
  if (FindWord(word, CheckDirection::kRightDiag).word == word)
    return FindWord(word, CheckDirection::kRightDiag);
  return WordLocation{};
}

WordLocation WordSearchSolver::FindWord(const std::string& word,
                                        CheckDirection direction) {
  std::vector<CharPositions> char_positions;
  if (direction == CheckDirection::kHorizontal ||
      direction == CheckDirection::kVertical ||
      direction == CheckDirection::kLeftDiag ||
      direction == CheckDirection::kRightDiag) {
    if (CheckForHorizontal(word, char_positions) ||
        CheckForVertical(word, char_positions) ||
        CheckForLeftDiag(word, char_positions) ||
        CheckForRightDiag(word, char_positions)) {
      WordLocation w = {word, char_positions};
      return w;
    }
  }
  return WordLocation{};
}

bool WordSearchSolver::CheckForHorizontal(
    const std::string& word, std::vector<CharPositions>& char_positions) {
  if (word.length() > puzzle_width_) return false;
  for (size_t row = 0; row < puzzle_height_; row++) {
    for (size_t col = 0; col < puzzle_width_ - word.length() + 1; col++) {
      for (size_t i = 0; i < word.length(); i++) {
        if (puzzle_.at(row).at(col + i) == word.at(i)) {
          CharPositions tmp = {word.at(i), row, col + i};
          char_positions.push_back(tmp);
          if (char_positions.size() == word.length()) {
            return true;
          }
        } else {
          char_positions.clear();
        }
      }
    }
  }
  return false;
}

bool WordSearchSolver::CheckForVertical(
    const std::string& word, std::vector<CharPositions>& char_positions) {
  if (word.length() > puzzle_height_) return false;
  for (size_t col = 0; col < puzzle_width_; col++) {
    for (size_t row = 0; row < puzzle_height_ - word.length() + 1; row++) {
      char_positions.clear();
      for (size_t i = 0; i < word.length(); i++) {
        if (puzzle_.at(row + i).at(col) == word.at(i)) {
          CharPositions tmp = {word.at(i), row + i, col};
          char_positions.push_back(tmp);
          if (char_positions.size() == word.length()) {
            return true;
          }
        } else {
          char_positions.clear();
        }
      }
    }
  }
  return false;
  ;
}

bool WordSearchSolver::CheckForRightDiag(
    const std::string& word, std::vector<CharPositions>& char_positions) {
  if (word.length() > puzzle_height_ || word.length() > puzzle_width_)
    return false;
  for (size_t row = 0; row < puzzle_height_ - word.length() + 1; row++) {
    for (size_t col = word.length() - 1; col < puzzle_width_; col++) {
      for (size_t i = 0; i < word.length(); i++) {
        if (puzzle_.at(row + i).at(col - i) == word.at(i)) {
          CharPositions tmp = {word.at(i), row + i, col - i};
          char_positions.push_back(tmp);
          if (char_positions.size() == word.size()) {
            return true;
          }
        } else {
          char_positions.clear();
        }
      }
    }
  }
  return false;
}

bool WordSearchSolver::CheckForLeftDiag(
    const std::string& word, std::vector<CharPositions>& char_positions) {
  if (word.length() > puzzle_height_ || word.length() > puzzle_width_)
    return false;
  for (size_t row = 0; row < puzzle_height_ - word.length() + 1; row++) {
    for (size_t col = 0; col < puzzle_width_ - word.length() + 1; col++) {
      char_positions.clear();
      for (size_t i = 0; i < word.length(); i++) {
        if (puzzle_.at(row + i).at(col + i) == word.at(i)) {
          CharPositions tmp = {word.at(i), row + i, col + i};
          char_positions.push_back(tmp);
          if (char_positions.size() == word.size()) {
            return true;
          }
        } else {
          char_positions.clear();
        }
      }
    }
  }
  return false;
}
