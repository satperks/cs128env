#include "seam_carver.hpp"

#include <iostream>

#include "pixel.hpp"

// given functions below, DO NOT MODIFY

SeamCarver::SeamCarver(const ImagePPM& image): image_(image) {
  height_ = image.GetHeight();
  width_ = image.GetWidth();
  // std::cout << "successfully set seamcarver" << std::endl;
}

void SeamCarver::SetImage(const ImagePPM& image) {
  image_ = image;
  width_ = image.GetWidth();
  height_ = image.GetHeight();
}

// returns the instance's image_
const ImagePPM& SeamCarver::GetImage() const { return image_; }

// returns the image's height
int SeamCarver::GetHeight() const { return height_; }

// returns the image's width
int SeamCarver::GetWidth() const { return width_; }

// helper square func
int SeamCarver::Sq(int x) const { return x * x; }

// helper calclulate engergy func
void SeamCarver::EngergyUL(
    int row, int col, Pixel& left, Pixel& right, Pixel& up, Pixel& bot) const {
  if (col == 0)
    left = image_.GetPixel(row, width_ - 1);
  else
    left = image_.GetPixel(row, col - 1);
  right = image_.GetPixel(row, col + 1);
  up = image_.GetPixel(height_ - 1, col);
  bot = image_.GetPixel(row + 1, col);
}

void SeamCarver::EngergyUR(
    int row, int col, Pixel& left, Pixel& right, Pixel& up, Pixel& bot) const {
  if (row == 0)
    up = image_.GetPixel(height_ - 1, col);
  else
    up = image_.GetPixel(row - 1, col);
  bot = image_.GetPixel(row + 1, col);
  left = image_.GetPixel(row, col - 1);
  right = image_.GetPixel(row, 0);
}

void SeamCarver::EngergyLR(
    int row, int col, Pixel& left, Pixel& right, Pixel& up, Pixel& bot) const {
  if (col == (width_ - 1))
    right = image_.GetPixel(row, 0);
  else
    right = image_.GetPixel(row, col + 1);
  left = image_.GetPixel(row, col - 1);
  up = image_.GetPixel(row - 1, col);
  bot = image_.GetPixel(0, col);
}

void SeamCarver::EngergyLL(
    int row, int col, Pixel& left, Pixel& right, Pixel& up, Pixel& bot) const {
  if (row == (height_ - 1))
    bot = image_.GetPixel(0, col);
  else
    bot = image_.GetPixel(row + 1, col);
  right = image_.GetPixel(row, col + 1);
  left = image_.GetPixel(row, width_ - 1);
  up = image_.GetPixel(row - 1, col);
}

// returns the energy of the pixel at row col in image_
int SeamCarver::GetEnergy(int row, int col) const {
  Pixel left(0, 0, 0);
  Pixel right(0, 0, 0);
  Pixel up(0, 0, 0);
  Pixel bot(0, 0, 0);
  if (row == 0 && col != (width_ - 1)) {
    EngergyUL(row, col, left, right, up, bot);
  } else if (col == (width_ - 1) && row != (height_ - 1)) {
    EngergyUR(row, col, left, right, up, bot);
  } else if (row == (height_ - 1) && col != 0) {
    EngergyLR(row, col, left, right, up, bot);
  } else if (col == 0 && row != 0) {
    EngergyLL(row, col, left, right, up, bot);
  } else {
    left = image_.GetPixel(row, col - 1);
    right = image_.GetPixel(row, col + 1);
    up = image_.GetPixel(row - 1, col);
    bot = image_.GetPixel(row + 1, col);
  }
  int eng =
      Sq(left.GetRed() - right.GetRed()) +
      Sq(left.GetGreen() - right.GetGreen()) +
      Sq(left.GetBlue() - right.GetBlue()) + Sq(up.GetRed() - bot.GetRed()) +
      Sq(up.GetGreen() - bot.GetGreen()) + Sq(up.GetBlue() - bot.GetBlue());
  return eng;
}

// helper comp func
int SeamCarver::Min(int a, int b, int c) const {
  int min = b;
  if (a < min) {
    min = a;
  }
  if (c < min) {
    min = c;
  }
  return min;
}

int SeamCarver::Min(int a, int b) const {
  int min = a;
  if (b < min) {
    min = b;
  }
  return min;
}

// helper 2D array func for HorizontalSearm
void SeamCarver::ArrayHor(int**& values) const {
  for (int row = 0; row < height_; row++) {
    values[row] = new int[width_];
    values[row][width_ - 1] = GetEnergy(row, width_ - 1);
  }
  for (int col = width_ - 2; col >= 0; col--) {
    for (int row = 0; row < height_; row++) {
      int best = 0;
      if (row == 0) {
        best = Min(values[row][col + 1], values[row + 1][col + 1]);
      } else if (row == height_ - 1) {
        best = Min(values[row][col + 1], values[row - 1][col + 1]);
      } else {
        best = Min(values[row - 1][col + 1],
                   values[row][col + 1],
                   values[row + 1][col + 1]);
      }
      values[row][col] = GetEnergy(row, col) + best;
    }
  }
}

