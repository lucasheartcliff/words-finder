#include <iostream>
#include <iterator>
#include <list>
#include <set>
#include <string>

class FileNode {
  unsigned int fileIndex;
  unsigned int count;
  std::set<unsigned int> lines;
};

class WordNode {
  std::string word;
  unsigned long long count;
  std::list<FileNode> files;
};

int main() { std::cout << "Hello World!\n"; }