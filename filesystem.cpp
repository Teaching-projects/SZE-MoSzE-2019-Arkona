#include "filesystem.h"

void Filesystem::printUserandLocation()
{
	cout << user;
	for (auto& dir : currentLocation) {
		cout << dir->getName();
	}
	cout << "\n$ ";

	for (vector<Directory*>::iterator it = currentLocation.begin(); it != currentLocation.end(); it++) {

	}

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
		currentDirectory->ls();
	}
	else if (command == "treelist") {
		root->treelist(0);
	}
	else {
		cout << "Wrong command!"<<endl;
		return;
	}
}

void Filesystem::mkdir(stringstream &ss)
{
	string name;
	ss >> name;

	if (!currentDirectory->mkdir(new Directory(name))){
        cout << "Directory already exists\n";
   	 }

}

void Filesystem::touch(stringstream &ss)
{
	string name;
	ss >> name;
	string content;
	while (ss >> content) {
		;
	}

	if (!currentDirectory->touch(new File(name, content))) {
		cout << "File already exists\n";
	}
}

void Filesystem::cd(stringstream &ss)
{
	string directoryName;
	ss >> directoryName;

	if (directoryName.empty()) {
		currentLocation = vector<Directory*>{};
		currentLocation.push_back(root);
		currentDirectory = root;
		return;
	}

	if (directoryName == "..") {
		if(currentDirectory->getNameRaw() == "~"){
			return;
		}
		currentLocation.pop_back();
		currentDirectory = currentLocation.back();
		return;
	}

	Directory* newLocation = new Directory(directoryName);

	if (newLocation) {
		currentDirectory = newLocation;
		currentLocation.push_back(newLocation);
		return;
	}

	cout << "Directory Not Found\n";

}
