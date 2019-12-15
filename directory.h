#ifndef DIRECTORY_H
#define DIRECTORY_H
#include <vector>
#include <iostream>
#include <algorithm>
#include "file.h"
using namespace std;

enum ObjectCreationResult{Success, DirectoryExists, FileExists};

class Directory
{
private:
    vector<Directory*> directories;
    vector<File*> files;
    string name;

    int canCreate(const string& name) const;
public:
    Directory(const string& name):
        name(name){}
    ~Directory(){
        for(auto& x: directories){
            delete x;
        }
        for(auto& x: files){
            delete x;
        }
    }
    string getName() const {return name + "/";}
    string getNameRaw() const {return name;}

    int mkdir(string dirName);
    int mkdir(Directory* dir);

    int touch(string fileName, string content);
    int touch(File* file);

    bool isEmpty() const;

    std::string getJsonContent(std::string);

    void deleteDirectory(const string& d);
    void deleteFile(const string& fileName);
    void rm();
    void treelist(int indent) const;
    void ls() const;

    bool containsFile(const string& fileName) const;
    bool containsDirectory(const string& dirName) const;

    Directory* getDirectory(const string& dirname) const;
    File* getFile(const string& fileName) const;

    void eraseCharFromName(char character){
        for(auto& x: files){
            x->eraseCharFromName(character);
        }

        for(auto& x: directories){
            x->eraseCharFromName(character);
        }

        name.erase(std::remove(name.begin(), name.end(), character), name.end());
    }
};

#endif // DIRECTORY_H
