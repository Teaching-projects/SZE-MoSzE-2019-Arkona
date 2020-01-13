#ifndef FILESYSTEM_H
#define FILESYSTEM_H
#include "directory.h"
#include <sstream>
#include <string>
#include "filesystemserializer.h"

/**
 *
 * 	@brief emulates Linux like file system, stores root Directory, starts with run method
 *
 *
 */

class Filesystem
{
private:
    const string user = "User@User:";
    Directory* root;
    string* filename;

    vector<Directory*> currentLocation;

    /**
     *
     * @brief stores current path, last element is always current directory
     *
     */

    void printUserandLocation();
        
    /**
    *  @brief print user member and last element of currentDirectory in Unix like format
    */
    
    void runCommand(string line);
        
    /**
    *  @brief evaluates command line argument
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
    *  @brief attempts to delete Directory with given name at location
    */
    

    void startup(string* filename);
            
    /**
    *
    * @brief loads last state from json or creates a new one
    *
    */
    
    void exit(string* filename);
            
    /**
    * @brief To exit the shell where it is currently running.
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
