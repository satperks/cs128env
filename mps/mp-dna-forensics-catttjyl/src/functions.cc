#include "functions.hpp"

#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "utilities.hpp"

using namespace std;

bool CheckForMatch(string str, const string& num, string sequence) {
  bool is_match = false;
  int repeat = 0;
  unsigned int tmp = 0;
  unsigned int length = str.size();
  for (size_t s = 0; s < sequence.size() - length + 1; s++) {
    bool check = true;
    for (size_t letter = 0; letter < length; letter++) {
      if (str.at(letter) != sequence.at(s + letter)) {
        check = false;
      }
    }
    if (check) {
      if (repeat == 0) {
        tmp = s;
      } else {
        unsigned int comp = s - tmp;
        if (comp > length) {
          if (repeat == stoi(num)) {
            is_match = true;
          }
          repeat = 0;
        }
      }
      tmp = s;
      repeat++;
      s += (length - 1);
    }
  }
  if (repeat == stoi(num)) {
    is_match = true;
  }
  return is_match;
}

string Name(vector<string> first_line,
            map<string, vector<string>>& database,
            const string& sequence) {
  string result;
  map<string, vector<string>> copy(database);
  for (auto const& [key, value] : database) {
    for (size_t col = 1; col < value.size(); col++) {
      if (!CheckForMatch(first_line.at(col), value.at(col), sequence)) {
        copy.erase(key);
      }
    }
  }
  if (copy.size() != 1) {
    return "No match";
  }
  for (auto const& [key, value] : copy) {
    result = key;
  }
  return result;
}

string SearchForDNAmatch(vector<string> database, string sequence) {
  for (size_t i = 0; i < sequence.size(); i++) {
    if (sequence.at(i) != 'A' && sequence.at(i) != 'T' &&
        sequence.at(i) != 'C' && sequence.at(i) != 'G') {
      return "No match";
    }
  }
  vector<string> first_line = utilities::GetSubstrs(database.at(0), ',');
  map<string, vector<string>> pair;
  for (size_t i = 1; i < database.size(); i++) {
    vector<string> each_line = utilities::GetSubstrs(database.at(i), ',');
    pair.insert(::pair<string, vector<string>>(each_line.at(0), each_line));
  }
  string name = Name(first_line, pair, sequence);
  return name;
}