#ifndef GRAYSCALE_IMAGE_H
#define GRAYSCALE_IMAGE_H

#include <cstdlib>  // for size_t
#include <string>
#include <vector>

#include "color.hpp"
#include "elevation_dataset.hpp"

class GrayscaleImage {
public:
  GrayscaleImage(const ElevationDataset& dataset);
  // Initializes the primitive data members with their respective values as read
  // from the dataset; populates the two-dimensional
  // std::vector<std::vector<Color>> with Color representation of each elevation
  // datum. Sets width_ and height_ appropriately.
  GrayscaleImage(const std::string& filename, size_t width, size_t height);
  // Initializes the primitive data members with their respective values as read
  // from the file; populates the two-dimensional
  // std::vector<std::vector<Color>> with translated Color representation from
  // each read elevation datum. Sets width_ and height_ appropriately.
  size_t Width() const;
  // Returns the width of the image
  size_t Height() const;
  // Returns the height of the image
  unsigned int MaxColorValue() const;
  // Returns the value stored in kMaxColorValue
  const Color& ColorAt(int row, int col) const;
  // Returns the Color at row col by reference to const
  const std::vector<std::vector<Color>>& GetImage() const;
  // Returns reference to const to image_.
  void ToPpm(const std::string& name) const;
  // Writes out image_ in plain PPM format; filename is name.

private:
  size_t width_;
  size_t height_;
  std::vector<std::vector<Color>> image_;
  static const int kMaxColorValue = 255;
};

#endif