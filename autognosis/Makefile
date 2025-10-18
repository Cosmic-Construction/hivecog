CC = gcc
CFLAGS = -Wall -Wextra -std=gnu99 -I. -I../common/debug -DLINUX -D__BYTE_ORDER=__LITTLE_ENDIAN -O2
LDFLAGS = -lpthread

SOURCES = autognosis.c hive_coordination.c entropic_bootstrap.c homeostatic_feedback.c feedforward_autopoiesis.c
OBJECTS = $(SOURCES:.c=.o)
TARGET = libautognosis.a
TEST_TARGET = test_autognosis
BOOTSTRAP_TEST = test_bootstrap
HOMEOSTATIC_TEST = test_homeostatic
AUTOPOIESIS_TEST = test_autopoiesis

.PHONY: all clean test

all: $(TARGET)

test: $(TEST_TARGET)
	./$(TEST_TARGET)

test-bootstrap: $(BOOTSTRAP_TEST)
	./$(BOOTSTRAP_TEST)

test-homeostatic: $(HOMEOSTATIC_TEST)
	./$(HOMEOSTATIC_TEST)

test-autopoiesis: $(AUTOPOIESIS_TEST)
	./$(AUTOPOIESIS_TEST)

test-all: test test-bootstrap test-homeostatic test-autopoiesis

$(TARGET): $(OBJECTS)
	ar rcs $(TARGET) $(OBJECTS)
	ranlib $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(TEST_TARGET): test_autognosis.c $(TARGET)
	$(CC) $(CFLAGS) test_autognosis.c -L. -lautognosis $(LDFLAGS) -o $(TEST_TARGET)

$(BOOTSTRAP_TEST): test_bootstrap.c $(TARGET)
	$(CC) $(CFLAGS) test_bootstrap.c -L. -lautognosis $(LDFLAGS) -lm -o $(BOOTSTRAP_TEST)

$(HOMEOSTATIC_TEST): test_homeostatic.c $(TARGET)
	$(CC) $(CFLAGS) test_homeostatic.c -L. -lautognosis $(LDFLAGS) -lm -o $(HOMEOSTATIC_TEST)

$(AUTOPOIESIS_TEST): test_autopoiesis.c $(TARGET)
	$(CC) $(CFLAGS) test_autopoiesis.c -L. -lautognosis $(LDFLAGS) -lm -o $(AUTOPOIESIS_TEST)

test_hive_integration: test_hive_integration.c $(TARGET)
	$(CC) $(CFLAGS) test_hive_integration.c -L. -lautognosis $(LDFLAGS) -o test_hive_integration

clean:
	rm -f $(OBJECTS) $(TARGET) $(TEST_TARGET) $(BOOTSTRAP_TEST) $(HOMEOSTATIC_TEST) $(AUTOPOIESIS_TEST) test_hive_integration

install: $(TARGET)
	mkdir -p ../lib
	cp $(TARGET) ../lib/
	mkdir -p ../include
	cp autognosis.h ../include/