/**
 * @file roman.h
 * @brief Roman numeral conversion utilities for values 1–100.
 */

#ifndef ROMAN_H
#define ROMAN_H

/**
 * @brief Convert integer (1–100) to a Roman numeral string.
 *
 * @param value Integer number (1–100).
 * @return Pointer to static string with Roman numeral representation,
 *         or NULL if value is out of range.
 */
const char *to_roman(int value);

/**
 * @brief Convert Roman numeral (I–C) to integer.
 *
 * Handles uppercase or lowercase input.
 *
 * @param roman Roman numeral string.
 * @return Integer representation (1–100), or -1 on invalid input.
 */
int from_roman(const char *roman);

#endif
