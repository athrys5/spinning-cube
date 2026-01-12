#include <stdio.h>
#include <math.h>

#define HEIGHT 40;
#define WIDTH 80;
#define DISTANCE 5;

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

//todo: struct for a point

void rotateY(float x, float z, float angle_deg, float *new_x, float *new_z) {
    float angle_rad = angle_deg * (M_PI / 180); 
    float cos_a = cos(angle_rad); 
    float sin_a = sin(angle_rad); 
    
    *new_x = x * cos_a + z * sin_a;
    *new_z = -x * sin_a + z * cos_a;
}

void render2D(float x, float y, float z) {
	float x_screen = (x * DISTANCE) / (z + DISTANCE);
        float y_screen = (y * DISTANCE) / (z + DISTANCE);	
}

void clear_screen(){
	for(int i = 0; i < WIDTH; i++)
		for(int j = 0; j < HEIGHT; j++)
			screen[i][j] = ' ';
}

int main(){
	float angle = 0;
	while(1) {
		angle += 20;
		for(int i = 0; i < 8; i++) {
			float x = matrix[i][1];
			float z = matrix[i][3];
			float new_x, new_z;
			rotateY(x, z, angle, &new_x, &new_z);
		}
		break;
	}
	return 0;
}
