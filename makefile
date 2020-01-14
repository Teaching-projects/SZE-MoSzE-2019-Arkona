OBJS=main.o filesystem.o file.o directory.o filesystemserializer.o
CXXFLAGS = -g -std=c++11

all: $(OBJS)
	g++ -o terminal $(OBJS)

main.o: main.cpp
	g++ -g -Wall -c main.cpp $(CXXFLAGS)
  
filesystem.o: filesystem.cpp
	g++ -g -Wall -c filesystem.cpp $(CXXFLAGS)
  
file.o: file.cpp
	g++ -g -Wall -c file.cpp $(CXXFLAGS)
  
directory.o: directory.cpp
	g++ -g -Wall -c directory.cpp $(CXXFLAGS)
	
filesystemserializer.o: filesystemserializer.cpp
	g++ -g -Wall -c filesystemserializer.cpp $(CXXFLAGS)
  
clean:
	rm -f *.o
