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
        
    /**
    * This option is used to encode any data from standard input or from any file.
    */
    
    static Directory* decode(std::string json);
        
    /**
    * This option is used to decode any encoded data from standard input or from any file.
    */
    
};

#endif // FILESYSTEMSERIALIZER_H
