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

int Directory::canCreate(const string& name) const
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

int Directory::mkdir(Directory* dir)
{
    int result = this->canCreate(dir->getName());

    if(result == Success){
        directories.push_back(dir);
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

int Directory::touch(File *file)
{
    int result = this->canCreate(file->getName());

    if(result == Success){
        files.push_back(file);
    }
    return result;

}

void Directory::deleteDirectory(const string& d)
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

void Directory::deleteFile(const string& fileName)
{
    for(auto it = files.begin(); it != files.end();){
        if( (**it).getName() == fileName){
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

Directory* Directory::getDirectory(const string& dirname) const
{
    for(auto& dir: directories){
        if( dir->getNameRaw() == dirname)
            return dir;
    }
    return nullptr;
}

File* Directory::getFile(const string& fileName) const
{
    for(auto& file: files){
        if( file->getName() == fileName)
            return file;
    }

    return nullptr;
}

std::string Directory::getJsonContent(std::string current)
{
    current += " { ";

    current += " \"name\" : \"" + this->name + "\" , ";

    current += " \"files\" : [ ";
    for(auto& file: this->files){
        current = file->getJsonContent(current);
        if(this->files.size() > 1 && this->files.back() != file){
            current += " , ";
        }
    }
    current += "], ";

    current += " \"directories\" : [ ";
    for(auto& dir: this->directories){
        current = dir->getJsonContent(current);
        if(this->directories.size() > 1 && this->directories.back() != dir){
            current += " , ";
        }
    }
    current += " ] ";

    current += " } ";
    return current;
}
