#ifndef FILE_H
#define FILE_H
#include <string>
#include <algorithm>

using namespace  std;

/**
 *
 * 	@brief Class to strore a file with name and content
 *
 */

class File
{
private:
    string name;
    string content;
public:
    File(string& name,string& content):
        name(name),content(content){}

    bool operator ==(File f){
        return f.name == this->name;
    }
    string getName() const {return name;}

    /**
    *   @brief returns content in json format
    */

    string getJsonContent(const string& current);

    /**
    * @brief deletes characters from name
    */
    
    void eraseCharFromName(char character){
        name.erase(std::remove(name.begin(), name.end(), character), name.end());
    }

    /**
    * @brief deletes characters from name
    */


};

#endif // FILE_H
