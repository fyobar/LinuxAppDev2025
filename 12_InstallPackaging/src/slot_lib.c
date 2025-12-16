/**
 * @file slot_lib.c
 * @brief Implementation of slot machine library functions.
 *
 * This file contains functions for displaying the slot machine reels,
 * headers, footers, and generating random reel symbols.
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include <libintl.h>
#include <wchar.h>
#include <string.h>
#include "slot_lib.h"
#include "config.h"


#define _(STRING) gettext(STRING)

/**
 * @brief Calculate the display width of a UTF-8 string.
 *
 * Converts the input string to wide characters and computes
 * its display width. Falls back to strlen() if conversion fails.
 *
 * @param s Input UTF-8 string.
 * @return Display width of the string in characters.
 */
static int utf8_width(const char *s) {
    wchar_t wcs[128];
    int len = mbstowcs(wcs, s, 128);
    if (len < 0)
        return strlen(s);   // fallback
    return wcswidth(wcs, len);
}

/**
 * @brief Predefined symbols for the slot machine reels.
 *
 * Each symbol is a 3x5 text block representing an item or number.
 */
const char *symbols[NUM_ITEMS][3] = {
    { "┌───┐", "│ 1 │", "└───┘" },
    { "┌───┐", "│ 2 │", "└───┘" },
    { "┌───┐", "│ 3 │", "└───┘" },
    { "┌───┐", "│ 4 │", "└───┘" },
    { "┌───┐", "│ 5 │", "└───┘" },
    { "┌───┐", "│ 6 │", "└───┘" }
};

/**
 * @brief Print the slot machine header including credits.
 *
 * @param credits Current player credits.
 */
void print_header(int credits) {
    char line[64];
    int pad;

    snprintf(line, sizeof(line),
             "%s %d", _("Credits:"), credits);

    pad = INNER_WIDTH - utf8_width(line);
    if (pad < 0) pad = 0;

    printf("      %s\n", _("SLOT MACHINE"));
    printf("┌===================┐\n");
    printf("│ %s%*s │\n", line, pad, "");
}

/**
 * @brief Print the 3 slot reels.
 *
 * @param r1 Array of 3 strings for reel 1.
 * @param r2 Array of 3 strings for reel 2.
 * @param r3 Array of 3 strings for reel 3.
 */
void print_reels(const char *r1[3], const char *r2[3], const char *r3[3]) {
    for (int i = 0; i < 3; i++) {
        printf("│ %s %s %s │\n", r1[i], r2[i], r3[i]);
    }
}

/**
 * @brief Print the footer of the slot machine including current bet.
 *
 * @param bet Current bet amount.
 */
void print_footer(int bet) {
    char line[64];
    int pad;

    printf("│===================│\n");

    if (bet > 0) {
        snprintf(line, sizeof(line),
                 "%s %d", _("Current bet:"), bet);

        pad = INNER_WIDTH - utf8_width(line);
        if (pad < 0) pad = 0;

        printf("│ %s%*s │\n", line, pad, "");
    }

    printf("└===================┘\n");
    printf("      [ %s ]\n", _("Spin!"));
}

/**
 * @brief Generate a random reel symbol index.
 *
 * Returns a random integer from 0 to NUM_ITEMS-1 representing
 * a reel symbol.
 *
 * @return Random index for the reel symbol.
 */
int spin_reel() {
    return rand() % NUM_ITEMS;
}
