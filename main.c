#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include <stdlib.h>

#define HEIGHT 40 
#define WIDTH 80
#define DISTANCE 10.0
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

int edges[12][2] = {
    // Back face (z = -1)
    {0, 1}, {1, 2}, {2, 3}, {3, 0},
    // Front face (z = 1)
    {4, 5}, {5, 6}, {6, 7}, {7, 4},
    // Connection between faces
    {0, 4}, {1, 5}, {2, 6}, {3, 7}
};

void clear(){
	printf("\033[2J\033[H");
	fflush(stdout);
}

void draw_line(int x0, int y0, int x1, int y1) {
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;
    int err = dx - dy;
    
    while(1) {
	if(y0 >= 0 && y0 < HEIGHT && x0 >= 0 && x0 < WIDTH) {
            screen[y0][x0] = '*';
        }
        
        if(x0 == x1 && y0 == y1) break;
        
        int e2 = 2 * err;
        if(e2 > -dy) {
            err -= dy;
            x0 += sx;
        }
        if(e2 < dx) {
            err += dx;
            y0 += sy;
        }
    }
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
	*col = (int)(x_screen * SCALE * 2.0 + WIDTH/2);
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
		int screen_points[8][2];
		for(int i = 0; i < 8; i++) {
			float x = matrix[i][0];
			float y = matrix[i][1];
			float z = matrix[i][2];
			float new_x, new_z;
			int col = 0;
			int row = 0;
			rotateY(x, z, angle, &new_x, &new_z);
			get_screen_point(new_x, y, new_z, &col, &row);
			screen_points[i][0] = col;
			screen_points[i][1] = row;			
		}
		for(int i = 0; i < 12; i++) {
        		int v0 = edges[i][0];  
       			int v1 = edges[i][1];  
        
    			draw_line(screen_points[v0][0], screen_points[v0][1],
                      screen_points[v1][0], screen_points[v1][1]);
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
