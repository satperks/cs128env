#include <fstream>
#include <iostream>

#include "image_ppm.hpp"
#include "seam_carver.hpp"

void PrintUsage(const std::string& command) {
  std::cout << "Usage: " << command << " INPUT_FILE [options] -o OUTPUT_FILE\n"
            << "Options:\n"
            << "\t-h times\tcarve times horizontal seams\n"
            << "\t-v times\tcarve times vertical seams\n";
}

int main(int argc, char* argv[]) {
  std::string out_option = "-o";
  if (argc < 4 || out_option != argv[argc - 2]) {
    PrintUsage(argv[0]);
    return 1;
  }

  std::ifstream infile(argv[1]);
  if (!infile.good()) {
    std::cout << "file '" << argv[1] << "' not found" << std::endl;
    return 1;
  }

  /* UNCOMMENT COMMENTED CODE BELOW AS YOU IMPLEMENT */

  ImagePPM image;
  infile >> image;
  infile.close();
  SeamCarver carver(image);
  // std::cout << "energy: " << std::endl;
  // for (int row = 0; row < carver.GetHeight(); row++) {
  //   for (int col = 0; col < carver.GetWidth(); col++) {
  //     std::cout << carver.GetEnergy(row, col) << " ";
  //   }
  //   std::cout << '\n';
  // }
  // std::cout << '\n';
  // int* hor_min_path = carver.GetHorizontalSeam();
  // int* ver_min_path = carver.GetVerticalSeam();
  // std::cout << "horrizontal path: \n";
  // for (int i = 0; i < carver.GetWidth(); i++) {
  //   std::cout << hor_min_path[i] << " ";
  // }
  // std::cout << '\n';
  // std::cout << "vertical path: \n";
  // for (int i = 0; i < carver.GetHeight(); i++) {
  //   std::cout << ver_min_path[i] << " ";
  // }
  // std::cout << '\n';
  for (int i = 2; i < argc - 2; i += 2) {
    std::string times_string = argv[i + 1];
    int times = 0;
    try {
      times = std::stoi(times_string);
    } catch (const std::exception& e) {
      std::cout << "Malformed option" << std::endl;
      PrintUsage(argv[0]);
      return 1;
    }

    std::string option = argv[i];
    if (option == "-h") {
      for (int t = 0; t < times; t++) {
        carver.RemoveHorizontalSeam();
        // std::cout << carver.GetHeight() << " " << carver.GetWidth()
        //           << std::endl;
      }
    } else if (option == "-v") {
      for (int t = 0; t < times; t++) {
        carver.RemoveVerticalSeam();
        // std::cout << carver.GetHeight() << " " << carver.GetWidth()
        //           << std::endl;
      }
    } else {
      std::cout << argv[i] << " not an option" << std::endl;
      PrintUsage(argv[0]);
      return 1;
    }
  }
  // std::cout << carver.GetHeight() << std::endl;
  // std::cout << carver.GetWidth() << std::endl;
  std::ofstream outfile(argv[argc - 1]);
  outfile << carver.GetImage();
  outfile.close();
}
