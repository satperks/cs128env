#include "elevation_dataset.hpp"

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

void CheckForExtre(const std::vector<int>& input, int& max, int& min) {
  max = input.at(0);
  min = input.at(0);
  for (size_t i = 0; i < input.size(); i++) {
    if (input.at(i) > max) {
      max = input.at(i);
    }
    if (input.at(i) < min) {
      min = input.at(i);
    }
  }
}

ElevationDataset::ElevationDataset(const std::string& filename,
                                   size_t width,
                                   size_t height):
    width_(width), height_(height) {
  int max = 0;
  int min = 0;
  std::ifstream ifs{filename};
  if (!ifs.is_open()) throw std::runtime_error("unable to open file");

  std::vector<int> tmp;
  for (std::string line; std::getline(ifs, line); line = "") {
    size_t last = 0;
    for (size_t i = 0; i != line.length(); i++) {
      if (line.at(i) == ' ') {
        std::string each = line.substr(last, i - last);
        if (each.empty()) {
          last = i + 1;
          continue;
        }
        last = i + 1;
        tmp.push_back(stoi(each));
      }
    }
    std::string each = line.substr(last, line.length() - last);
    if (!each.empty()) tmp.push_back(stoi(each));
  }
  if (tmp.size() != width_ * height_)
    throw std::runtime_error(
        "matrix not filled with or enough for data points");
  CheckForExtre(tmp, max, min);
  max_ele_ = max;
  min_ele_ = min;
  size_t i = 0;
  for (size_t row = 0; row < height_; row++) {
    std::vector<int> datatmp;
    for (size_t col = 0; col < width_; col++) {
      datatmp.push_back(tmp.at(i));
      i++;
    }
    data_.push_back(datatmp);
  }
}

size_t ElevationDataset::Width() const { return width_; }

size_t ElevationDataset::Height() const { return height_; }

int ElevationDataset::MaxEle() const { return max_ele_; }

int ElevationDataset::MinEle() const { return min_ele_; }

int ElevationDataset::DatumAt(size_t row, size_t col) const {
  return data_.at(row).at(col);
}

const std::vector<std::vector<int>>& ElevationDataset::GetData() const {
  return data_;
}

// size_t width_;
// size_t height_;
// std::vector<std::vector<int>> data_;
// int max_ele_;
// int min_ele_;
