/**
 * @file guesser.c
 * @brief A number guessing game with optional Roman numeral support.
 *
 * This program asks the user to think of a number between 1 and 100 and
 * tries to guess it using a binary search algorithm. The program can
 * optionally display numbers in the Roman numeral system using the -r
 * command-line option.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <libintl.h>
#include <unistd.h>
#include "config.h"
#include "roman.h"

/** @brief Macro for internationalization */
#define _(STRING) gettext(STRING)

/**
 * @brief Print program usage and options.
 *
 * Uses gettext for internationalization. Call this function
 * when the user passes -h or --help.
 *
 * @param prog_name The program executable name (argv[0])
 */
void print_help(const char *prog_name) {
    printf(_("Usage: %s [OPTIONS]\n"), prog_name);
    printf(_("Options:\n"));
    printf(_("\t-r       Use Roman numerals\n"));
    printf(_("\t-h       Show help message\n"));
    printf(_("\t--help   Show help message\n"));

    printf(_("\nThis program tries to guess a number chosen by the user between 1 and 100.\n"));
    printf(_("It uses a binary search algorithm and optionally displays numbers in Roman numerals.\n"));
}

/**
 * @brief Main entry point for the guesser program.
 *
 * This program asks the user to choose a number between 1 and 100.
 * It then guesses the number using a binary search approach by asking
 * the user if the number is greater than the guessed midpoint.
 *
 * @param argc Number of command-line arguments.
 * @param argv Array of command-line argument strings.
 *
 * @return Returns 0 on successful execution, 1 if an input error occurs.
 *
 * @note Command-line options:
 *  - -r : Use Roman numerals instead of Arabic numbers.
 *  - -h : Display this help message and exit.
 */
int main(int argc, char *argv[]) {

    /* Set locale and gettext for internationalization */
    setlocale(LC_ALL, "");
    bindtextdomain("guesser", LOCALE_PATH);
    textdomain("guesser");

    int use_roman = 0; /**< Flag to indicate whether to use Roman numerals */

    int opt;
    while ((opt = getopt(argc, argv, "rh")) != -1) {
        switch (opt) {
            case 'r':
                /** @brief Enable Roman numeral display */
                use_roman = 1;
                break;
            case 'h':
                print_help(argv[0]);
                return 0;
        }
    }

    int low = 1; /**< Lower bound of the guessing range */
    int high = 100; /**< Upper bound of the guessing range */
    int mid; /**< Current guess */
    char input[128]; /**< Buffer for user input */

    /** @brief Prompt the user to choose a number */
    if (use_roman) printf(_("Choose a random number between %s and %s.\n"), to_roman(low), to_roman(high));
    else printf(_("Choose a random number between %d and %d.\n"), low, high);

    /** @brief Main guessing loop using binary search */
    while (low <= high) {
        mid = (low + high) / 2;

        if (use_roman) printf(_("Is the number greater than %s? (Yes/No): "), to_roman(mid));
        else printf(_("Is the number greater than %d? (Yes/No): "), mid);

        if (fgets(input, sizeof(input), stdin) == NULL) {
            fprintf(stderr, _("Error: failed to read input.\n"));
            return 1;
        }

        /** @brief Remove trailing newline from input */
        input[strcspn(input, "\n")] = 0;

        if (strcmp(input, _("Yes")) == 0) {
            low = mid + 1;
        } else if (strcmp(input, _("No")) == 0) {
            high = mid;
        } else {
            fprintf(stderr, _("Invalid input. Please type exactly 'Yes' or 'No'.\n"));
        }

        if (low == high) break;
    }

    /** @brief Print the guessed number */
    if (use_roman) printf(_("The number is %s!\n"), to_roman(low));
    else printf(_("The number is %d!\n"), low);

    return 0;
}
