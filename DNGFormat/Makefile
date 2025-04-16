CC = gcc
CFLAGS = -shared -fPIC
SRC_DIR = ./src
BUILD_DIR = ./libs/shared

TARGETS = $(BUILD_DIR)/PNGtoDNG.so $(BUILD_DIR)/DNGtoPNG.so

all: $(TARGETS)

$(BUILD_DIR)/PNGtoDNG.so: $(SRC_DIR)/PNGtoDNG.c
	$(CC) $(CFLAGS) -o $@ $<

$(BUILD_DIR)/DNGtoPNG.so: $(SRC_DIR)/DNGtoPNG.c
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -f $(TARGETS)
