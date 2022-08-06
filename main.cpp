#include <fstream>
#include <iostream>

#include <functional>
#include <iterator>
#include <vector>
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

  normalizedWord.erase(
      std::remove_if(
          normalizedWord.begin(), normalizedWord.end(),
          [](char c) { return c == ',' || c == '.' || c == '!' || c == '?'; }),
      normalizedWord.end());

  normalizedWord = toUpperCase(normalizedWord);
  return normalizedWord;
}

void a(string directory, string selectedWord) {
  print(directory);

  vector<string> files = getFilesFromPath(directory);

  AVLTree *tree = new AVLTree();

  function<void(string, unsigned long long, unsigned int)> callback =
      [&tree](string line, unsigned long long lineNumber, unsigned int fileIndex) {
        std::vector<std::string> lineWordsArray;

        split(line, lineWordsArray, ' ');
        for (auto &w : lineWordsArray) {
          string formattedWord = normalizeWord(w);
          if (formattedWord == "")
            continue;

          WordNode *node = new WordNode();

          FileNode *fileNode = new FileNode();

          fileNode->count = 1;
          fileNode->lines.insert(lineNumber);

          node->word = formattedWord;
          node->count = 1;

          node->files[fileIndex]=*fileNode;

          tree->insert(node);
        }
      };

  for (unsigned int i = 0; i < files.size(); i++) {
    string filePath = files[i];
    string fullFilePath = directory + filePath;

    readFile(fullFilePath, callback, i);
  }

  tree->display(&files);
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
