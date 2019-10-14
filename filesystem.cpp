#include "filesystem.h"

void Filesystem::printUserandLocation()
{
    cout << user;
    for (auto& dir : currentLocation) {
        cout << dir->getName();
    }
    cout << "\n$ ";
}

void Filesystem::run()
{
    string input;
    while (true) {
        printUserandLocation();
        getline(cin, input);
        if (input == "exit") return;
        runCommand(input);
    }
}

void Filesystem::runCommand(string line)
{
    stringstream ss(line);
    string command;
    ss >> command;

    if (command.empty())
        return;
    else if (command == "mkdir") {
        this->mkdir(ss);
    }
    else if (command == "touch") {
        this->touch(ss);
    }
    else if (command == "cd") {
        this->cd(ss);
    }
    else if (command == "ls") {
        this->ls(ss);
    }
    else if (command == "treelist") {
        root->treelist(0);
    }
    else if (command == "rm"){
        this->rm(ss);
    }
    else {
        cout << "Wrong command!"<<endl;
        return;
    }
}

void Filesystem::ls(stringstream &ss)
{
    string path;
    ss >> path;

    Directory* relativeDir = this->getRelativeDir(path);

    if(relativeDir == nullptr){
        return;
    }

    relativeDir->ls();
}

void printFuncName(bool func){
    if(func){
        std::cout<< "mkdir: cannot create directory: ";
    }else{
        std::cout<< "touch: cannot create File: ";
    }
}

void evaluateResult(int result, bool func){
    switch(result){
    case Success:{
        break;
    }
    case FileExists:{
        printFuncName(func);
        std::cout << "File exists\n";
        break;
    }
    case DirectoryExists:{
        printFuncName(func);
        std::cout << "Directory exists\n";
        break;
    }
    }
}

void Filesystem::mkdir(stringstream &ss)
{
    string name;
    ss >> name;

    string path;
    ss >> path;

    Directory* relativeDir = this->getRelativeDir(path);

    if(relativeDir == nullptr){
        return;
    }

    int result = relativeDir->mkdir(new Directory(name));
    evaluateResult(result,true);

}

void Filesystem::touch(stringstream &ss)
{
    string name;
    ss >> name;

    string path;
    ss >> path;

    Directory* relativeDir = this->getRelativeDir(path);

    if (relativeDir == nullptr){
        return;
    }

    string content;
    while (ss >> content) {
    }

    int result = relativeDir->touch(new File(name,content));
    evaluateResult(result,false);
}

std::vector<Directory*> Filesystem::parseRelativePath(string arg)
{
    std::vector<Directory*> relativePath;
    if(arg.back() != '/'){
        std::cout << "Relative path should end with /\n";
        relativePath.push_back(nullptr);
        return relativePath;
    }
    string parsedName = "";
    Directory* relativeDirectory;
    unsigned int begin = 0;
    if(arg.front() == '/'){
        relativeDirectory = this->root;
        begin++;
    }else{
        relativeDirectory = this->currentDirectory;
    }

    for(unsigned int i = begin ; i < arg.size(); i++){
        if( arg[i] == '/'){
            Directory* result = relativeDirectory->contains(parsedName);
            if(result){
                relativeDirectory = result;
                relativePath.push_back(result);
                parsedName = "";
            }else{
                std::cout << "Directory In Path Not Found\n";
                relativePath.push_back(nullptr);
                return relativePath;
            }
        }else{
            parsedName += arg[i];
        }
    }
    return relativePath;
}

Directory* Filesystem::getRelativeDir(string path)
{
    if(path.find('/') != std::string::npos){
        return this->parseRelativePath(path).back();
    }

    return this->currentDirectory;
}

void Filesystem::cd(stringstream &ss)
{
    string directoryName;
    ss >> directoryName;



    if (directoryName.empty()) {
        this->cdRoot();
        return;
    }

    if(directoryName.find('/') != std::string::npos){
        this->cdRelativePath(directoryName);
        return;
    }

    if (directoryName == "..") {
        this->cdParent();
        return;
    }

    if(!this->cdToDirectory(currentDirectory->contains(directoryName))){
        cout << "Directory Not Found\n";
    }
}

void Filesystem::cdRoot()
{
    currentLocation = vector<Directory*>{};
    currentLocation.push_back(root);
    currentDirectory = root;
}

void Filesystem::cdParent()
{
    if(currentDirectory->getNameRaw() == "~"){
        return;
    }
    currentLocation.pop_back();
    currentDirectory = currentLocation.back();
}

void Filesystem::cdRelativePath(string arg)
{
    auto result = this->parseRelativePath(arg);
    if(result.back()){
        this->currentDirectory = result.back();
        this->currentLocation.insert(this->currentLocation.end(), result.begin(), result.end());
    }
}

bool Filesystem::cdToDirectory(Directory* newLocation)
{
    if (newLocation) {
        currentDirectory = newLocation;
        currentLocation.push_back(newLocation);
        return true;
    }
    return false;
}

void Filesystem::deleteDirFor(string name, Directory* location)
{
    Directory* dirToDelete = location->contains(name);
    if(dirToDelete){
        dirToDelete->rm();
        location->deleteDirectory(dirToDelete->getNameRaw());
    }
}

void Filesystem::rm(stringstream &ss)
{
    string arg1;
    ss >> arg1;
    if(arg1.empty()){
        return;
    }

    Directory* relativeDirectory;

    if(arg1 == "-rf"){
        //cerr << "called RM RF \n";
        string arg2;
        ss >> arg2;

        relativeDirectory = this->getRelativeDir(arg2);
        if(relativeDirectory == nullptr){
            return;
        }
        if(relativeDirectory != this->currentDirectory){
            ss >> arg2;
            if(arg2.empty()){
                return;
            }
        }
        this->deleteDirFor(arg2,relativeDirectory);
        return;
    }else{

        relativeDirectory = this->getRelativeDir(arg1);
        if(relativeDirectory == nullptr){
            return;
        }
        if(relativeDirectory != this->currentDirectory){
            ss >> arg1;
            if(arg1.empty()){
                return;
            }
        }

        //cerr << "Called RM\n";
        File* fileToDelete = relativeDirectory->containsFile(arg1);
        Directory* dirToDelete = relativeDirectory->contains(arg1);
        if(dirToDelete){
            cout << "Cannot remove: '" << dirToDelete->getNameRaw() << "' it is a directory\n";
            return;
        }
        if(!fileToDelete){
            cout << "File does not exist\n";
            return;
        }
        relativeDirectory->deleteFile(fileToDelete->getName());
    }
}
