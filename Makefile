CXX = g++
CXXFLAGS = -std=c++17 -static-libgcc -static-libstdc++
CXXFLAGS_DBG = -std=c++17 -static-libgcc -static-libstdc++ -g

.PHONY: all clean

all: json

json: main.cpp
	$(CXX) $(CXXFLAGS) -o json main.cpp

dbg: main.cpp
	$(CXX) $(CXXFLAGS_DBG) -o json-dbg main.cpp

clean:
	rm -f json json-dbg

