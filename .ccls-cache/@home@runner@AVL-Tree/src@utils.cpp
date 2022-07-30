#pragma once
#include <dirent.h>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <list>
#include <sys/types.h>
#include <vector>
#include <algorithm> 
#include <functional> 
#include <cctype>
#include <locale>
#include<bits/stdc++.h>

using namespace std;

void readFile(string path, function<void (string)> callback) {
  ifstream file(path);

  string text;

  while (getline(file, text)) {
    callback(text);
  }

  file.close();
}

list<string> getFilesFromPath(string path) {
  struct dirent *entry;
  list<string> files;

  DIR *directory = opendir(path.c_str());
  if (directory == NULL)
    return files;

  while ((entry = readdir(directory)) != NULL) {
    files.push_front(entry->d_name);
  }
  return files;
  }

// trim from start (in place)
static inline void ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(),
            std::not1(std::ptr_fun<int, int>(std::isspace))));
}

// trim from end (in place)
static inline void rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(),
            std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
}

// trim from both ends (in place)
static inline void trim(std::string &s) {
    ltrim(s);
    rtrim(s);
}

// trim from start (copying)
static inline std::string ltrim_copy(std::string s) {
    ltrim(s);
    return s;
}

// trim from end (copying)
static inline std::string rtrim_copy(std::string s) {
    rtrim(s);
    return s;
}
void toUpperCase(string text){
  transform(text.begin(), text.end(), text.begin(), ::toupper);
}