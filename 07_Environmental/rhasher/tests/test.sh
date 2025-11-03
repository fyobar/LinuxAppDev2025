#!/bin/sh

echo "Running tests..."

RHASHER="./src/rhasher"

if [ ! -x "$RHASHER" ]; then
    echo "FAIL: rhasher binary not found"
    exit 1
fi

TMPFILE=$(mktemp /tmp/rhasher-test.tmp)
trap 'rm -f "$TMPFILE"' EXIT
echo -n "Test data to hash" > "$TMPFILE"

# Test 1: MD5 of file
RHASH_MD5_HEX_FILE=$(echo "MD5 $TMPFILE" | $RHASHER | awk '{print $1}')
SYS_MD5_HEX_FILE=$(md5sum "$TMPFILE" | awk '{print $1}')
if [ "$RHASH_MD5_HEX_FILE" != "$SYS_MD5_HEX_FILE" ]; then
    echo "FAIL: MD5 mismatch"
    echo "  rhasher: $RHASH_MD5_HEX_FILE"
    echo "  md5sum : $SYS_MD5_HEX_FILE"
    exit 1
fi

# Test 2: MD5 of string
RHASH_MD5_HEX_STR=$(echo "MD5 \"test\"" | $RHASHER | awk '{print $1}')
SYS_MD5_HEX_STR=$(echo -n "test" |  md5sum | awk '{print $1}')
if [ "$RHASH_MD5_HEX_STR" != "$SYS_MD5_HEX_STR" ]; then
    echo "FAIL: MD5 mismatch"
    echo "  rhasher: $RHASH_MD5_HEX_STR"
    echo "  md5sum : $SYS_MD5_HEX_STR"
    exit 1
fi

# Test 3: SHA1 of file
RHASH_SHA1_HEX_FILE=$(echo "SHA1 $TMPFILE" | $RHASHER | awk '{print $1}')
SYS_SHA1_HEX_FILE=$(sha1sum "$TMPFILE" | awk '{print $1}')
if [ "$RHASH_SHA1_HEX_FILE" != "$SYS_SHA1_HEX_FILE" ]; then
    echo "FAIL: SHA1 mismatch"
    echo "  rhasher: $RHASH_SHA1_HEX_FILE"
    echo "  sha1sum: $SYS_SHA1_HEX_FILE"
    exit 1
fi

# Test 4: SHA1 of string
RHASH_SHA1_HEX_STR=$(echo "SHA1 \"test\"" | $RHASHER | awk '{print $1}')
SYS_SHA1_HEX_STR=$(echo -n "test" | sha1sum | awk '{print $1}')
if [ "$RHASH_SHA1_HEX_STR" != "$SYS_SHA1_HEX_STR" ]; then
    echo "FAIL: SHA1 mismatch"
    echo "  rhasher: $RHASH_MD5_HEX_STR"
    echo "  sha1sum: $SYS_MD5_HEX_STR"
    exit 1
fi

echo "All tests passed."
exit 0
