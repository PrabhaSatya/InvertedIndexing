g++ -c invertedindexing.cpp
g++ -c ptrie.cpp
g++ -c skiplist.cpp
g++ -o invertedindexing  invertedindexing.o  ptrie.o  skiplist.o
./invertedindexing
