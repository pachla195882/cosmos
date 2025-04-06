CC = g++
CFLAGS = -std=c++14 -I/opt/homebrew/include/
LDFLAGS = -L/opt/homebrew/lib -lSDL3
TARGET = simulator
SOURCES = main.cpp src/Vector2.cpp src/Planet.cpp
OBJECTS = $(SOURCES:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(TARGET) $(LDFLAGS)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)
