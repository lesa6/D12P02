#include <ncurses.h>
#include <stdio.h>

#define WIDTH 80
#define HEIGHT 25
#define SPEED_STEP 50

void game(int cells[HEIGHT][WIDTH]);
int neighbors_count(int cells[HEIGHT][WIDTH], int row, int cell);
void draw(int cells[HEIGHT][WIDTH]);
int input(int cells[HEIGHT][WIDTH]);
void change_speed(int button, int *speed, int *life);

int main() {
    int cells[HEIGHT][WIDTH];
    int speed = 300;
    int life = 1;

    if (input(cells) == 0) {
        printf("n/a");
    } else {
        if (freopen("/dev/tty", "r", stdin) == NULL)
            printf("n/a");
        else {
            initscr();
            noecho();
            cbreak();
            curs_set(0);

            while (life) {
                draw(cells);
                timeout(speed);
                game(cells);

                int button = getch();
                change_speed(button, &speed, &life);
            }
            endwin();
        }
    }

    return 0;
}

int neighbors_count(int cells[HEIGHT][WIDTH], int row, int cell) {
    int count = 0;
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (!(i == 0 && j == 0)) {
                count += cells[(row + i + HEIGHT) % HEIGHT][(cell + j + WIDTH) % WIDTH];
            }
        }
    }
    return count;
}

void game(int cells[HEIGHT][WIDTH]) {
    int cells_new[HEIGHT][WIDTH];

    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            int neighbors = neighbors_count(cells, i, j);
            if (cells[i][j] == 1) {
                cells_new[i][j] = (neighbors == 2 || neighbors == 3) ? 1 : 0;
            } else {
                cells_new[i][j] = (neighbors == 3) ? 1 : 0;
            }
        }
    }

    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            cells[i][j] = cells_new[i][j];
        }
    }
}

int input(int cells[HEIGHT][WIDTH]) {
    int result = 1;

    for (int i = 0; i < HEIGHT && result == 1; i++) {
        for (int j = 0; j < WIDTH && result == 1; j++) {
            if (scanf("%1d", &cells[i][j]) != 1) {
                result = 0;
            }
            if (cells[i][j] != 0 && cells[i][j] != 1) {
                result = 0;
            }
        }
    }
    return result;
}

void draw(int cells[HEIGHT][WIDTH]) {
    clear();

    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (cells[i][j] == 1) {
                mvprintw(i, j, "o");
            } else {
                mvprintw(i, j, " ");
            }
        }
    }
    refresh();
}

void change_speed(int button, int *speed, int *life) {
    if (button == 'a' || button == 'A') {
        if (*speed - SPEED_STEP >= 10) {
            *speed -= SPEED_STEP;
        }
    } else if (button == 'z' || button == 'Z') {
        if (*speed + SPEED_STEP <= 2000) {
            *speed += SPEED_STEP;
        }
    }

    if (button == ' ') {
        *life = 0;
    }
}