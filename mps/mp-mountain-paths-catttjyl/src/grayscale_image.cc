#include "grayscale_image.hpp"

#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>

#include "color.hpp"
#include "elevation_dataset.hpp"

GrayscaleImage::GrayscaleImage(const ElevationDataset& dataset) {
  width_ = dataset.Width();
  height_ = dataset.Height();
  for (size_t row = 0; row < height_; row++) {
    std::vector<Color> image_tmp;
    for (size_t col = 0; col < width_; col++) {
      int shade_of_gray = 0;
      if (dataset.MaxEle() != dataset.MinEle())
        shade_of_gray = (int)std::round(
            (double)(dataset.DatumAt(row, col) - dataset.MinEle()) /
            (double)(dataset.MaxEle() - dataset.MinEle()) * kMaxColorValue);
      Color tmp(shade_of_gray, shade_of_gray, shade_of_gray);
      image_tmp.push_back(tmp);
    }
    image_.push_back(image_tmp);
  }
  // std::cout << "[HERE] successfully run grayscale constructor" << std::endl;
}
// Initializes the primitive data members with their respective values as read
// from the dataset; populates the two-dimensional
// std::vector<std::vector<Color>> with Color representation of each elevation
// datum. Sets width_ and height_ appropriately.

GrayscaleImage::GrayscaleImage(const std::string& filename,
                               size_t width,
                               size_t height):
    width_(width), height_(height) {
  ElevationDataset dataset(filename, width, height);
  for (size_t row = 0; row < height_; row++) {
    std::vector<Color> image_tmp;
    for (size_t col = 0; col < width_; col++) {
      int shade_of_gray = 0;
      if (dataset.MaxEle() != dataset.MinEle())
        shade_of_gray = (int)std::round(
            (double)(dataset.DatumAt(row, col) - dataset.MinEle()) /
            (double)(dataset.MaxEle() - dataset.MinEle()) * kMaxColorValue);
      Color tmp(shade_of_gray, shade_of_gray, shade_of_gray);
      image_tmp.push_back(tmp);
    }
    image_.push_back(image_tmp);
  }
}
// Initializes the primitive data members with their respective values as read
// from the file; populates the two-dimensional std::vector<std::vector<Color>>
// with translated Color representation from each read elevation datum. Sets
// width_ and height_ appropriately.

size_t GrayscaleImage::Width() const { return width_; }

size_t GrayscaleImage::Height() const { return height_; }

unsigned int GrayscaleImage::MaxColorValue() const { return kMaxColorValue; }

const Color& GrayscaleImage::ColorAt(int row, int col) const {
  return image_.at(row).at(col);
}

const std::vector<std::vector<Color>>& GrayscaleImage::GetImage() const {
  return image_;
}

void GrayscaleImage::ToPpm(const std::string& name) const {
  std::ofstream ofs{name};
  ofs << "P3"
      << "\n"
      << width_ << " " << height_ << "\n"
      << "255" << std::endl;
  for (size_t row = 0; row < height_; row++) {
    std::string each_line;
    for (size_t col = 0; col < width_; col++) {
      Color tmp = image_.at(row).at(col);
      each_line += std::to_string(tmp.Red()) + " " +
                   std::to_string(tmp.Green()) + " " +
                   std::to_string(tmp.Blue()) + " ";
    }
    each_line = each_line.substr(0, each_line.length() - 1);
    ofs << each_line << std::endl;
  }
}

// size_t width_;
// size_t height_;
// std::vector<std::vector<Color>> image_;
// static const int kMaxColorValue = 255;
