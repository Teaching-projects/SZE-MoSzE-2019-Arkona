#ifndef FILESYSTEMSERIALIZER_H
#define FILESYSTEMSERIALIZER_H
#include "directory.h"
#include <string>
class Directory;

class FileSystemSerializer
{
private:
public:
    FileSystemSerializer();

    static std::string encode(Directory* root);
    static Directory* decode(std::string json);

};

#endif // FILESYSTEMSERIALIZER_H
