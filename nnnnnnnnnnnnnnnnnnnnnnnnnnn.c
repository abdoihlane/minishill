#include <stdio.h>
#include <math.h>

// Forward declaration of struct to use in function pointer
struct Point;

// Define a function pointer type for distance calculation
typedef double (*DistanceFunc)(struct Point, struct Point);

// Define the struct
typedef struct Point {
    int x;
    int y;
    DistanceFunc distanceTo;
} Point;

// Function to calculate distance (outside struct, but used via pointer)
double calculateDistance(Point p1, Point p2) {
    int dx = p2.x - p1.x;
    int dy = p2.y - p1.y;
    return sqrt(dx * dx + dy * dy);
}

int main() {
    // Create two points and assign the function pointer
    Point a = {0, 0, calculateDistance};
    Point b = {3, 4, calculateDistance};

    // Call the function via the struct
    double distance = a.distanceTo(a, b);

    printf("Distance between points: %.2f\n", distance);

    return 0;
}
