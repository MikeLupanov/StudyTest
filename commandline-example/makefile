.PHONY: all clean format

VIGENERE_DIR=../Vigenere
CXX=g++
OFLAGS=-O2 -std=c++17 -Wall -DNDEBUG -I$(VIGENERE_DIR)

SOURCE=commandline.cpp
VIGENERE=$(wildcard $(addprefix $(VIGENERE_DIR)/, *.cpp *.h))
EXECUTABLE=vigenere-command

all: $(EXECUTABLE)

$(EXECUTABLE): $(SOURCE) vigenere.o
	$(CXX) $^ -o $@ $(OFLAGS)

vigenere.o: $(VIGENERE)
	$(CXX) -c $<  -o $@ $(OFLAGS)

format:
	astyle -n -A10 $(SOURCE) $(VIGENERE)

clean:
	rm -f vigenere-* *.o

