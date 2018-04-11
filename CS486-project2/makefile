all: P2

P2: EulerPath.o deBruijnByHash.o deBruijnByStringComp.o k-assembler.o sequence.o test.o main.o
        g++ -std=c++11 EulerPath.o deBruijnByHash.o deBruijnByStringComp.o k-assembler.o sequence.o test.o main.o -o P2
deBruijnByHash.o: deBruijnByHash.cpp deBruijnByHash.hpp
        g++ -std=c++11 -c deBruijnByHash.cpp

deBruijnByStringComp.o: deBruijnByStringComp.cpp deBruijnByStringComp.hpp
        g++ -std=c++11 -c deBruijnByStringComp.cpp

k-assembler.o: k-assembler.hpp k-assembler.cpp
        g++ -std=c++11 -c k-assembler.cpp

sequence.o: sequence.cpp sequence.hpp
        g++ -std=c++11 -c sequence.cpp

EulerPath.o: EulerPath.cpp EulerPath.hpp
        g++ -std=c++11 -c EulerPath.cpp

main.o: main.cpp
        g++ -std=c++11 -c main.cpp

test.o: test.cpp test.hpp
        g++ -std=c++11 test.cpp

clean:
        rm -rf *.o
