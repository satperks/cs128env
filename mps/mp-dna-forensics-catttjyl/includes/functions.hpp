#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "utilities.hpp"

bool CheckForMatch(std::string str,
                   const std::string& num,
                   std::string sequence);
std::string Name(std::vector<std::string> first_line,
                 std::map<std::string, std::vector<std::string>>& database,
                 const std::string& sequence);
std::string SearchForDNAmatch(std::vector<std::string> database,
                              std::string sequence);

#endif