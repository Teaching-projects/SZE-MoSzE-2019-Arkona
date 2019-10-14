#include "directory.h"

void Directory::ls() const
{
    for(auto& x: files){
        cout << x-> getName() << "\n";
    }
    for(auto& x: directories){
        cout << x-> getName() << "\n";
    }
}

bool Directory::rm()
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
    return true;
}

void printIndents(int indent)
{
    for(int i=0;i< indent;i++){
        cout << "  ";
    }
}

void Directory::treelist(int indent) const
{
    for(auto& x: files){
        printIndents(indent);
        cout << x-> getName() << "\n";
    }

    for(auto& x: directories){
        printIndents(indent);
        cout << x-> getName() << "\n";
        x->treelist(indent + 1);
    }
}

int Directory::mkdir(Directory *d)
{
    for (auto& dir : directories) {
        if (dir->getNameRaw() == d->getNameRaw()){
            return ObjectCreationResult::DirectoryExists;
        }
    }

    for(auto& file: files){
        if(file->getName() == d->getNameRaw()){
            return ObjectCreationResult::FileExists;
        }
    }

    directories.push_back(d);
    return ObjectCreationResult::Success;
}

int Directory::touch(File *f)
{
    for(auto& file: files){
        if( *file == *f){
            return ObjectCreationResult::FileExists;
        }
    }
    for(auto& dir: directories){
        if(f->getName() == dir->getNameRaw()){
            return ObjectCreationResult::DirectoryExists;
        }
    }

    files.push_back(f);
    return ObjectCreationResult::Success;
}

void Directory::deleteDirectory(string dir)
{
    auto it = directories.begin();
    while(it != directories.end()){
        if((*it)->getNameRaw() == dir){
            delete *it;
            directories.erase(it);
        }
    }
}

void Directory::deleteFile(string fileName)
{
    auto it = files.begin();
    while(it != files.end()){
        if((*it)->getName() == fileName){
            delete *it;
            files.erase(it);
        }
    }
}

Directory* Directory::contains(string dirname) const
{
    for(auto& dir: directories){
        if( dir-> getNameRaw() == dirname)
            return dir;
    }

    return nullptr;
}

File* Directory::containsFile(string fileName) const
{
    for(auto& file: files){
        if( file-> getName() == fileName)
            return file;
    }

    return nullptr;
}
