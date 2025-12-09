/**
 * @file roman.c
 * @brief Conversion between Arabic numbers (1–100) and Roman numerals.
 *
 * This file implements two main functions:
 *   - ::to_roman — convert an integer to a Roman numeral string
 *   - ::from_roman — convert a Roman numeral to an integer
 *
 * The implementation uses a static lookup table for all values from 1 to 100,
 * which ensures constant-time conversion to Roman numerals, and a simple
 * linear search for the reverse conversion (which is sufficient for the small range).
 */

#include <string.h>
#include <ctype.h>
#include "roman.h"

/**
 * @brief Lookup table mapping integers 1–100 to Roman numerals.
 *
 * This table provides fast conversion in ::to_roman.
 * Index 0 is unused and always NULL.
 */
static const char *roman_table[101] = {
    NULL,
    "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX", "X",
    "XI", "XII", "XIII", "XIV", "XV", "XVI", "XVII", "XVIII", "XIX", "XX",
    "XXI", "XXII", "XXIII", "XXIV", "XXV", "XXVI", "XXVII", "XXVIII", "XXIX", "XXX",
    "XXXI", "XXXII", "XXXIII", "XXXIV", "XXXV", "XXXVI", "XXXVII", "XXXVIII", "XXXIX", "XL",
    "XLI", "XLII", "XLIII", "XLIV", "XLV", "XLVI", "XLVII", "XLVIII", "XLIX", "L",
    "LI", "LII", "LIII", "LIV", "LV", "LVI", "LVII", "LVIII", "LIX", "LX",
    "LXI", "LXII", "LXIII", "LXIV", "LXV", "LXVI", "LXVII", "LXVIII", "LXIX", "LXX",
    "LXXI", "LXXII", "LXXIII", "LXXIV", "LXXV", "LXXVI", "LXXVII", "LXXVIII", "LXXIX", "LXXX",
    "LXXXI", "LXXXII", "LXXXIII", "LXXXIV", "LXXXV", "LXXXVI", "LXXXVII", "LXXXVIII", "LXXXIX", "XC",
    "XCI", "XCII", "XCIII", "XCIV", "XCV", "XCVI", "XCVII", "XCVIII", "XCIX", "C"
};

/**
 * @brief Convert an integer to a Roman numeral.
 *
 * Converts values in the range **1..100** to their Roman numeral equivalents.
 * The returned string is a pointer to a static lookup table and **must not be freed**.
 *
 * @param value An integer between 1 and 100.

 * @return A pointer to a Roman numeral string,
 *         or `NULL` if the value is outside the supported range.
 */
const char *to_roman(int value) {
    if (value < 1 || value > 100)
        return NULL;
    return roman_table[value];
}

/**
 * @brief Parse a Roman numeral and convert it to an integer.
 *
 * Handles Roman numerals in the range **I..C** (1–100).
 * The function is case-insensitive: `"xiv"` and `"XIV"` are equivalent.
 *
 * @param roman A null-terminated string containing a Roman numeral.
 *
 * @return The corresponding integer value (1–100),
 *         or **-1** if the input is invalid, NULL, or outside the supported range.
 */
int from_roman(const char *roman) {
    if (!roman)
        return -1;

    char buf[32];
    size_t len = strlen(roman);
    if (len >= sizeof(buf))
        return -1;

    /* Normalize to uppercase */
    for (size_t i = 0; i < len; i++)
        buf[i] = toupper((unsigned char)roman[i]);
    buf[len] = '\0';

    /* Linear scan is fine for 100 entries */
    for (int i = 1; i <= 100; i++) {
        if (strcmp(buf, roman_table[i]) == 0)
            return i;
    }

    return -1;
}
