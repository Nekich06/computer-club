.PHONY: build run clean

CFLAGS += -Iinc
SRCS = src/main.cpp src/shift.cpp src/time.cpp src/simulator.cpp src/errors.cpp src/parser.cpp src/event.cpp
TARGET = bin/computer_club
BIN_DIR = bin

build: $(TARGET)

$(TARGET): $(SRCS) | $(BIN_DIR)
	$(CXX) $(CFLAGS) $(SRCS) -o $(TARGET)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

run: $(TARGET)
	./$(TARGET) $(ARGS)

clean:
	rm -f $(TARGET)
