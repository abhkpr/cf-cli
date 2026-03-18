CXX = g++
CXXFLAGS = -Iinclude -std=c++17 -Wall -Wextra
LDFLAGS = -lcurl

SRC = $(wildcard src/*.cpp src/api/*.cpp src/commands/*.cpp)
OBJ = $(SRC:.cpp=.o)

TARGET = build/cf

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(OBJ) -o $(TARGET) $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)
