#include <iostream>
#include "filesystem.h"

using namespace std;

int main(int argc, char** argv)
{
    Filesystem* cmd;

    if(argc <= 1){
        cmd = new Filesystem(nullptr);
    }else{
        string filename = argv[1];
        cmd = new Filesystem(&filename);
    }

    //cmd->run();

    delete cmd;
    cout << "Terminated\n";

    return 0;
}
