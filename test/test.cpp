#include <gtest/gtest.h>
#include "../file.h"
#include "../file.cpp"
#include "../directory.h"
#include "../directory.cpp"
#include "../filesystem.h"
#include "../filesystem.cpp"
#include "../filesystemserializer.h"
#include "../filesystemserializer.cpp"
#include <iostream>
#include <sstream>

TEST(FileTest,savedNameCorrectly){

	std::string* name = new std::string("test");
	std::string* content = new std::string("test2");
	File* f = new File(*name,*content);
	
   	ASSERT_EQ(f->getName(), "test");
}

TEST(FileTest,ErasingCharacters){

	std::string* name = new std::string("testaaaaaaaa");
	std::string* content = new std::string("test2");
	File* f = new File(*name,*content);
	
	f->eraseCharFromName('a');
   	ASSERT_EQ(f->getName(), "test");
	delete name;
	delete content;
	delete f;
}

TEST(DirectoryTest, FileContent){

	std::string* name = new std::string("test");
	Directory* d = new Directory(*name);

	ASSERT_TRUE(d->isEmpty());	

	d->touch(*name,*name);
	ASSERT_NE(d->getFile(*name),nullptr);
	ASSERT_TRUE(d->getFile(*name));

	delete name;
	delete d;
}

TEST(DirectoryTest, DirectoryContent){

	std::string* name = new std::string("test");
	std::string* fileName = new std::string("testaaaa");
 
	Directory* d = new Directory(*name);

	d->mkdir(*name);
	ASSERT_FALSE(d->isEmpty());	
	
	d->deleteDirectory(*name);
	ASSERT_TRUE(d->isEmpty());

	d->touch(*fileName, *name);
	File* file;

	d->eraseCharFromName('a');
	file = d->getFile(*name);
	ASSERT_NE(file,nullptr);
	
	delete name;
	delete fileName;
	delete d;
}

TEST(FilesystemSerializerTest, decodeTest){
	std::string* test = new std::string("test");
	std::string* json = new std::string(" {  \"name\" : \"~\" ,  \"files\" : [ ],  \"directories\" : [  {  \"name\" : \"test\" ,  \"files\" : [ ],  \"directories\" : [  ]  }  ]  } ");

	Directory* d = FileSystemSerializer::decode(*json);
	ASSERT_NE(d, nullptr);
	d->eraseCharFromName('"');
	ASSERT_NE(d->getDirectory(*test),nullptr);

	delete json;
	delete test;
}

TEST(FilesystemSerializerTest, endcodeTest){
	std::string* root = new std::string("~");
	std::string* test = new std::string("test");
	std::string* json = new std::string(" {  \"name\" : \"~\" ,  \"files\" : [ ],  \"directories\" : [  {  \"name\" : \"test\" ,  \"files\" : [ ],  \"directories\" : [  ]  }  ]  } ");
	Directory* d = new Directory(*root);
	d->mkdir("test");
	
	ASSERT_EQ(FileSystemSerializer::encode(d), *json);
	delete root;
	delete json;
	delete test;
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
