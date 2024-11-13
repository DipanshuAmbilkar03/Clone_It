#include <iostream>
#include <graphics.h>
#include <cmath>
#include <dos.h> 

using namespace std;

int main()
{
    // Initialize graphics window
    initwindow(800, 500, "Sunrise Animation");

    // Set background color
    setbkcolor(LIGHTBLUE);
    cleardevice();

    // Draw mountains using polygons (triangles)
    setcolor(DARKGRAY);
    int mountain1[] = {100, 400, 250, 200, 400, 400};
    fillpoly(3, mountain1);
    int mountain2[] = {300, 400, 450, 150, 600, 400};
    fillpoly(3, mountain2);

    // Initial position of the sun
    int sun_x = 450, sun_y = 400;
    int sun_radius = 30;

    // Animate the sun rising
    for (int i = 0; i <= 250; i += 5) {
        cleardevice();  // Clear screen to update the scene

        // Redraw the background and mountains
        setbkcolor(LIGHTBLUE);
        setcolor(DARKGRAY);
        fillpoly(3, mountain1);
        fillpoly(3, mountain2);

        // Draw the sun rising
        setcolor(YELLOW);
        setfillstyle(SOLID_FILL, YELLOW);
        fillellipse(sun_x, sun_y - i, sun_radius, sun_radius);

        delay(100);  // Delay to slow down the animation
    }

    // Keep the window open until a key is pressed
    getch();
    closegraph();
    return 0;
}
