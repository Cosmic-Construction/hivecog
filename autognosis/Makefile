CC = gcc
CFLAGS = -Wall -Wextra -std=gnu99 -I. -I../common/debug -DLINUX -D__BYTE_ORDER=__LITTLE_ENDIAN -O2
LDFLAGS = -lpthread

SOURCES = autognosis.c hive_coordination.c
OBJECTS = $(SOURCES:.c=.o)
TARGET = libautognosis.a
TEST_TARGET = test_autognosis

.PHONY: all clean test

all: $(TARGET)

test: $(TEST_TARGET)
	./$(TEST_TARGET)

$(TARGET): $(OBJECTS)
	ar rcs $(TARGET) $(OBJECTS)
	ranlib $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(TEST_TARGET): test_autognosis.c $(TARGET)
	$(CC) $(CFLAGS) test_autognosis.c -L. -lautognosis $(LDFLAGS) -o $(TEST_TARGET)

test_hive_integration: test_hive_integration.c $(TARGET)
	$(CC) $(CFLAGS) test_hive_integration.c -L. -lautognosis $(LDFLAGS) -o test_hive_integration

clean:
	rm -f $(OBJECTS) $(TARGET) $(TEST_TARGET) test_hive_integration

install: $(TARGET)
	mkdir -p ../lib
	cp $(TARGET) ../lib/
	mkdir -p ../include
	cp autognosis.h ../include/