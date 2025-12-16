/**
 * @file slot_lib.h
 * @brief Slot machine library functions and constants.
 *
 * This header provides functions for displaying slot machine reels,
 * headers, footers, and spinning logic. It also defines constants
 * used for reel display dimensions and number of symbols.
 */

#ifndef SLOT_LIB_H
#define SLOT_LIB_H

/** @brief Number of different items in the slot machine. */
#define NUM_ITEMS 6

/** @brief Width of the inner reel display (must match symbols width). */
#define INNER_WIDTH 17

/**
 * @brief 2D array representing all slot machine symbols.
 *
 * Each symbol consists of 3 strings forming a 3x5 visual representation:
 *  ┌───┐
 *  │ 1 │
 *  └───┘
 *
 * Indexed as symbols[NUM_ITEMS][3].
 */
extern const char *symbols[NUM_ITEMS][3];

/**
 * @brief Print the game header including current credits.
 *
 * @param credits Current player credits to display in the header.
 */
void print_header(int credits);

/**
 * @brief Print the current state of the three reels.
 *
 * @param r1 First reel symbol (3 lines)
 * @param r2 Second reel symbol (3 lines)
 * @param r3 Third reel symbol (3 lines)
 */
void print_reels(const char *r1[3], const char *r2[3], const char *r3[3]);

/**
 * @brief Print the footer of the slot machine including current bet.
 *
 * @param bet Current bet amount. If 0, no bet is displayed.
 */
void print_footer(int bet);

/**
 * @brief Generate a random reel result.
 *
 * Returns an integer index between 0 and NUM_ITEMS-1
 * corresponding to one of the symbols.
 *
 * @return Index of the selected symbol for the reel.
 */
int spin_reel();

#endif /* SLOT_LIB_H */
