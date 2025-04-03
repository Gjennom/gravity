CC = g++ -std=c++17
LDFLAGS = -lraylib

TARGET = gravity.exe
SRC = gravity.cpp gravity_functions.cpp
OBJ = $(SRC:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) -o $(TARGET) $(OBJ) $(LDFLAGS)

%.o: %.cpp gravity.h
	$(CC) -c $< -o $@

clean:
	rm -f $(TARGET) $(OBJ)
