#ifndef FILE_H
#define FILE_H
#include <string>

using namespace  std;

class File
{
private:
    string name;
    string content;
public:
    File(string name,string content = ""):
        name(name),content(content){}

    bool operator ==(File f){
        return f.name == this->name;
    }
    string getName() const {return name;}
};

#endif // FILE_H
