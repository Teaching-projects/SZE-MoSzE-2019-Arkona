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
public:
    Directory(string name):
        name(name){}
    string getName() const {return name + "/";}
    string getNameRaw() const {return name;}
    int mkdir(Directory* d);
    int touch(File* f);

    bool operator ==(File* f){
        return f->getName() == this->name;
    }
    bool operator ==(File f){
        return f.getName() == this->name;
    }
    bool operator ==(Directory* d){
        return d->name == this->name;
    }
    bool operator ==(Directory d){
        return d.name == this->name;
    }

    void deleteDirectory(string d);
    void deleteFile(string fileName);
    void rm();
    void treelist(int indent) const;
    void ls() const;

    Directory* getDirectory(string dirname) const;
    File* getFile(string fileName) const;
};

#endif // DIRECTORY_H
