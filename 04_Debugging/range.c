#include <stdio.h>
#include <stdlib.h>

void display(int value) {
    printf("%d\n", value);
}


void range(int start, int stop, int step) {
    int size = 0;
    
    if ((step > 0 && start < stop) || (step < 0 && start > stop)) {
        size = (stop - start + step - (step > 0 ? 1 : -1)) / step;
    }
    
    for (int i = 0, val = start; i < size; i++, val += step) {
        display(val);
    }
}


int main(int argc, char* argv[]) {
    int start = 0, stop = 0, step = 1;

    if (argc == 2) {
        stop = atoi(argv[1]);
    } else if (argc == 3) {
        start = atoi(argv[1]);
        stop = atoi(argv[2]);
    } else if (argc == 4) {
        start = atoi(argv[1]);
        stop = atoi(argv[2]);
        step = atoi(argv[3]);
    } else {
        fprintf(stderr, "Usage: %s stop\n", argv[0]);
        fprintf(stderr, "   or: %s start stop\n", argv[0]);
        fprintf(stderr, "   or: %s start stop step\n", argv[0]);
        return 1;
    }
    
    range(start, stop, step);
    
    return 0;
}

