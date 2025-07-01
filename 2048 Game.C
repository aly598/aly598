#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 4

void initialize(int (*grid)[SIZE][SIZE]);
void printGrid(int (*grid)[SIZE][SIZE]);
void spawnTile(int (*grid)[SIZE][SIZE]);
void move(int (*grid)[SIZE][SIZE], int direction, int *score);
void processLine(int *line, int *score);
int isGameOver(int (*grid)[SIZE][SIZE]);
void copyGrid(int (*src)[SIZE][SIZE], int (*dest)[SIZE][SIZE]);

int main() {
    int grid[SIZE][SIZE], undoGrid[SIZE][SIZE];
    int score = 0, undoScore = 0;
    int moveDir;

    srand(time(NULL));
    initialize(&grid);

    while (!isGameOver(&grid)) {
        printGrid(&grid);
        printf("Score: %d\n", score);
        printf("Enter move (1=Up, 2=Down, 3=Left, 4=Right, 5=Undo, 6=Reset): ");
        scanf("%d", &moveDir);

        if (moveDir >= 1 && moveDir <= 4) {
            // Save current state for undo
            copyGrid(&grid, &undoGrid);
            undoScore = score;

            move(&grid, moveDir, &score);
            spawnTile(&grid);
        } else if (moveDir == 5) {
            copyGrid(&undoGrid, &grid);
            score = undoScore;
            printf("Undo performed.\n");
        } else if (moveDir == 6) {
            initialize(&grid);
            score = 0;
            printf("Game reset.\n");
        } else {
            printf("Invalid input! Use 1-6.\n");
        }
    }

    printGrid(&grid);
    printf("Game Over! Final Score: %d\n", score);
    return 0;
}

void initialize(int (*grid)[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            (*grid)[i][j] = 0;

    spawnTile(grid);
    spawnTile(grid);
}

void printGrid(int (*grid)[SIZE][SIZE]) {
    printf("\n-------------------------\n");
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if ((*grid)[i][j] == 0)
                printf("  .   ");
            else
                printf("%4d  ", (*grid)[i][j]);
        }
        printf("\n");
    }
    printf("-------------------------\n");
}

void spawnTile(int (*grid)[SIZE][SIZE]) {
    int emptyCells[SIZE * SIZE][2];
    int count = 0;

    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            if ((*grid)[i][j] == 0) {
                emptyCells[count][0] = i;
                emptyCells[count][1] = j;
                count++;
            }

    if (count == 0) return;

    int index = rand() % count;
    int row = emptyCells[index][0];
    int col = emptyCells[index][1];
    (*grid)[row][col] = (rand() % 10 == 0) ? 4 : 2;
}

void processLine(int *line, int *score) {
    int temp[SIZE] = {0}, merged[SIZE] = {0};
    int idx = 0;

    for (int i = 0; i < SIZE; i++) {
        if (line[i] == 0) continue;

        if (temp[idx] == 0) {
            temp[idx] = line[i];
        } else if (temp[idx] == line[i] && merged[idx] == 0) {
            temp[idx] *= 2;
            *score += temp[idx];
            merged[idx] = 1;
        } else {
            idx++;
            temp[idx] = line[i];
        }
    }

    for (int i = 0; i < SIZE; i++) {
        line[i] = temp[i];
    }
}

void move(int (*grid)[SIZE][SIZE], int direction, int *score) {
    int temp[SIZE];

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (direction == 1)      temp[j] = (*grid)[j][i];             // Up
            else if (direction == 2) temp[j] = (*grid)[SIZE - 1 - j][i];  // Down
            else if (direction == 3) temp[j] = (*grid)[i][j];             // Left
            else if (direction == 4) temp[j] = (*grid)[i][SIZE - 1 - j];  // Right
        }

        processLine(temp, score);

        for (int j = 0; j < SIZE; j++) {
            if (direction == 1)      (*grid)[j][i] = temp[j];
            else if (direction == 2) (*grid)[SIZE - 1 - j][i] = temp[j];
            else if (direction == 3) (*grid)[i][j] = temp[j];
            else if (direction == 4) (*grid)[i][SIZE - 1 - j] = temp[j];
        }
    }
}

int isGameOver(int (*grid)[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            if ((*grid)[i][j] == 0)
                return 0;

    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE - 1; j++) {
            if ((*grid)[i][j] == (*grid)[i][j + 1] || (*grid)[j][i] == (*grid)[j + 1][i])
                return 0;
        }

    return 1;
}

void copyGrid(int (*src)[SIZE][SIZE], int (*dest)[SIZE][SIZE]) { 
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            (*dest)[i][j] = (*src)[i][j];
}`