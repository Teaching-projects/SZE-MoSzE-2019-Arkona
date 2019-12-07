#ifndef FILE_H
#define FILE_H
#include <string>
#include <algorithm>

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

    string getJsonContent(string current);

    void eraseCharFromName(char character){
        name.erase(std::remove(name.begin(), name.end(), character), name.end());
    }
};

#endif // FILE_H
