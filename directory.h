#ifndef DIRECTORY_H
#define DIRECTORY_H
#include <vector>
#include <iostream>
#include "file.h"
using namespace std;

enum ObjectCreationResult{Success, DirectoryExists, FileExists};

class Directory
{
private:
    vector<Directory*> directories;
    vector<File*> files;
    string name;

    int canCreate(string name) const;
public:
    Directory(string name):
        name(name){}
    string getName() const {return name + "/";}
    string getNameRaw() const {return name;}
    int mkdir(string dirName);
    int touch(string fileName, string content);

    bool isEmpty() const;

    void deleteDirectory(string d);
    void deleteFile(string fileName);
    void rm();
    void treelist(int indent) const;
    void ls() const;

    bool containsFile(string fileName) const;
    bool containsDirectory(string dirName) const;

    Directory* getDirectory(string dirname) const;
    File* getFile(string fileName) const;
};

#endif // DIRECTORY_H
