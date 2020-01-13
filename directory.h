#ifndef DIRECTORY_H
#define DIRECTORY_H
#include <vector>
#include <iostream>
#include <algorithm>
#include "file.h"
using namespace std;

enum ObjectCreationResult{Success, DirectoryExists, FileExists};

/**
 *
 * 	@brief Class with name that stores other Directories and Files
 *
 */

class Directory
{
private:
    vector<Directory*> directories;
    vector<File*> files;
    string name;

    int canCreate(const string& name) const;

    /**
     * @brief Check current state and returns ObjectCreationResult
     */

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
    
    /**
    * @brief The mkdir() shall create a new directory.
    */

    int touch(string fileName, string content);
    int touch(File* file);
    
    /**
    * @brief List of directories/files.
    */

    bool isEmpty() const;

    std::string getJsonContent(std::string);

    /**
    * @brief returns content in json format.
    */

    void deleteDirectory(const string& d);
    
    /**
    * @brief Command to delete a directory.
    */
    
    void deleteFile(const string& fileName);
        
    /**
    * @brief Command to delete a file.
    */
    
    void rm();
        
    /**
    * @brief Command to delete a file or directory.
    */
    
    void treelist(int indent) const;
        
    /**
    * @brief List contents of directories and files in a treelike format.
    */
    
    void ls() const;
        
    /**
    * @brief Command that lists directory contents of files and other directories.
    */
    
    bool containsFile(const string& fileName) const;
        
    /**
    * @brief Checcks a directory if it contains files.
    */
    
    bool containsDirectory(const string& dirName) const;
        
    /**
    * @brief Checks a directory if it contains directories.
    */

    Directory* getDirectory(const string& dirname) const;
    File* getFile(const string& fileName) const;

    /**
     *  @brief returns (File/Directory) or null
     */

    void eraseCharFromName(char character){
        for(auto& x: files){
            x->eraseCharFromName(character);
        }

        for(auto& x: directories){
            x->eraseCharFromName(character);
        }

        name.erase(std::remove(name.begin(), name.end(), character), name.end());
    }

    /**
    * @brief Deletes all characters in names recursively
    */

};

#endif // DIRECTORY_H
