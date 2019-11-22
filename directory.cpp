#include "directory.h"
#include <iomanip>

void Directory::ls() const
{
    for(auto& x: files){
        cout << x-> getName() << "\n";
    }
    for(auto& x: directories){
        cout << x-> getName() << "\n";
    }
}

void Directory::rm()
{
    for(auto& file: files){
        delete file;
    }
    files = std::vector<File*>();
    for(auto& dir: directories){
        dir->rm();
        delete dir;
    }
    directories = std::vector<Directory*>();
}

void Directory::treelist(int indent) const
{
    for(auto& x: files){
        cout << setw(indent + 4) << x-> getName() << "\n";
    }

    for(auto& x: directories){
        cout << setw(indent + 4) << x-> getName() << "\n";
        x->treelist(indent + 1);
    }
}

int Directory::canCreate(string name) const
{
    for (auto& dir : directories) {
        if (dir->getNameRaw() == name){
            return ObjectCreationResult::DirectoryExists;
        }
    }

    for(auto& file: files){
        if (file->getName() == name){
            return ObjectCreationResult::FileExists;
        }
    }

    return ObjectCreationResult::Success;
}

int Directory::mkdir(string dirName)
{
    int result = this->canCreate(dirName);

    if(result == Success){
        directories.push_back(new Directory(dirName));
    }
    return result;
}

int Directory::touch(string fileName, string content)
{
    int result = this->canCreate(fileName);

    if(result == Success){
        files.push_back(new File(fileName,content));
    }
    return result;

}

void Directory::deleteDirectory(string d)
{
    for(auto it = directories.begin(); it != directories.end();){
        if( (*it)->getNameRaw() == d ){
            delete *it;
            directories.erase(it);
        }else{
            it++;
        }
    }
}

void Directory::deleteFile(string fileName)
{
    for(auto it = files.begin(); it != files.end();){
        if( **it == File(fileName)){
            delete *it;
            files.erase(it);
        }else{
            it++;
        }
    }
}

bool Directory::isEmpty() const
{
    return this->files.empty() && this->directories.empty();
}

Directory* Directory::getDirectory(string dirname) const
{
    for(auto& dir: directories){
        if( dir->getNameRaw() == dirname)
            return dir;
    }
    return nullptr;
}

File* Directory::getFile(string fileName) const
{
    for(auto& file: files){
        if( file->getName() == fileName)
            return file;
    }

    return nullptr;
}
