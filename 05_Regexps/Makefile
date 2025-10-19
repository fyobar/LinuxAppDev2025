TARGET = esub

CC = gcc

CFLAGS = -Wall

TRASH = $(TARGET)

SRC = esub.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -fr $(TRASH)

test: $(TARGET)
	test_string_1="Hello world"
	test_pattern_1="(world)"
	test_substitution_1="<b>\1<\/b>/"

	test_string_2="flight 777"
	test_pattern_2="([a-z]+) ([0-9]+)"
	test_substitution_2="Number: \2 Word: \1/"

	test_string_3="user@example.com"
	test_pattern_3=".*@([^ ]+)"
	test_substitution_3="\1"


	@if [ "$$(./esub $test_pattern_1 $test_substitution_1 $test_string_1)" = "$$(echo "$test_string_1" | sed -E 's/$test_pattern_1/$test_substitution_1/')" ] && \
	[ "$$(./esub $test_pattern_2 $test_substitution_2 $test_string_2)" = "$$(echo "$test_string_2" | sed -E 's/$test_pattern_2/$test_substitution_2/')" ] && \
	[ "$$(./esub $test_pattern_3 $test_substitution_3 $test_string_3)" = "$$(echo "$test_string_3" | sed -E 's/$test_pattern_3/$test_substitution_3/')" ] ; then \
		echo "Match"; \
	else \
		echo "Don't match"; \
	fi
