#!/bin/sh

MOVE=./move
SRC="source.txt"
DST="destination.txt"

reset_files() {
    rm -f "$SRC" "$DST"
    echo "Some data to transfer" > "$SRC"
}

check_result() {
    expected_code=$1
    if (( exit_code != expected_code )); then
    	echo "FAIL: returned code $exit_code doesn't match expected code $expected_code"
    else
        echo "PASS: received expected exit code $exit_code"
    fi
}

run_fault() {
    fault_spec=$1
    expected_code="$2"
    description="$3"

    reset_files
    echo "Injecting fault: $description"
    strace -q -e fault="$fault_spec" $MOVE "$SRC" "$DST" >/dev/null 2>&1
    exit_code=$?
    check_result $expected_code EXIT_CODE
}

reset_files
$MOVE "$SRC" "$DST"
exit_code=$?
check_result 0 EXIT_CODE

run_fault "openat:error=ENOENT:when=3" 2 "Input open failure"

run_fault "lseek:error=EIO:when=1" 3 "Cannot determine file size"

run_fault "openat:error=EACCES:when=4" 6 "Output open failure"

run_fault "close:error=EIO:when=3" 8 "Input close failure"

run_fault "close:error=EIO:when=4" 9 "Output close failure"

run_fault "unlink:error=EACCES:when=1" 10 "Source delete failure"

echo "All tests executed."

reset_files

