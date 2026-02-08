CFLAGS += -Iinc
SRCS = src/main.cpp src/shift.cpp src/time.cpp src/simulator.cpp src/errors.cpp src/parser.cpp src/event.cpp
TARGET = bin/computer_club

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(CFLAGS) $(SRCS) -o $(TARGET)

run: $(TARGET)
	./$(TARGET) $(ARGS)

clean:
	rm -f $(TARGET)
