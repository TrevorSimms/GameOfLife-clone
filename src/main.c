#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef enum {
	false,
	true
}bool;

#define SCALE (50)
#define ROWS (1 * SCALE)
#define COLUMNS (2 * SCALE)
#define CELLBOUNDS ((ROWS-1) || (COLUMNS-1))
#define LOOPDELAY (1000000000)

#define addMargin(iter,margin) for(int i = 0; i < iter; i++) putchar(margin)

void renderScreen(const bool arr[ROWS][COLUMNS]) 
{
	for(int i = 0; i < ROWS; i++) {
		for(int j = 0; j < COLUMNS; j++) {
			if(arr[i][j] == true) putchar('#');
			else putchar(' ');
		}
		putchar('\n');
	}
}

bool evalCell(const bool arr[ROWS][COLUMNS], int index_r, int index_c) 
{
	int neighbors = 0;
	int bound_r = (index_r == (ROWS-1)) ? 2 : 3;
	int bound_c = (index_c == (COLUMNS-1)) ? 2 : 3;

	for(int i = (index_r == 0) ? 1 : 0; i < bound_r; i++) {
			for (int j = (index_c == 0) ? 1 : 0; j < bound_c; j++) {
				if((i == 1) && (j == 1)) continue;
				else if (arr[index_r-1+i][index_c-1+j] == true)
					neighbors++;
			}
	}
	if (arr[index_r][index_c] == true)
		return ((neighbors <= 3) && (neighbors >= 2)) ? true : false;
	return (neighbors == 3) ? true : false;
}

int main(void)
{
	bool cells[ROWS][COLUMNS];
	int speed, intensity;
	printf(
		"Conway's Game of Life!!!\n"
		"Best in FullScreen ;) \n"
		"Exit with [CTRL]+C\n"
	);
	while (true)
	{
		printf("How fast would you like it? (1-10): ");
		scanf("%d", &speed);
		if (((int)speed > 10) || ((int)speed < 1)) printf("Invalid argument. \n");
		else break;
	}
	while (true)
	{
		printf("And the intensity? (1-20): ");
		scanf("%d", &intensity);
		if ((intensity > 20) || (intensity < 1)) printf("Invalid argument. \n");
		else break;
	}

	srand(time(0));
	for(int i = 0; i < ROWS; i++)
		for(int j = 0; j < COLUMNS; j++)
			cells[i][j] = (rand() % intensity) == 1 ? true : false;
	
	renderScreen(cells);
	while (true)
	{
		addMargin(8, '\n');
		addMargin(COLUMNS, '=');
		putchar('\n');
		for(int i = 0; i < ROWS; i++)
			for(int j = 0; j < COLUMNS; j++)
				cells[i][j] = evalCell(cells, i, j);
		renderScreen(cells);
		addMargin(COLUMNS, '=');
		addMargin(8, '\n');
		for (long i = 0; i < LOOPDELAY/speed; i++);
	}
	
	return 0;
}
