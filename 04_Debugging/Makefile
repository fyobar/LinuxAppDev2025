TARGET = range
TRASH = $(TARGET) $(TARGET).dSYM *.txt *.o
CC = gcc
CFLAGS = -O0 -g
SRC = range.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -fr $(TRASH)
	
test: $(TARGET)
	./range 1 12 | grep -E '\b[0-9]*[05]\b' > ref_output_1.txt
	./range -100 100 3 | sed -n '28,35p'  > ref_output_2.txt
	
	gdb -x debug_script_1.gdb ./range --quiet --batch >&1 | tee gdb_output_1.txt
	gdb -x debug_script_2.gdb ./range --quiet --batch >&1 | tee gdb_output_2.txt

	grep '^start' gdb_output_1.txt | sed -n 's/.*value[[:space:]]*=[[:space:]]*\([0-9\-]\+\).*/\1/p' > gdb_output_processed_1.txt
	grep '^start' gdb_output_2.txt | sed -n 's/.*value[[:space:]]*=[[:space:]]*\([0-9\-]\+\).*/\1/p' > gdb_output_processed_2.txt
	
	cmp ref_output_1.txt gdb_output_processed_1.txt
	cmp ref_output_2.txt gdb_output_processed_2.txt
	
