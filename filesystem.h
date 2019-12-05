#ifndef FILESYSTEM_H
#define FILESYSTEM_H
#include "directory.h"
#include <sstream>
#include <string>

class Filesystem
{
private:
    const string user = "User@User:";
    Directory* root = new Directory("~");

    vector<Directory*> currentLocation;

    vector<Directory*> directories;
    vector<File*> files;
    void printUserandLocation();
    void runCommand(string line);
    void mkdir(stringstream& ss);
    void touch(stringstream& ss);

    void ls(stringstream& ss);

    void echo(stringstream& ss);

    std::vector<Directory *> parseRelativePath(string arg);
    Directory* getRelativeDir(string path);

    void cd(stringstream& ss);
    void cdRelativePath(string arg);

    void rm(stringstream& ss);
    void deleteDirFor(string name, Directory *location);
public:
    Filesystem(){
        currentLocation.push_back(root);
    }

    void run();
};

#endif // FILESYSTEM_H
