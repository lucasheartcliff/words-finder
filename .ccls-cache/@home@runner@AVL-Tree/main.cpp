#include <fstream>
#include <iostream>

#include <functional>
#include <iterator>
#include <list>
#include <string>

#include "./src/models/avl-tree.cpp"
#include "./src/models/nodes.cpp"
#include "./src/utils.cpp"

using std::advance;
using std::function;
using std::string;

void a(string directory, string selectedWord) {
  print(directory);

  list<string> files = getFilesFromPath(directory);

  AVLTree *tree = new AVLTree();

  function<void(string)> callback = [](string w) {
    print("word: "+ w);
    trim(w);
    toUpperCase(w);
    string formattedWord = w;

    print(formattedWord);
  };

  for (int i = 0; i < files.size(); i++) {
    list<string>::iterator iter = files.begin();
    advance(iter, i);
    string filePath = *iter;

    print(filePath);

    readFile(filePath, callback);
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
