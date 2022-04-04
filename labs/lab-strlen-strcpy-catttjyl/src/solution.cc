
unsigned int StrLen(const char* c_str) {
  unsigned int index = 0;
  while (c_str[index] != '\0') {
    index++;
  }
  return index;
}

void StrCpy(char*& to, const char* from) {
  if (from == nullptr) {
    return;
  }
  unsigned int from_len = StrLen(from);
  char* tmp = new char[from_len + 1];
  for (unsigned int i = 0; i < from_len + 1; i++) {
    tmp[i] = from[i];
  }
  delete[] to;
  to = tmp;
}
