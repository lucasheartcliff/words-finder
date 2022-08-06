#pragma once
#include <algorithm>
#include <bits/stdc++.h>
#include <cctype>
#include <dirent.h>
#include <filesystem>
#include <fstream>
#include <functional>
#include <iostream>
#include <locale>
#include <sys/types.h>
#include <vector>

using namespace std;

void print(string text) { std::cout << text + "\n"; }

void split(const std::string &txt, std::vector<std::string> &strs, char ch) {
  size_t pos = txt.find(ch);
  size_t initialPos = 0;
  strs.clear();

  // Decompose statement
  while (pos != std::string::npos) {
    strs.push_back(txt.substr(initialPos, pos - initialPos));
    initialPos = pos + 1;

    pos = txt.find(ch, initialPos);
  }

  // Add the last one
  strs.push_back(
      txt.substr(initialPos, std::min(pos, txt.size()) - initialPos + 1));
}

void readFile(string path, function<void(string, unsigned long long, unsigned int)> callback, unsigned int fileIndex) {
  ifstream file(path);

  string text;

  unsigned long lineNumber = 1;
  while (getline(file, text)) {
    callback(text, lineNumber, fileIndex);
    lineNumber++;
  }

  file.close();
}

vector<string> getFilesFromPath(string path) {
  struct dirent *entry;
  vector<string> files;

  DIR *directory = opendir(path.c_str());
  if (directory == NULL)
    return files;

  while ((entry = readdir(directory)) != NULL) {
    files.push_back(entry->d_name);
  }
  return files;
}

// trim from start (in place)
string ltrim(std::string s) {
  s.erase(s.begin(),
          std::find_if(s.begin(), s.end(),
                       std::not1(std::ptr_fun<int, int>(std::isspace))));
  return s;
}

// trim from end (in place)
string rtrim(std::string s) {
  s.erase(std::find_if(s.rbegin(), s.rend(),
                       std::not1(std::ptr_fun<int, int>(std::isspace)))
              .base(),
          s.end());

  return s;
}

// trim from both ends (in place)
string trim(std::string s) {
  s = ltrim(s);
  s = rtrim(s);

  return s;
}

string toUpperCase(string text) {
  std::transform(text.begin(), text.end(), text.begin(), ::toupper);

  return text;
}
