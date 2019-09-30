#ifndef DIRECTORY_H
#define DIRECTORY_H
#include <vector>
#include <iostream>
#include "file.h"
using namespace std;

class Directory
{
private:
    vector<Directory*> directories;
    vector<File*> files;
    string name;
public:
    Directory(string name):
        name(name){}
    string getName() const {return name + "/";}
    string getNameRaw() const {return name;}
    bool mkdir(Directory* d);
    bool touch(File* f);
    bool operator ==(Directory d){
        return d.name == this->name;
    }
    void deleteDirectory(string dir);
    void deleteFile(string fileName);
    bool rm();
    void treelist(int indent) const;
    void ls() const;
    Directory* contains(string dirname) const;
    File* containsFile(string fileName) const;
};

#endif // DIRECTORY_H
