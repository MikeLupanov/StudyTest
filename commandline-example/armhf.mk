.PHONY: all clean format start

VIGENERE_DIR=../Vigenere
CXX=arm-linux-gnueabihf-g++
OFLAGS=-O2 -std=c++17 -Wall -DNDEBUG -I$(VIGENERE_DIR)

SOURCE=commandline.cpp
VIGENERE=$(wildcard $(addprefix $(VIGENERE_DIR)/, *.cpp *.h))
EXECUTABLE=vigenere-command-armhf
OBJ=vigenere-armhf.o
ARMHF_LIBS=/usr/arm-linux-gnueabihf/

all: $(EXECUTABLE)

$(EXECUTABLE): $(SOURCE) $(OBJ)
	$(CXX) $^ -o $@ $(OFLAGS)

$(OBJ): $(VIGENERE)
	$(CXX) -c $<  -o $@ $(OFLAGS)

start:
	qemu-arm -L $(ARMHF_LIBS) ./$(EXECUTABLE) -k ZERO -e LADOGA
	qemu-arm -L $(ARMHF_LIBS) ./$(EXECUTABLE) -k ZERO -d KEUCFE
