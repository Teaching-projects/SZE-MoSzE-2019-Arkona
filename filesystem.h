#ifndef FILESYSTEM_H
#define FILESYSTEM_H
#include "directory.h"
#include <sstream>

class Filesystem
{
private:
    const string user = "User@User:";
    Directory* root = new Directory("~");
    Directory* currentDirectory;

    vector<Directory*> currentLocation;

    vector<Directory*> directories;
    vector<File*> files;
    void printUserandLocation();
    void runCommand(string line);
    void mkdir(stringstream& ss);
    void touch(stringstream& ss);

    void cd(stringstream& ss);
    void cdRoot();
    void cdParent();
    bool cdToDirectory(Directory* newLocation);
    
    void rm(stringstream& ss);
public:
    Filesystem(){
        currentDirectory = root;
        currentLocation.push_back(currentDirectory);
    }

    void run();
};

#endif // FILESYSTEM_H
