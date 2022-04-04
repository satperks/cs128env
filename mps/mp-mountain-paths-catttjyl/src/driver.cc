#include <cerrno>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "elevation_dataset.hpp"
#include "grayscale_image.hpp"
#include "path_image.hpp"

int main() {
  ElevationDataset dataset(
      "./example-data/ex_input_data/map-input-w51-h55.dat", 51, 55);
  GrayscaleImage image(dataset);
  PathImage path(image, dataset);
  image.ToPpm("grayscale-w51-h55-3.ppm");
  path.ToPpm("paths-w51-h557-3.ppm");
  // std::cout << "max: " << dataset.MaxEle() << std::endl;
  // std::cout << "min: " << dataset.MinEle() << std::endl;

  // std::vector<std::vector<int>> data_matrix = dataset.GetData();

  // for (size_t i = 0; i < data_matrix.size(); i++) {
  //   std::cout << "row" << i << std::endl;
  //   for (size_t j = 0; j < data_matrix.at(i).size(); j++) {
  //     std::cout << data_matrix.at(i).at(j) << " ";
  //   }
  //   std::cout << "\n";
  // }

  return 0;
}