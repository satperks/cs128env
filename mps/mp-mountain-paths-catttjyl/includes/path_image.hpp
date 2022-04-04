#ifndef PATH_IMAGE_H
#define PATH_IMAGE_H

#include <cstdlib>  // for size_t
#include <string>
#include <vector>

#include "color.hpp"
#include "elevation_dataset.hpp"
#include "grayscale_image.hpp"
#include "path.hpp"

class PathImage {
public:
  PathImage(const GrayscaleImage& image, const ElevationDataset& dataset);
  // Initializes the primitive data members with their respective values read
  // from image; populates the two-dimensional std::vector<std::vector<Color>>
  // with values from the image’s image_. Calculates and stores all paths
  // through the image; you may wish to maintain the row of the best path in a
  // variable best_path_row_.
  void AssignGreen(const std::vector<std::vector<int>>& data_copy,
                   std::vector<std::vector<Color>>& image_copy);
  size_t Width() const;
  // Returns the width of the image
  size_t Height() const;
  // Returns the height of the image
  unsigned int MaxColorValue() const;
  // Returns the value stored in max_color_value_
  const std::vector<Path>& Paths() const;
  // Returns reference to const to paths_.
  const std::vector<std::vector<Color>>& GetPathImage() const;
  // Returns reference to const to path_image_.
  void ToPpm(const std::string& name) const;
  // Writes out path_image_ in plain PPM format; filename is name.

private:
  std::vector<Path> paths_;
  size_t width_ = 0;
  size_t height_ = 0;
  std::vector<std::vector<Color>> path_image_;
  static const int kMaxColorValue = 255;
  static const int kRedR = 252;
  static const int kRedG = 25;
  static const int kRedB = 63;
  static const int kGreenR = 31;
  static const int kGreenG = 253;
  static const int kGreenB = 13;
};

#endif