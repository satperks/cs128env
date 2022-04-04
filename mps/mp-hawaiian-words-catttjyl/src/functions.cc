#include "functions.hpp"

#include <cctype>
#include <iostream>
#include <string>

bool Consonant(unsigned char letter,
               unsigned char nextLetter,
               std::string& tmpt,
               size_t& i) {
  if (letter == 'p' || letter == 'k' || letter == 'h' || letter == 'l' ||
      letter == 'm' || letter == 'n' || letter == 'w' || letter == '\'' ||
      letter == ' ') {
    tmpt = letter;
  } else if (letter == 'a' && nextLetter == '2') {
    tmpt = "ah-w";
    i++;
  } else if (letter == 'i' && nextLetter == 'w') {
    tmpt = "ee-v";
    i++;
  } else if (letter == 'e' && nextLetter == 'w') {
    tmpt = "eh-v";
    i++;
  } else if (letter == 'u' && nextLetter == 'w') {
    tmpt = "oo-w";
    i++;
  } else if (letter == 'o' && nextLetter == 'w') {
    tmpt = "oh-w";
  } else {
    return false;
  }
  return true;
}

bool Vowels(unsigned char letter, unsigned char nextLetter, std::string& tmpt) {
  if (letter == 'a') {
    tmpt = "ah-";
  } else if (letter == 'e') {
    tmpt = "eh-";
  } else if (letter == 'i') {
    tmpt = "ee-";
  } else if (letter == 'o') {
    tmpt = "oh-";
  } else if (letter == 'u') {
    tmpt = "oo-";
  } else {
    return false;
  }
  if (nextLetter == '\'' || nextLetter == ' ') {
    tmpt = tmpt.substr(0, tmpt.length() - 1);
  }
  return true;
}

bool VowelsGroups(unsigned char letter,
                  unsigned char nextLetter,
                  std::string& tmpt) {
  if (letter == 'a') {
    if (nextLetter == 'i' || nextLetter == 'e') {
      tmpt = "eye-";
    } else if (nextLetter == 'o' || nextLetter == 'u') {
      tmpt = "ow-";
    } else {
      return false;
    }
  } else if (letter == 'e' && nextLetter == 'i') {
    tmpt = "ay-";
  } else if (letter == 'e' && nextLetter == 'u') {
    tmpt = "eh-oo";
  } else if (letter == 'i' && nextLetter == 'u') {
    tmpt = "ew-";
  } else if (letter == 'o' && nextLetter == 'i') {
    tmpt = "oy-";
  } else if (letter == 'o' && nextLetter == 'u') {
    tmpt = "ow-";
  } else if (letter == 'u' && nextLetter == 'i') {
    tmpt = "ooey-";
  } else {
    return false;
  }
  return true;
}

std::string Generator(std::string input) {
  std::string output;
  std::string tmpt;
  unsigned char next = ' ';
  size_t i = 0;
  for (i = 0; i < input.size(); i++) {
    unsigned char current = input.at(i);
    current = std::tolower(current);
    if (i != input.size() - 1) {
      next = std::tolower(input.at(i + 1));
      if (VowelsGroups(current, next, tmpt)) {
        output += tmpt;
        i++;
      } else if (Consonant(current, next, tmpt, i) ||
                 Vowels(current, next, tmpt)) {
        output += tmpt;
      } else {
        return input +
               "contains a character not a part of the Hawaiian language.";
      }
    } else if (Vowels(current, next, tmpt)) {
      output += tmpt;
    } else {
      return input +
             "contains a character not a part of the Hawaiian language.";
    }
  }
  if (output.at(output.length() - 1) == '-') {
    return output.substr(0, output.length() - 1);
  }
  return output;
}