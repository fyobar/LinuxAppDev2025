CC = gcc
CFLAGS = -Wall
LDLIBS = -ldl

TARGET = move
SO = protect_delete.so

TRASH = $(TARGET) $(SO) *.o *.txt

STRACE_TEST_SCRIPT = error_injection_test.sh
LDPRELOAD_TEST_SCRIPT = test_protected.sh

all: $(TARGET) $(SO)

$(TARGET): move.c
	$(CC) $(CFLAGS) -o $@ $<

$(SO): protect_delete.c
	$(CC) $(CFLAGS) -fPIC -shared -o $@ $< $(LDLIBS)

test: all
	chmod +x "$(STRACE_TEST_SCRIPT)"
	chmod +x "$(LDPRELOAD_TEST_SCRIPT)"

	./$(STRACE_TEST_SCRIPT)
	./$(LDPRELOAD_TEST_SCRIPT)

clean:
	-rm -f $(TRASH)

