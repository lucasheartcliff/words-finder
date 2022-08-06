#include <fstream>
#include <iostream>

#include <functional>
#include <iterator>
#include <list>
#include <string>

#include <algorithm>

#include "./src/models/avl-tree.cpp"
#include "./src/models/nodes.cpp"
#include "./src/utils.cpp"

using std::advance;
using std::function;
using std::string;

string normalizeWord(string word) {
  string normalizedWord = word;
  normalizedWord = trim(normalizedWord);
  
  normalizedWord.erase(std::remove_if(
      normalizedWord.begin(), normalizedWord.end(),
      [](char c) {
    return c == ',' || c == '.' || c == '!' || c == '?'; }), normalizedWord.end());
  
  normalizedWord = toUpperCase(normalizedWord);
  return normalizedWord;
}

void a(string directory, string selectedWord) {
  print(directory);

  list<string> files = getFilesFromPath(directory);

  AVLTree *tree = new AVLTree();

  print(normalizeWord("         test."));
  function<void(string)> callback = [](string line) {
    std::vector<std::string> lineWordsArray;

    split(line, lineWordsArray, ' ');
    for (auto &w : lineWordsArray) {
      string formattedWord = normalizeWord(w);
      if (formattedWord == "")
        continue;

      // print(formattedWord);
    }
  };

  for (int i = 0; i < files.size(); i++) {
    list<string>::iterator iter = files.begin();
    advance(iter, i);
    string filePath = *iter;
    string fullFilePath = directory + filePath;

    print(fullFilePath);

    readFile(fullFilePath, callback);
  }
}

int main(int argc, char **argv) {
  string directory;
  string selectedWord;

  for (int i = 0; i < argc; ++i) {
    string arg = argv[i];

    if (argc > i + 1) {
      string argp = argv[i + 1];
      if (arg == "-dir") {
        directory = argp;
      }

      else if (arg == "-text") {
        selectedWord = argp;
      }
    }
  }
  a(directory, selectedWord);
}
