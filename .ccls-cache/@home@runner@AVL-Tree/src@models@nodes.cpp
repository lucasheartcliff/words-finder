#pragma once

#include <vector>
#include <map>
#include <set>
#include <string>

using std::vector;
using std::map;
using std::set;
using std::string;

using namespace std;

template <typename T> class Node {
public:
  T *left;
  T *right;
  int height;
};

class FileNode {
public:
  unsigned long long count;
  set<unsigned long long> lines;

  string linesToString() {
    string linesString = "";
    for (auto &line : lines) {
      string lineString = "" + to_string(line) + "";
      
      if (linesString == "")
        linesString += lineString;
      else
        linesString += ", " + lineString;
    }
    return linesString;
  }

  string toString() { return  "count: " + to_string(count) + ", lines: [" + linesToString() +"]"; }
};

class WordNode : public Node<WordNode> {
public:
  string word;
  unsigned long long count;
  map<unsigned int, FileNode> files;

  string toString(vector<string> *fileNames){
    string wordNodeString = "\n"+word + " : " + "{ count: " + to_string(count) + "}\n";

    for (map<unsigned int, FileNode>::iterator itr = files.begin(); itr != files.end(); ++itr) {
        unsigned int key =  itr->first;
        string fileName = (*fileNames)[key];
      
        FileNode fileNode = itr->second;

        wordNodeString += "   " +fileName + " : {" + fileNode.toString() + "}\n"; 
    }

    return wordNodeString;
  }
};
