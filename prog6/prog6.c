#include <stdio.h>

#define WIDTH 60
#define HEIGHT 30

// 2D Character Buffer
char buffer[HEIGHT][WIDTH];

// Design a structure for a circle
struct Circle {
    int center_x;
    int center_y;
    int radius;
};

// Function 1: Initialize the 2D buffer with spaces
void init_buffer() {
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            buffer[y][x] = ' ';
        }
    }
}

// Function 2: Create a circle instance
struct Circle create_circle(int x, int y, int r) {
    struct Circle c;
    c.center_x = x;
    c.center_y = y;
    c.radius = r;
    return c;
}

// Function 3: Draw the circle into the 2D buffer
void draw_circle(struct Circle c) {
    // Loop through every pixel in our 2D buffer
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            
            // Terminal characters are typically twice as tall as they are wide.
            // Multiplying the x-distance by 0.5 compensates for this aspect ratio 
            // so our circle doesn't look like a stretched oval.
            float dx = (x - c.center_x) * 0.5f;
            float dy = (y - c.center_y);
            
            // Calculate distance squared from the center: a^2 + b^2 = c^2
            float distance_sq = (dx * dx) + (dy * dy);
            float radius_sq = c.radius * c.radius;
            
            // If the point is close to the circumference (radius_sq ± thickness margin), draw a '*'
            if (distance_sq >= radius_sq - c.radius && distance_sq <= radius_sq + c.radius) {
                buffer[y][x] = '*';
            }
        }
    }
}

// Function 4: Render the 2D buffer to the screen
void print_buffer() {
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            putchar(buffer[y][x]);
        }
        putchar('\n'); // Move to the next line after printing a row
    }
}

int main() {
    // 1. Initialize the blank canvas
    init_buffer();
    
    // 2. Setup the circle (center at x=30, y=15 with radius 12)
    struct Circle my_circle = create_circle(30, 15, 12);
    
    // 3. Draw the circle into the buffer
    draw_circle(my_circle);
    
    // 4. Render the buffer to the screen
    print_buffer();
    
    return 0;
}
