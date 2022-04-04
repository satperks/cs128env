#include "image_ppm.hpp"

#include "pixel.hpp"

Pixel ImagePPM::GetPixel(int row, int col) const { return pixels_[row][col]; }

int ImagePPM::GetMaxColorValue() const { return max_color_value_; }

void ImagePPM::RemoveHor(int*& to_remove) {
  int new_height = height_ - 1;
  auto** new_pix = new Pixel*[new_height];
  for (int row = 0; row < new_height; row++) {
    new_pix[row] = new Pixel[width_];
  }
  for (int col = 0; col < width_; col++) {
    int image_row = 0;
    for (int row = 0; row < new_height; row++) {
      if (row == to_remove[col]) {
        image_row++;
      }
      new_pix[row][col] = GetPixel(image_row, col);
      image_row++;
    }
  }
  for (int i = 0; i < height_; i++) {
    delete[] pixels_[i];
  }
  delete[] pixels_;
  height_--;
  pixels_ = new_pix;
}

void ImagePPM::RemoveVer(int*& to_remove) {
  int new_width = width_ - 1;
  auto** new_pix = new Pixel*[height_];
  for (int row = 0; row < height_; row++) {
    new_pix[row] = new Pixel[new_width];
  }
  for (int row = 0; row < height_; row++) {
    int image_col = 0;
    for (int col = 0; col < new_width; col++) {
      if (to_remove[row] == col) {
        image_col++;
      }
      new_pix[row][col] = GetPixel(row, image_col);
      image_col++;
    }
  }
  for (int i = 0; i < height_; i++) {
    delete[] pixels_[i];
  }
  delete[] pixels_;
  width_--;
  pixels_ = new_pix;
}

// given functions below, DO NOT MODIFY

ImagePPM::ImagePPM(const std::string& path) {
  std::ifstream input_file(path);
  input_file >> *this;
  input_file.close();
}

ImagePPM::ImagePPM(const ImagePPM& source) { *this = source; }

ImagePPM& ImagePPM::operator=(const ImagePPM& source) {
  if (this == &source) {
    return *this;
  }

  Clear();

  height_ = source.height_;
  width_ = source.width_;
  max_color_value_ = source.max_color_value_;

  pixels_ = new Pixel*[height_];
  for (int row = 0; row < height_; row++) {
    pixels_[row] = new Pixel[width_];

    for (int col = 0; col < width_; col++) {
      pixels_[row][col] = source.pixels_[row][col];
    }
  }

  return *this;
}

ImagePPM::~ImagePPM() { Clear(); }

void ImagePPM::Clear() {
  for (int i = 0; i < height_; i++) {
    delete[] pixels_[i];
  }

  delete[] pixels_;

  height_ = 0;
  width_ = 0;
  pixels_ = nullptr;
}

std::istream& operator>>(std::istream& is, ImagePPM& image) {
  image.Clear();
  std::string line;
  // ignore magic number line
  getline(is, line);
  // check to see if there's a comment line
  getline(is, line);
  if (line[0] == '#') {
    getline(is, line);
  }
  // parse width and height
  int space = line.find_first_of(' ');
  image.width_ = std::stoi(line.substr(0, space));
  image.height_ = std::stoi(line.substr(space + 1));
  // get max color value
  getline(is, line);
  image.max_color_value_ = std::stoi(line);
  // init and fill in Pixels array
  image.pixels_ = new Pixel*[image.height_];
  for (int i = 0; i < image.height_; i++) {
    image.pixels_[i] = new Pixel[image.width_];
  }
  for (int row = 0; row < image.height_; row++) {
    for (int col = 0; col < image.width_; col++) {
      getline(is, line);
      int red = std::stoi(line);
      getline(is, line);
      int green = std::stoi(line);
      getline(is, line);
      int blue = std::stoi(line);

      Pixel p(red, green, blue);
      image.pixels_[row][col] = p;
    }
  }
  return is;
}

std::ostream& operator<<(std::ostream& os, const ImagePPM& image) {
  os << "P3" << '\n'
     << image.width_ << " " << image.height_ << '\n'
     << image.max_color_value_ << '\n';
  for (int row = 0; row < image.height_; row++) {
    for (int col = 0; col < image.width_; col++) {
      os << image.pixels_[row][col].GetRed() << '\n'
         << image.pixels_[row][col].GetGreen() << '\n'
         << image.pixels_[row][col].GetBlue() << '\n';
    }
  }
  return os;
}
