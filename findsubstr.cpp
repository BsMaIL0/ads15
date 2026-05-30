#include <fstream>
#include <iostream>

class BoyerMooreHorspool {
 private:
  static const int ALPHABET_SIZE = 256;

  char* pattern;
  int patternLen;
  int badChar[ALPHABET_SIZE];

  static int getStringLength(const char* str) {
    int len = 0;
    while (str[len] != '\0') {
      len++;
    }
    return len;
  }

  void initBadChar() {
    for (int i = 0; i < ALPHABET_SIZE; i++) {
      badChar[i] = patternLen;
    }

    for (int i = 0; i < patternLen - 1; i++) {
      badChar[static_cast<unsigned char>(pattern[i])] = patternLen - 1 - i;
    }
  }

 public:
  BoyerMooreHorspool(const char* pat) {
    patternLen = getStringLength(pat);
    pattern = new char[patternLen + 1];
    for (int i = 0; i <= patternLen; i++) {
      pattern[i] = pat[i];
    }

    initBadChar();
  }

  ~BoyerMooreHorspool() { delete[] pattern; }

  int findAllOccurrences(const char* text, int textLen) {
    if (patternLen > textLen || patternLen <= 0) {
      return 0;
    }

    int count = 0;
    int i = 0;

    while (i <= textLen - patternLen) {
      int j = patternLen - 1;

      while (j >= 0 && pattern[j] == text[i + j]) {
        j--;
      }

      if (j < 0) {
        count++;
        i++;
      } else {
        int shift =
            badChar[static_cast<unsigned char>(text[i + patternLen - 1])];
        i += shift;
      }
    }

    return count;
  }
};

int main(int argc, char* argv[]) {
  if (argc != 3) {
    std::cerr << "Wrong arguments!\n";
    return 1;
  }

  const char* pattern = argv[1];
  const char* filename = argv[2];

  if (pattern[0] == '\0') {
    std::cout << "0\n";
    return 0;
  }

  std::fstream file(filename, std::ios::binary | std::ios::ate | std::ios::in);
  if (!file) {
    std::cout << "0\n";
    return 0;
  }

  auto size = file.tellg();
  if (size <= 0) {
    std::cout << "0\n";
    return 0;
  }

  file.seekg(0, std::ios::beg);

  char* buffer = new char[size];
  if (!file.read(buffer, size)) {
    delete[] buffer;
    std::cout << "0\n";
    return 0;
  }

  BoyerMooreHorspool bmh(pattern);
  int totalCount = bmh.findAllOccurrences(buffer, static_cast<int>(size));

  std::cout << totalCount << "\n";

  delete[] buffer;
  return 0;
}
