#include "filesystemserializer.h"
#include "file.h"
#include <sstream>

FileSystemSerializer::FileSystemSerializer()
{

}

std::string FileSystemSerializer::encode(Directory* root)
{
    std::string json = "";

    json = root->getJsonContent(json);

    return json;
}

void skipWords(int count, stringstream& ss)
{
    string bin;
    for(int i=0;i<count;i++){
        ss >> bin;
    }
}

Directory* FileSystemSerializer::decode(std::string json)
{

    if (json.empty()){
        return nullptr;
    }

    vector<Directory*> path;
    vector<int> toAdd;

    const int FILE = 1;
    const int DIR = 0;


    std::stringstream ss(json);
    string element;

    skipWords(4,ss);
    Directory* root = new Directory(element);
    path.push_back(root);

    while (ss >> element){

        if(element == "\"files\""){
            toAdd.push_back(FILE);
        }

        if (element == "\"directories\""){
            toAdd.push_back(DIR);
        }

        if (element == "]" || element == "],"){
            if(toAdd.back() == DIR){
                path.pop_back();
            }
            toAdd.pop_back();
        }

        if (element == "{"){
            if(toAdd.back() == DIR){
                skipWords(2,ss);
                string name;
                ss >> name;
                Directory* d = new Directory(name);
                path.back()->mkdir(d);
                path.push_back(d);
            }

            if(toAdd.back() == FILE){
                skipWords(2,ss);
                string name;
                ss >> name;
                skipWords(3,ss);
                string content;
                ss >> content;
                path.back()->touch(new File(name,content));
            }
        }

    }

    return root;
}
