#include <iostream>
#include <fstream>
#include <list>
#include <set>
#include <string>

using std::list; 
using std::set;
using std::string;

class FileNode {
  unsigned int fileIndex;
  unsigned long long count;
  set<unsigned long long> lines;
};

class WordNode {
  string word;
  unsigned long long count;
  list<FileNode> files;
};


int main() { std::cout << "Hello World!\n"; }