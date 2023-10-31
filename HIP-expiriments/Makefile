CC = hipcc
CFLAGS = -Wall -D__HIP_PLATFORM_AMD__

SOURCES = primitives.c test-send-recv.c
OBJECTS = $(SOURCES:.c=.o)
SRC_DIR = source
EXECUTABLE = iccltest
INCLUDE_DIR = include
BUILD_DIR = build

SOURCES = $(wildcard $(SRC_DIR)/*.c)
OBJECTS = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SOURCES))

all: $(EXECUTABLE)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $@

clean:
	rm -rf $(BUILD_DIR) $(EXECUTABLE)