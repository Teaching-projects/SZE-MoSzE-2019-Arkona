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


    /**
     * @brief Check current state and returns ObjectCreationResult
     */

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

    /**
    * @brief The mkdir() shall create a new directory.
    */

    int mkdir(string dirName);
    int mkdir(Directory* dir);

    /**
    * @brief touch creates file in directory
    */

    int touch(string fileName, string content);
    int touch(File* file);
    

    bool isEmpty() const;

    /**
    * @brief returns content in json format.
    */

    std::string getJsonContent(std::string);

    /**
     * @brief removes object but doesnt delete it
     */

    void removeReference(string name);

    /**
    * @brief Command to delete a directory.
    */

    void deleteDirectory(const string& d);
    
    /**
    * @brief Command to delete a file.
    */
    
    void deleteFile(const string& fileName);

    /**
    * @brief Command to delete a file or directory.
    */

    void rm();

    /**
    * @brief List contents of directories and files in a treelike format.
    */
    
    void treelist(int indent) const;
        
    /**
    * @brief Command that lists directory contents of files and other directories.
    */
    
    void ls() const;
        
    /**
    * @brief Checcks a directory if it contains files.
    */
    
    bool containsFile(const string& fileName) const;
        
    /**
    * @brief Checks a directory if it contains directories.
    */
    
    bool containsDirectory(const string& dirName) const;
        
    /**
     *  @brief returns Directory with given name or null
     */

    Directory* getDirectory(const string& dirname) const;

    /**
     *  @brief returns File with given name or null
     */

    File* getFile(const string& fileName) const;

    /**
    * @brief Deletes all characters in names recursively
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
};

#endif // DIRECTORY_H
