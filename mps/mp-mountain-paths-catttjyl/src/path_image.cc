#include "path_image.hpp"

#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "color.hpp"
#include "elevation_dataset.hpp"
#include "grayscale_image.hpp"
#include "path.hpp"

void PathImage::AssignGreen(const std::vector<std::vector<int>>& data_copy,
                            std::vector<std::vector<Color>>& image_copy) {
  Color green(kGreenR, kGreenG, kGreenB);
  unsigned int least_change = paths_.at(0).EleChange();
  size_t least_row = 0;
  for (size_t i = 0; i < paths_.size(); i++) {
    if (paths_.at(i).EleChange() < least_change) {
      least_change = paths_.at(i).EleChange();
      least_row = i;
    }
  }
  size_t current_row = least_row;
  image_copy.at(current_row).at(0) = green;
  for (size_t col = 1; col < width_; col++) {
    size_t tmp = current_row;
    int current_value = data_copy.at(current_row).at(col - 1);
    int least_ele = abs(current_value - data_copy.at(current_row).at(col));
    if (tmp != height_ - 1) {
      int down = abs(current_value - data_copy.at(tmp + 1).at(col));
      if (down < least_ele) {
        least_ele = down;
        current_row = tmp + 1;
      }
    }
    if (tmp != 0) {
      int up = abs(current_value - data_copy.at(tmp - 1).at(col));
      if (up < least_ele) {
        least_ele = up;
        current_row = tmp - 1;
      }
    }
    image_copy.at(current_row).at(col) = green;
  }
}

PathImage::PathImage(const GrayscaleImage& image,
                     const ElevationDataset& dataset) {
  height_ = dataset.Height();
  width_ = dataset.Width();
  Color red(kRedR, kRedG, kRedB);
  std::vector<std::vector<int>> data_copy = dataset.GetData();
  std::vector<std::vector<Color>> image_copy = image.GetImage();
  for (size_t h = 0; h < height_; h++) {
    Path p(width_, h);
    size_t current_row = h;
    image_copy.at(h).at(0) = red;
    for (size_t col = 1; col < width_; col++) {
      size_t tmp = current_row;
      int current_value = data_copy.at(current_row).at(col - 1);
      int least_ele = abs(current_value - data_copy.at(current_row).at(col));
      if (tmp != height_ - 1) {
        int down = abs(current_value - data_copy.at(tmp + 1).at(col));
        if (down < least_ele) {
          least_ele = down;
          current_row = tmp + 1;
        }
      }
      if (tmp != 0) {
        int up = abs(current_value - data_copy.at(tmp - 1).at(col));
        if (up < least_ele) {
          least_ele = up;
          current_row = tmp - 1;
        }
      }
      p.SetLoc(col, current_row);
      p.IncEleChange(least_ele);
      image_copy.at(current_row).at(col) = red;
    }
    paths_.push_back(p);
  }
  AssignGreen(data_copy, image_copy);
  path_image_ = image_copy;
}

size_t PathImage::Width() const { return width_; }

size_t PathImage::Height() const { return height_; }

unsigned int PathImage::MaxColorValue() const { return kMaxColorValue; }

const std::vector<Path>& PathImage::Paths() const { return paths_; }

const std::vector<std::vector<Color>>& PathImage::GetPathImage() const {
  return path_image_;
}

void PathImage::ToPpm(const std::string& name) const {
  std::ofstream ofs{name};
  ofs << "P3"
      << "\n"
      << width_ << " " << height_ << "\n"
      << "255" << std::endl;
  for (size_t row = 0; row < height_; row++) {
    std::string each_line;
    for (size_t col = 0; col < width_; col++) {
      Color tmp = path_image_.at(row).at(col);
      each_line += std::to_string(tmp.Red()) + " " +
                   std::to_string(tmp.Green()) + " " +
                   std::to_string(tmp.Blue()) + " ";
    }
    each_line = each_line.substr(0, each_line.length() - 1);
    ofs << each_line << std::endl;
  }
}

// std::vector<Path> paths_;
// size_t width_ = 0;
// size_t height_ = 0;
// std::vector<std::vector<Color>> path_image_;
// static const int kMaxColorValue = 255;
