/**
 * @file slot_machine.c
 * @brief Main entry point for the Slot Machine game.
 *
 * Implements a console slot machine game with animated reels, betting,
 * credit tracking, and i18n support via gettext.
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <locale.h>
#include <libintl.h>
#include <string.h>
#include <ctype.h>
#include "slot_lib.h"
#include "config.h"

#define _(STRING) gettext(STRING)  /**< Shortcut for gettext translation */
#define CLEAR "clear"              /**< Command to clear console screen */


/**
 * @brief Prints localized help information for the slot machine game
 */
void print_help(void) {
    printf(_("Slot Machine Game\n"));
    printf("=================\n");
    printf(_("\nUsage: slot_machine [options]\n\n"));
    printf(_("Options:\n"));
    printf(_("  -h, --help    Show this help message and exit\n\n"));
    printf(_("Gameplay:\n"));
    printf(_("  Enter your bet (1 to your current credits) to spin the reels.\n"));
    printf(_("  Enter 'q' to quit the game.\n"));
    printf(_("  Three matching symbols: win 5× bet\n"));
    printf(_("  Two matching symbols: win 2× bet\n"));
    printf(_("  No match: lose your bet\n"));
}

/**
 * @brief Calculate UTF-8 string length in characters.
 *
 * This function counts the number of Unicode characters in a UTF-8
 * encoded string. It is used for proper alignment and formatting
 * of multi-byte characters.
 *
 * @param s UTF-8 encoded string
 * @return Number of characters (not bytes)
 */
int utf8len(const char *s) {
    int len = 0;
    unsigned char c;
    while ((c = (unsigned char)*s++)) {
        if ((c & 0xC0) != 0x80) len++;
    }
    return len;
}

/**
 * @brief Entry point of the Slot Machine game.
 *
 * Sets up locale, initializes credits, and enters the main game loop.
 * The user can place bets, spin the reels, and win or lose credits.
 * Input validation is performed for numeric bets, and the player
 * can exit the game at any time by entering 'q'.
 *
 * @return Exit status code (0 on normal exit)
 */
int main(int argc, char *argv[]) {
    setlocale(LC_ALL, "");
    bindtextdomain("slot_machine", LOCALE_PATH);
    textdomain("slot_machine");

    // Check command-line arguments
    for (int i = 1; i < argc; i++) {
        if ((strcmp(argv[i], "-h") == 0) || (strcmp(argv[i], "--help") == 0)) {
            print_help();
            return 0;
        }
    }

    int credits = 100;  /**< Player's initial credits */
    int r1, r2, r3;     /**< Reel results */

    srand(time(NULL));

    while (1) {
        system(CLEAR);
        print_header(credits);
        print_reels(symbols[0], symbols[0], symbols[0]);  /**< Initial display */
        print_footer(0);

        if (credits <= 0) {
            printf(_("\nYou are out of credits. Game over.\n"));
            break;
        }

        /* --- User input for bet with validation and quit option --- */
        char input[32];
        int bet = -1;

        while (1) {
            printf(_("\nEnter your bet (or 'q' to quit): "));
            if (!fgets(input, sizeof(input), stdin)) {
                bet = 0;
                break;
            }

            input[strcspn(input, "\n")] = 0;  /**< Remove newline */

            if (strcmp(input, "q") == 0 || strcmp(input, "Q") == 0) {
                bet = 0;
                break;
            }

            /* Validate numeric input */
            int valid = 1;
            for (size_t i = 0; i < strlen(input); i++) {
                if (!isdigit((unsigned char)input[i])) {
                    valid = 0;
                    break;
                }
            }

            if (!valid) {
                printf(_("Invalid input. Please enter a number or 'q'.\n"));
                continue;
            }

            bet = atoi(input);

            if (bet <= 0 || bet > credits) {
                printf(_("Invalid bet. Must be between 1 and %d.\n"), credits);
                continue;
            }

            break;  /**< Correct input received */
        }

        if (bet == 0) {
            printf(_("\nThanks for playing.\n"));
            break;
        }

        /* --- Independent reel animation --- */
        int total_steps = 15;
        r1 = spin_reel();
        r2 = spin_reel();
        r3 = spin_reel();

        for (int step = 0; step <= total_steps; step++) {
            int i1 = step < total_steps - 2 ? spin_reel() : r1;
            int i2 = step < total_steps - 1 ? spin_reel() : r2;
            int i3 = step < total_steps     ? spin_reel() : r3;

            system(CLEAR);
            print_header(credits);
            print_reels(symbols[i1], symbols[i2], symbols[i3]);
            print_footer(bet);

            usleep(100000);  /**< Delay for animation effect */
        }

        /* --- Payout logic --- */
        if (r1 == r2 && r2 == r3) {
            int win = bet * 5;
            credits += win;
            printf(_("\nJACKPOT! You win %d credits.\n"), win);
        } else if (r1 == r2 || r2 == r3 || r1 == r3) {
            int win = bet * 2;
            credits += win;
            printf(_("\nTwo matched! You win %d credits.\n"), win);
        } else {
            credits -= bet;
            printf(_("\nNo match. You lose %d credits.\n"), bet);
        }

        printf(_("\nPress Enter to continue..."));
        getchar();
    }

    return 0;
}
