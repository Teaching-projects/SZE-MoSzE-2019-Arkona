#ifndef FILESYSTEMSERIALIZER_H
#define FILESYSTEMSERIALIZER_H
#include "directory.h"
#include <string>
class Directory;

/**
 *
 * @brief Used to conver Json to Directory* and vica versa
 *
 */

class FileSystemSerializer
{
private:
public:
    FileSystemSerializer();

    /**
    * This option is used to encode any data from standard input or from any file.
    */

    static std::string encode(Directory* root);
        
    /**
    * This option is used to decode any encoded data from standard input or from any file.
    */

    static Directory* decode(std::string json);
    
};

#endif // FILESYSTEMSERIALIZER_H
