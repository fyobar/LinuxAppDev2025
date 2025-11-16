#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <libintl.h>
#include "config.h"

#define _(STRING) gettext(STRING)


int main(void) {

    setlocale(LC_ALL, "");
    bindtextdomain("guesser", LOCALE_PATH);
    textdomain("guesser");

    int low = 1;
    int high = 100;
    int mid;
    char input[128];

    printf(_("Choose a random number between 1 and 100.\n"));

    while (low <= high) {
        mid = (low + high) / 2;
        printf(_("Is the number greater than %d? (Yes/No): "), mid);

        if (fgets(input, sizeof(input), stdin) == NULL) {
            fprintf(stderr, _("Error: failed to read input.\n"));
            return 1;
        }

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

    printf(_("The number is %d!\n"), low);

    return 0;
}
