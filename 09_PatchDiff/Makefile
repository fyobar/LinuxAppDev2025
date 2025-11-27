CC = gcc
CFLAGS = -Wall


ORIG = maze.c
P1 = maze_p1.c
P2 = maze_p2.c
P3 = maze_p3.c

BIN0 = maze_orig
BIN1 = maze_p1
BIN2 = maze_p2
BIN3 = maze_p3

PATCH1 = maze_p1.patch
PATCH2 = maze_p2.patch
PATCH3 = maze_p3.patch

TRASH = $(BIN0) $(BIN1) $(BIN2) $(BIN3) $(P1) $(P2) $(P3)



all: $(BIN0) $(BIN1) $(BIN2) $(BIN3)


$(BIN0): $(ORIG)
	$(CC) $(CFLAGS) -o $@ $<

$(BIN1): $(P1)
	$(CC) $(CFLAGS) -o $@ $<

$(BIN2): $(P2)
	$(CC) $(CFLAGS) -o $@ $<

$(BIN3): $(P3)
	$(CC) $(CFLAGS) -o $@ $<


$(P1): $(ORIG) $(PATCH1)
	cp $(ORIG) $@
	patch $@ $(PATCH1)

$(P2): $(P1) $(PATCH2)
	cp $(P1) $@
	patch $@ $(PATCH2)

$(P3): $(P2) $(PATCH3)
	cp $(P2) $@
	patch $@ $(PATCH3)


run: $(BIN0) $(BIN1) $(BIN2) $(BIN3)
	@echo "=== Run original maze w/o params) ==="
	./$(BIN0)
	@echo ""
	@echo "=== Run patched maze w/ size) ==="
	./$(BIN1) 6
	@echo ""
	@echo "=== Run double patched maze w/ pass+wall and size ==="
	./$(BIN2) ".*" 6
	@echo ""
	@echo "=== Run triply patched maze w/ seed, pass+wall and size ==="
	./$(BIN3) 99 ".*" 6
	@echo ""


clean:
	rm -f $(TRASH)
