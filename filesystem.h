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
    Directory* root;
    string* filename;

    vector<Directory*> currentLocation;

    void printUserandLocation();
        
    /**
    * 
    */
    
    void runCommand(string line);
        
    /**
    * 
    */
    
    void mkdir(stringstream& ss);
        
    /**
    * @brief The mkdir() shall create a new directory.
    */
    
    void touch(stringstream& ss);
        
    /**
    * @brief List of directories/files.
    */
    
    void ls(stringstream& ss);
        
    /**
    * @brief Command that lists directory contents of files and other directories.
    */
    

    void echo(stringstream& ss);
            
    /**
    * @brief Moves the elements from one folder to another.
    */
    
    void trimNames(char character);

    std::vector<Directory *> parseRelativePath(string arg);
    Directory* getRelativeDir(string path);

    void cd(stringstream& ss);
            
    /**
    * @brief Moves into a folder in the tree.
    */
    
    void cdRelativePath(string arg);
            
    /**
    * @brief Relative path is defined as path related tothe present working directory.
    */
    
    void rm(stringstream& ss);
            
    /**
    * @brief Command to delete a file or directory.
    */
    
    void deleteDirFor(string name, Directory *location);
            
    /**
    * 
    */
    

    void startup(string* filename);
            
    /**
    * 
    */
    
    void exit(string* filename);
            
    /**
    * @brief To exit the sehll where it is currently running.
    */
    
public:
    Filesystem(string* filename){
        startup(filename);
        this->filename = filename;
    }
    ~Filesystem(){
        this->exit(this->filename);
        delete root;
    }
    void run();
};

#endif // FILESYSTEM_H
