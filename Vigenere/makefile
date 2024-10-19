.PHONY: all clean dialog command

CXX=g++
OFLAGS=-O2 -std=c++17 -Wall -DNDEBUG

all: commandline dialog

commandline: vigenere-command

dialog: vigenere-dialog

vigenere-command: commandline.cpp vigenere.o
	$(CXX) $^ -o $@ $(OFLAGS)

vigenere-dialog: dialog.cpp vigenere.o
	$(CXX) $^ -o $@ $(OFLAGS)

vigenere.o: vigenere.cpp vigenere.h
	$(CXX) -c $<  -o $@ $(OFLAGS)

format:
	astyle *.cpp *.h
clean:
	rm -f vigenere-* *.orig *.o
