#include "file.h"

std::string File::getJsonContent(const string& current)
{

    return current + "{ \"name\" : \""
            + this->name
            +"\" , "
            + "\"content\" : "
            + this->content
            +""
            + " } ";
}
