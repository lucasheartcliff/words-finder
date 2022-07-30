#include <dirent.h>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <list>
#include <sys/types.h>
#include <vector>

using namespace std;

void readFile(string path, void (*callback)(string)) {
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
