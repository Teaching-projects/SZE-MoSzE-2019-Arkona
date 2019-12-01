OBJS=main.o filesystem.o file.o directory.o filesystemserializer.o
CXXFLAGS = -g -std=c++11

all: $(OBJS)
	g++ -o terminal $(OBJS)

main.o: main.cpp
	g++ -c main.cpp $(CXXFLAGS)
  
filesystem.o: filesystem.cpp
	g++ -c filesystem.cpp $(CXXFLAGS)
  
file.o: file.cpp
	g++ -c file.cpp $(CXXFLAGS)
  
directory.o: directory.cpp
	g++ -c directory.cpp $(CXXFLAGS)
	
filesystemserializer.o: filesystemserializer.cpp
	g++ -c filesystemserializer.cpp $(CXXFLAGS)
  
clean:
	rm -f *.o
