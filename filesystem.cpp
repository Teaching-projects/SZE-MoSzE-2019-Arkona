#include "filesystem.h"
#include <fstream>

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


void Filesystem::trimNames(char character)
{
    root->eraseCharFromName(character);
}

void Filesystem::startup(string* filename)
{
    if (filename){
        ifstream f(*filename);
        if(f.is_open()){
            string json((std::istreambuf_iterator<char>(f)),
                             std::istreambuf_iterator<char>());
            this->root = FileSystemSerializer::decode(json);
            this->currentLocation.front() = root;
            this->trimNames('"');
        }
    }
    this->run();
}

void Filesystem::exit(string* filename)
{
    string json = FileSystemSerializer::encode(this->root);

    if (filename){
        ofstream f(*filename);
        f << json;
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
    }else if (command == "echo"){
        this->echo(ss);
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

void evaluateResult(int result){
    switch(result){
    case Success:{
        break;
    }
    case FileExists:{
        std::cout <<"Error: File with same name exists\n";
        break;
    }
    case DirectoryExists:{
        std::cout << "Error: Directory with same name exists\n";
        break;
    }
    }
}

void Filesystem::mkdir(stringstream &ss)
{
    string path;
    ss >> path;

    string name = path.substr(path.find_last_of("/") + 1);
    path.erase(path.length() - name.size());

    Directory* relativeDir = this->getRelativeDir(path);

    if(relativeDir == nullptr){
        return;
    }

    int result = relativeDir->mkdir(name);
    evaluateResult(result);
}

void Filesystem::touch(stringstream &ss)
{
    string path;
    ss >> path;

    string name = path.substr(path.find_last_of("/") + 1);
    path.erase(path.length() - name.size());

    Directory* relativeDir = this->getRelativeDir(path);

    if (relativeDir == nullptr){
        return;
    }

    string content;
    while (ss >> content) {
    }

    int result = relativeDir->touch(name,content);
    evaluateResult(result);
}

std::vector<Directory*> Filesystem::parseRelativePath(string arg)
{

    if(arg == "/"){
        std::vector<Directory*> newPath{this->root};
        return newPath;
    }

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
        relativeDirectory = this->currentLocation.back();
    }

    for(unsigned int i = begin ; i < arg.size(); i++){
        if( arg[i] == '/'){
            Directory* result = relativeDirectory->getDirectory(parsedName);
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

    return this->currentLocation.back();
}

void Filesystem::cd(stringstream &ss)
{
    string directoryName;
    ss >> directoryName;

    if (directoryName.empty()) {
        this->cdRelativePath("/");
    }
    else if(directoryName.find('/') != std::string::npos){
        this->cdRelativePath(directoryName);
    }
    else if (directoryName == "..") {
        if(currentLocation.back()->getNameRaw() == "~"){
            return;
        }
        currentLocation.pop_back();
    }
    else if(currentLocation.back()->getDirectory(directoryName)){
        currentLocation.push_back(currentLocation.back()->getDirectory(directoryName));
    }else{
        cout << "Directory Not Found\n";
    }
}

void Filesystem::cdRelativePath(string arg)
{
    auto result = this->parseRelativePath(arg);
    if(result.back()){
        this->currentLocation = result;
    }
}

void Filesystem::deleteDirFor(string name, Directory* location)
{
    Directory* dirToDelete = location->getDirectory(name);
    if(dirToDelete){
        dirToDelete->rm();
        location->deleteDirectory(dirToDelete->getNameRaw());
    }
}

void Filesystem::echo(stringstream &ss)
{
    string content = "";
    string tmp;

    string ssString = ss.str();

    if (ssString.find(">") == std::string::npos)
    {
       cout << "Wrong format: echo content > filename\n";
       return;
    }

    while(ss >> tmp){
        if (tmp == ">") {break;}
        content += tmp;
    }

    string path;
    ss >> path;

    string name = path.substr(path.find_last_of("/") + 1);
    path.erase(path.length() - name.size());

    Directory* relativeDir = this->getRelativeDir(path);

    if (relativeDir == nullptr){
        return;
    }

    int result = relativeDir->touch(name,content);
    evaluateResult(result);
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
        if(relativeDirectory != this->currentLocation.back()){
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
        if(relativeDirectory != this->currentLocation.back()){
            ss >> arg1;
            if(arg1.empty()){
                return;
            }
        }

        //cerr << "Called RM\n";
        File* fileToDelete = relativeDirectory->getFile(arg1);
        Directory* dirToDelete = relativeDirectory->getDirectory(arg1);

        if(dirToDelete){
            if(dirToDelete->isEmpty() == false){
                cout << "Cannot remove: '" << dirToDelete->getNameRaw() << "' it is not an empty directory\n";
            }else{
                this->deleteDirFor(arg1,relativeDirectory);
            }
        }else if(fileToDelete){
            relativeDirectory->deleteFile(fileToDelete->getName());
        }else{
            cout << "File or Directory does not exist\n";
        }

    }
}
