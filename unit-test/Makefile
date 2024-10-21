.PHONY: all clean test format

VIGENERE_DIR=../Vigenere
CXX=g++
OFLAGS=-O2 -std=c++17 -Wall -DNDEBUG -I$(VIGENERE_DIR)
LDFLAGS=-lUnitTest++ 

SOURCES=$(VIGENERE_DIR)/vigenere.cpp unittest.cpp
HEADERS=$(VIGENERE_DIR)/vigenere.h
EXECUTABLE=vigenere-test


$(EXECUTABLE): $(SOURCES) $(HEADERS)
	$(CXX)  $(SOURCES)  -o $@ $(OFLAGS) $(LDFLAGS)

test: $(EXECUTABLE)
	./$(EXECUTABLE) 

format:
	astyle -n -A10 $(SOURCES) $(HEADERS)
clean:
	rm -f $(EXECUTABLE)
