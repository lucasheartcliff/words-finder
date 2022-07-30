#include <fstream>
#include <iostream>

#include <list>
#include <string>
#include <functional>
#include <iterator>

#include "./src/utils.cpp"
#include "./src/models/avl-tree.cpp"
#include "./src/models/nodes.cpp"

using std::string;
using std::advance;
using std::function;

void print(string text) { std::cout << text + "\n"; }


void a(string directory, string selectedWord){
  list<string> files = getFilesFromPath(directory);
  AVLTree *tree = new AVLTree();

  function<void (string)> callback = [](string w) { 
  trim(w);
    toUpperCase(w);
    string formattedWord = w;
  };
  

  for(int i = 0; i<files.size();i++){
   list<string>::iterator iter = files.begin();
    advance(iter, i);
    string filePath = *iter;

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
      if (arg == "--dir") {
        directory = argp;
      }

      else if (arg == "--text") {
        selectedWord = argp;
      }
    }
  }
}
