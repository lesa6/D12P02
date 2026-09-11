#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>

#define WIDTH 80
#define HEIGHT 25
#define STEP 50
#define MAX_SPEED 1000
#define MIN_SPEED 10

//Чтение матрицы
//Отрисовка поля
//Чтение ввода
void game(int *cells[HEIGHT][WIDTH]);
int neighbors_count(int cells[HEIGHT][WIDTH], int row, int cell);


int main(){
    int cells[WIDTH][HEIGHT];// сюда массив надо записать
    int delay = 15;

    initscr();
    noecho();
    cbreak();
    curs_set(0);
         
    while(1){
        //Отрисовка 
        timeout(delay);
        //считывание ввода у пользователей

        game(cells);
    }

    return 0;
}

int neighbors_count(int cells[HEIGHT][WIDTH], int row, int cell) {
    int count = 0;
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (i != 0 && j != 0){
                count += cells[(row + i + HEIGHT) % HEIGHT][(cell + j + WIDTH) % WIDTH];
            }
        }
    }
    return count;
}

void game(int *cells[HEIGHT][WIDTH]) {
    int cells_new[HEIGHT][WIDTH];

    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            int neighbors = count_neighbors(cells, i, j);

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