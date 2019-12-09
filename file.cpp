#include "file.h"

std::string File::getJsonContent(string current)
{

    return current + "{ \"name\" : \""
            + this->name
            +"\" , "
            + "\"content\" : "
            + this->content
            +""
            + " } ";
}
