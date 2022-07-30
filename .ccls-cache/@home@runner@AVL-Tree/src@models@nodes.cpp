#pragma once


#include <map>
#include <list>
#include <set>
#include <string>

using std::list; 
using std::set;
using std::string;
using std::map;

template<typename T>
class Node {
public:
  T *left;
  T *right;
  int height;
};


class FileNode {
public:
  unsigned long long count;
  set<unsigned long long> lines;
};

class WordNode : public Node<WordNode>{
public:
  string word;
  unsigned long long count;
  map<unsigned int, FileNode> files;
};

