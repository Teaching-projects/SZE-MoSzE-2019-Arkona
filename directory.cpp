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

bool Directory::mkdir(Directory *d)
{
    
    directories.push_back(d);
    return true;
}

bool Directory::touch(File *f)
{
    for(auto& file: files){
        if( *file == *f) return false;
    }

    files.push_back(f);
    return true;
}

Directory* Directory::contains(string dirname) const
{
    for(auto& dir: directories){
        if( dir-> getNameRaw() == dirname)
            return dir;
    }

    return nullptr;
}
