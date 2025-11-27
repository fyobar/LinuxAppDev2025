#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 6
#define SIZE (2*N + 1)

char maze[SIZE][SIZE];

int dx[] = {-1, 0, 1, 0};
int dy[] = {0, 1, 0, -1};


void init_maze() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            maze[i][j] = (i % 2 == 0 || j % 2 == 0) ? '#' : '.';
        }
    }
}

int valid(int x, int y) {
    return x >= 0 && x < N && y >= 0 && y < N;
}

void shuffle(int *array, int n) {
    for (int i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int tmp = array[i];
        array[i] = array[j];
        array[j] = tmp;
    }
}

void carve(int x, int y, int visited[N][N]) {
    visited[x][y] = 1;

    int dirs[4] = {0, 1, 2, 3};
    shuffle(dirs, 4);

    for (int i = 0; i < 4; i++) {
        int nx = x + dx[dirs[i]];
        int ny = y + dy[dirs[i]];

        if (valid(nx, ny) && !visited[nx][ny]) {
            int wallX = 2 * x + 1 + dx[dirs[i]];
            int wallY = 2 * y + 1 + dy[dirs[i]];
            maze[wallX][wallY] = '.';

            carve(nx, ny, visited);
        }
    }
}

void show() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            putchar(maze[i][j]);
        }
        putchar('\n');
    }
}


int main() {
    srand(time(NULL));

    init_maze();

    int visited[N][N] = {0};

    carve(0, 0, visited);
    show();

    return 0;
}
