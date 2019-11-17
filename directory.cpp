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

int Directory::mkdir(Directory *d)
{
    for (auto& dir : directories) {
        if (*dir == *d){
            return ObjectCreationResult::DirectoryExists;
        }
    }

    for(auto& file: files){
        if (*d == *file){
            return ObjectCreationResult::FileExists;
        }
    }

    directories.push_back(d);
    return ObjectCreationResult::Success;
}

int Directory::touch(File *f)
{
    for(auto& file: files){
        if(*file == *f){
            return ObjectCreationResult::FileExists;
        }
    }
    for(auto& dir: directories){
        if(*dir == *f){
            return ObjectCreationResult::DirectoryExists;
        }
    }

    files.push_back(f);
    return ObjectCreationResult::Success;
}

void Directory::deleteDirectory(string d)
{
    for(auto it = directories.begin(); it != directories.end();){
        if( **it == Directory(d)){
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
        if( *dir == Directory(dirname))
            return dir;
    }
    return nullptr;
}

File* Directory::getFile(string fileName) const
{
    for(auto& file: files){
        if( *file == File(fileName))
            return file;
    }

    return nullptr;
}
