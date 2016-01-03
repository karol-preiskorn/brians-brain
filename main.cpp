/**
* Brian's Brain
*
* Rules:
* -------
* Each cell has three possible states: passive, active, and semi-active.
* If a cell is active, it goes to semi-active state on the next step
* If a cell is semi-active, it becomes passive on the next step
* If a cell is passive, it becomes active if and only if it has exactly 2 active neighbors
*
**/
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "winbgi2.h"

void main() {

	printf("Brian's Brain automate \n");
	printf("==================-===\n\n");
	printf("Rules:\n");
	printf("* Each cell has three possible states: passive, active, and semi-active.\n");
	printf("* If a cell is active, it goes to semi-active state on the next step\n");
	printf("* If a cell is semi-active, it becomes passive on the next step\n");
	printf("* If a cell is passive, it becomes active if and only if it has exactly 2 active neighbors\n\n");

	const int v_widht=300;
	const int v_hight=300;
	int v_state=0;

	graphics(v_widht, v_hight);	// init

	// variables
	int range_min = 0;
	int range_max = 100;
	int v_cell_color = 0;
	int v_time=100;

	// cells coloring
	int v_color_active = 130;
	int v_color_semi_active = 220;
	int v_color_passive = 0;

	// matrix coordinates
	int x=0;
	int y=0;
	int t=0;

	// matrix init
	int matrix[v_widht][v_hight];
	int matrix_next_step[v_widht][v_hight];

	// generate random enviroment
	for(x = 0; x < v_widht; x++) {
		for(y = 0; y < v_hight; y++ ){			   
			// warning C4244: '=' : conversion from 'double' to 'int', possible loss of data	
			v_state = (double)rand() / (RAND_MAX + 1) * (range_max - range_min)	+ range_min;
			if(v_state >= 0 && v_state < 33) {
				v_cell_color = v_color_passive; // pasive
				}
			if(v_state >= 33 && v_state < 66) {
				v_cell_color = v_color_active; // active
				}
			if(v_state >= 66 && v_state <= 100) { 
				v_cell_color = v_color_semi_active; // semi-active
				}

			//printf("Put cell (%d, %d) in state %d\n", x, y, v_cell_color);
			matrix[x][y] = v_cell_color;
			putpixel(x, y, v_cell_color);
			}
		}

	// simulate enviroment t times 
	for(t = 0; t < v_time; t++) {
		for(x = 0; x < v_widht; x++) {
			for(y = 0; y < v_hight; y++){
				if(matrix[x][y] != v_color_active && matrix[x][y] != v_color_passive && matrix[x][y] != v_color_semi_active) {
					printf ("\nColor error! Time %d, Cell (%d, %d) color %d \n", t, x, y, matrix[x][y]);
					wait();
					exit(1);
					}
				// If a cell is active, it goes to semi-active state on the next step
				if(matrix[x][y] == v_color_active) {		   
					matrix_next_step[x][y] = v_color_semi_active; 
					}
				// If a cell is semi-active, it becomes passive on the next step
				if(matrix[x][y] == v_color_semi_active) {		   
					matrix_next_step[x][y] = v_color_passive; 
					}
				// If a cell is passive, it becomes active if and only if it has exactly 2 active neighbors
				if(matrix[x][y] == v_color_passive){
					int	l_2_active = 0; 
					// vertical and horizontal
					if(matrix[x+1][y] == v_color_active) {
						l_2_active++;
						}
					if(matrix[x-1][y] == v_color_active) {
						l_2_active++;
						} 
					if(matrix[x][y+1] == v_color_active) {
						l_2_active++;
						}
					if(matrix[x][y-1] == v_color_active) {
						l_2_active++;
						}
					// diagonal

					if(matrix[x-1][y+1] == v_color_active) {
						l_2_active++;
						}
					if(matrix[x+1][y+1] == v_color_active) {
						l_2_active++;
						}
					if(matrix[x-1][y-1] == v_color_active) {
						l_2_active++;
						}
					if(matrix[x+1][y-1] == v_color_active) {
						l_2_active++;
						}


					// set active cell
					if( l_2_active == 2 ) {
						matrix_next_step[x][y] = v_color_active; 
						} else {
							matrix_next_step[x][y] = matrix[x][y];
						}
					}
				// printf("Put cell (%d, %d) in state %d\n", x, y, matrix_next_step[x][y]);

				}

			}
		// print cells - generate enviroment
		int l_active_count = 0;
		int l_semi_active_count = 0;
		int l_passive_count = 0;

		for(x = 0; x < v_widht; x++) {
			for(y = 0; y < v_hight; y++){
				// printf("Put cell (%d, %d) in state %d\n", x, y, v_cell_color);
				// rewrite to old array
				matrix[x][y] = matrix_next_step[x][y];
				// print graph
				putpixel(x, y, matrix[x][y]);
				if (matrix[x][y] == v_color_active) l_active_count++; 
				if (matrix[x][y] == v_color_semi_active) l_semi_active_count++; 
				if (matrix[x][y] == v_color_passive) l_passive_count++; 
				}
			}

		printf("End of step %d sum of active %d, semi-active %d, passive %d\n", t, l_active_count, l_semi_active_count, l_passive_count);
		}
	printf("End of program\n");
	wait();
	}