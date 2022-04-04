#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP
#include <iostream>
#include <string>

std::string Generator(std::string input);
bool Consonant(char letter, char nextLetter, std::string& output);
bool Vowels(char letter, std::string& output);
bool VowelsGroups(char letter, char nextLetter, std::string& output);

#endif