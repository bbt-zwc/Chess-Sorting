#include "Headfile.h"

#define ROWS 9
#define COLS 13
#define SQUARE_SIZE 27

typedef struct {
    int x;
    int y;
} Point;

Point centers[ROWS][COLS];

void Location(void) 
{
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            centers[i][j].x = j * SQUARE_SIZE;
            centers[i][j].y = i * SQUARE_SIZE;
        }
    }
}