// helper height=2 (row = 2) func
void SeamCarver::ArrayHorSpc(int**& values) const {
  for (int row = 0; row < height_; row++) {
    values[row] = new int[width_];
    values[row][width_ - 1] = GetEnergy(row, width_ - 1);
  }
  for (int col = width_ - 2; col >= 0; col--) {
    for (int row = 0; row < 2; row++) {
      int best = 0;
      if (row == 0)
        best = Min(values[row][col + 1], values[row + 1][col + 1]);
      else if (row == 1)
        best = Min(values[row][col + 1], values[row - 1][col + 1]);
      values[row][col] = GetEnergy(row, col) + best;
    }
  }
}

int* SeamCarver::GetHorizontalSeam() const {
  int* to_return = new int[width_];
  int** values = new int*[height_];
  if (height_ == 2)
    ArrayHorSpc(values);
  else
    ArrayHor(values);
  int min = values[0][0];
  int min_row = 0;
  for (int row = 0; row < height_; row++) {
    if (values[row][0] < min) {
      min = values[row][0];
      min_row = row;
    }
  }
  to_return[0] = min_row;
  int current_row = min_row;
  for (int col = 1; col < width_; col++) {
    int tmp_row = current_row;
    int min = values[tmp_row][col];
    if (tmp_row != 0 && values[tmp_row - 1][col] < min) {
      min = values[tmp_row - 1][col];
      current_row = tmp_row - 1;
    }
    if (tmp_row != height_ - 1 && values[tmp_row + 1][col] < min) {
      current_row = tmp_row + 1;
    }
    to_return[col] = current_row;
  }
  std::cout << "horizontal path: \n";
  for (int i = 0; i < width_; i++) {
    std::cout << to_return[i] << " ";
  }
  std::cout << '\n';
  for (int i = 0; i < height_; i++) {
    delete[] values[i];
  }
  delete[] values;
  values = nullptr;
  return to_return;
}

// helper 2D array func for VerticalSearm
void SeamCarver::ArrayVer(int**& values) const {
  for (int row = 0; row < height_; row++) {
    values[row] = new int[width_];
  }
  for (int col = 0; col < width_; col++) {
    values[height_ - 1][col] = GetEnergy(height_ - 1, col);
  }
  for (int row = height_ - 2; row >= 0; row--) {
    for (int col = 0; col < width_; col++) {
      int best = 0;
      if (col == 0) {
        best = Min(values[row + 1][col], values[row + 1][col + 1]);
      } else if (col == width_ - 1) {
        best = Min(values[row + 1][col], values[row + 1][col - 1]);
      } else {
        best = Min(values[row + 1][col - 1],
                   values[row + 1][col],
                   values[row + 1][col + 1]);
      }
      values[row][col] = GetEnergy(row, col) + best;
    }
  }
}

// helper width=2 (col = 2) func
void SeamCarver::ArrayVerSpc(int**& values) const {
  for (int row = 0; row < height_; row++) {
    values[row] = new int[width_];
  }
  for (int col = 0; col < width_; col++) {
    values[height_ - 1][col] = GetEnergy(height_ - 1, col);
  }
  for (int row = height_ - 2; row >= 0; row--) {
    for (int col = 0; col < 2; col++) {
      int best = 0;
      if (col == 0) {
        best = Min(values[row + 1][col], values[row + 1][col + 1]);
      } else if (col == 1) {
        best = Min(values[row + 1][col], values[row + 1][col - 1]);
      }
      values[row][col] = GetEnergy(row, col) + best;
    }
  }
}

// returns the vertical seam of image_ with the least amount of
// energy
int* SeamCarver::GetVerticalSeam() const {
  int* to_return = new int[height_];
  int** values = new int*[height_];
  if (width_ == 2)
    ArrayVerSpc(values);
  else
    ArrayVer(values);
  int min = values[0][0];
  int min_col = 0;
  for (int col = 0; col < width_; col++) {
    if (values[0][col] < min) {
      min = values[0][col];
      min_col = col;
    }
  }
  to_return[0] = min_col;
  int current_col = min_col;
  for (int row = 1; row < height_; row++) {
    int tmp_col = current_col;
    int min = values[row][current_col];
    if (tmp_col != 0 && values[row][tmp_col - 1] < min) {
      min = values[row][tmp_col - 1];
      current_col = tmp_col - 1;
    }
    if (tmp_col != width_ - 1 && values[row][tmp_col + 1] < min) {
      current_col = tmp_col + 1;
    }
    to_return[row] = current_col;
  }
  std::cout << "vertical path: \n";
  for (int i = 0; i < height_; i++) {
    std::cout << to_return[i] << " ";
  }
  std::cout << '\n';
  for (int i = 0; i < height_; i++) {
    delete[] values[i];
  }
  delete[] values;
  values = nullptr;
  return to_return;
}

// removes one horizontal seam in image_. example:
void SeamCarver::RemoveHorizontalSeam() {
  if (height_ == 1) return;
  int* to_remove = GetHorizontalSeam();
  image_.RemoveHor(to_remove);
  SetImage(this->GetImage());
  delete[] to_remove;
  to_remove = nullptr;
}

// removes one vertical seam in image_. example:
void SeamCarver::RemoveVerticalSeam() {
  if (width_ == 1) return;
  int* to_remove = GetVerticalSeam();
  image_.RemoveVer(to_remove);
  SetImage(this->GetImage());
  delete[] to_remove;
  to_remove = nullptr;
}