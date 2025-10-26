#!/bin/sh

MOVE=./move
SRC="source.txt"
PRT_SRC="PROTECT.txt"
DST="destination.txt"

rm -f "$SRC" "$PRT_SRC" "$DST"

echo "Some data to transfer" > "$SRC"
echo "Some protected data to transfer" > "$PRT_SRC"

LD_PRELOAD=./protect_delete.so $MOVE $SRC $DST
LD_PRELOAD=./protect_delete.so $MOVE $PRT_SRC $DST

if [ -f "$PRT_SRC" ]; then
    echo "PASS: $PRT_SRC was not deleted"
else
    echo "FAIL: $PRT_SRC was deleted"
fi

if [ -f "$SRC" ]; then
    echo "FAIL: $SRC was not deleted"
else
    echo "PASS: $SRC was deleted"
fi

rm -f "$SRC" "$PRT_SRC" "$DST"

