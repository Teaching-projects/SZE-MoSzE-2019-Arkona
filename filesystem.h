#ifndef FILESYSTEM_H
#define FILESYSTEM_H
#include "directory.h"
#include <sstream>
#include <string>
#include "filesystemserializer.h"

class Filesystem
{
private:
    const string user = "User@User:";
    Directory* root = new Directory("~");
    string* filename;

    vector<Directory*> currentLocation;

    vector<Directory*> directories;
    vector<File*> files;
    void printUserandLocation();
    void runCommand(string line);
    void mkdir(stringstream& ss);
    void touch(stringstream& ss);

    void ls(stringstream& ss);

    void trimNames(char character);

    std::vector<Directory *> parseRelativePath(string arg);
    Directory* getRelativeDir(string path);

    void cd(stringstream& ss);
    void cdRelativePath(string arg);

    void rm(stringstream& ss);
    void deleteDirFor(string name, Directory *location);

    void startup(string* filename);
    void exit(string* filename);
public:
    Filesystem(string* filename){
        currentLocation.push_back(root);
        this->filename = filename;
        startup(filename);
    }
    ~Filesystem(){
        this->exit(this->filename);
    }
    void run();
};

#endif // FILESYSTEM_H
