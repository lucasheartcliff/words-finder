#pragma once

#include <list>
#include <set>
#include <string>

using std::list; 
using std::set;
using std::string;

class Node {
public:
  Node *left;
  Node *right;
  unsigned int height;
};


class FileNode {
public:
  unsigned int fileIndex;
  unsigned long long count;
  set<unsigned long long> lines;
};

class WordNode : Node{
public:
  string word;
  unsigned long long count;
  list<FileNode> files;
};

