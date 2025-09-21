#include <curses.h>
#include <locale.h>
#include <string.h>

#define DX 8
#define DY 4


int contains_new_line(const char *str) {
        for (int i = 0; str[i] != '\0'; i++) {
                if (str[i] == '\n') return 1;
        }

        return 0;
}

void print_truncated(WINDOW *win, const char *str, int max_len) {
        char line[max_len + 1];
        strncpy(line, str, max_len);
        line[max_len] = '\0';

        wprintw(win, (contains_new_line(line) ? "%s" : "%s\n"), line);
}


int main(int argc, char *argv[]) {
        FILE *file;
        WINDOW *frame, *window;

        char buffer[256];
        int c = 0;

        if (argc != 2) {
                fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
                return 1;
        }

        file = fopen(argv[1], "r");

        if (file == NULL) {
                fprintf(stderr, "Error opening file: %s\n", argv[1]);
                return 1;
        }

        setlocale(LC_ALL, "");
        initscr();
        noecho();
        cbreak();
        refresh();
        
        int width = COLS - 2 * DX;
        int height = LINES - 2 * DY;

        frame = newwin(height, width, DY, DX);
        box(frame, 0, 0);
        mvwaddstr(frame, 0, (int)((width - 5) / 2), argv[1]);
        wrefresh(frame);

        window = newwin(height - 2, width - 2, DY + 1, DX + 1);
        keypad(window, TRUE);
        scrollok(window, TRUE);

        int row_limit = height - 3;
        int col_limit = width - 3;

        for (int i = 0; i < row_limit; i++) {
                if (fgets(buffer, sizeof(buffer), file) != NULL) {
                        print_truncated(window, buffer, col_limit);
                }
        }

        while ((c = wgetch(window)) != 27) {
                if (c == 32) {
                        if (fgets(buffer, sizeof(buffer), file) != NULL) {
                                print_truncated(window, buffer, col_limit);
                        } else {
                                print_truncated(window, "Press ESC key to exit.", col_limit);
                        }
                }
        }

        fclose(file);
        delwin(window);
        delwin(frame);
        endwin();

        return 0;
}