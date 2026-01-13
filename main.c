#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include <stdlib.h>

#define HEIGHT 40
#define WIDTH 80
#define DISTANCE 5.0
#define SCALE 10.0

char screen[HEIGHT][WIDTH];

int matrix[8][3] = {
    {-1, -1, -1}, // 0: back bottom left
    {1, -1, -1},  // 1: back bottom right
    {1, 1, -1},   // 2: back top right
    {-1, 1, -1},  // 3: back top left
    {-1, -1, 1},  // 4: front bottom left
    {1, -1, 1},   // 5: front bottom right
    {1, 1, 1},    // 6: front top right
    {-1, 1, 1}    // 7: front top left
};

void clear(){
	printf("\033[2J\033[H");
	fflush(stdout);
}

void rotateY(float x, float z, float angle_deg, float *new_x, float *new_z) {
    float angle_rad = angle_deg * (M_PI / 180); 
    float cos_a = cos(angle_rad); 
    float sin_a = sin(angle_rad); 
    
    *new_x = x * cos_a + z * sin_a;
    *new_z = -x * sin_a + z * cos_a;
}

void get_screen_point(float x, float y, float z, int *col, int *row) {
	float x_screen = (x * DISTANCE) / (z + DISTANCE);
        float y_screen = (y * DISTANCE) / (z + DISTANCE);	
	*col = (int)(x_screen * SCALE + WIDTH/2);
        *row = (int)(-y_screen * SCALE + HEIGHT/2); 		
}

void clear_screen(){
	for(int i = 0; i < HEIGHT; i++)
		for(int j = 0; j < WIDTH; j++)
			screen[i][j] = ' ';
}

int main(){
	float angle = 0;
	while(1) {
		clear_screen();
		for(int i = 0; i < 8; i++) {
			float x = matrix[i][0];
			float y = matrix[i][1];
			float z = matrix[i][2];
			float new_x, new_z;
			int col = 0;
			int row = 0;
			rotateY(x, z, angle, &new_x, &new_z);
			get_screen_point(new_x, y, new_z, &col, &row);
			if(row >= 0 && row < HEIGHT && col >= 0 && col < WIDTH) screen[row][col] = '*';
		}
		
		system("clear");	

		for(int i = 0; i < HEIGHT; i++){
			for(int j = 0; j < WIDTH; j++){
				printf("%c", screen[i][j]);
			}
			printf("\n");	
		}
		usleep(100000);
		angle += 10;
	}
	return 0;
}
