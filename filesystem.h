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

    /**
     *
     * @brief stores current path, last element is always current directory
     *
     */

    vector<Directory*> currentLocation;

    /**
    *  @brief print user member and last element of currentDirectory in Unix like format
    */

    void printUserandLocation();
          
    /**
    *  @brief evaluates command line argument
    */

    void runCommand(string line);
    
    /**
    * @brief The mkdir() shall create a new directory.
    */

    void mkdir(stringstream& ss);

    /**
    * @brief List of directories/files.
    */

    void touch(stringstream& ss);
        
    /**
    * @brief Command that lists directory contents of files and other directories.
    */
    
    void ls(stringstream& ss);

    /**
    * @brief print contents of argument to output
    */

    void echo(stringstream& ss);
            
    /**
     * @brief recursiveli removes character from all files and directories
     *  @param used when parsing json
     */
    
    void trimNames(char character);

    /**
     * @brief returns relative path from string
     */

    std::vector<Directory *> parseRelativePath(string arg);

    /**
     * @brief return single directory from string
     */
    Directory* getRelativeDir(string path);

    /**
     * @brief used to navigate between folders
     */
    void cd(stringstream& ss);
            
    /**
    * @brief Relative path is defined as path related tothe present working directory.
    */
    
    void cdRelativePath(string arg);
            
    /**
    * @brief Command to delete a file or directory. Can get -rf command
    *
    */
    
    void rm(stringstream& ss);
            
    /**
    *  @brief attempts to delete Directory with given name at location
    */
    
    void deleteDirFor(string name, Directory *location);
            
    /**
    *
    * @brief loads last state from json or creates a new one
    *
    */

    void startup(string* filename);
            
    /**
    * @brief To exit the shell where it is currently running.
    */
    
    void exit(string* filename);
    
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
