//this code only show clipped part 
#include<iostream>
#include<graphics.h>
using namespace std;

struct PT {
    int x, y;
    char code[4];
};

void drawWindow() {
    rectangle(50, 150, 450, 350);  // Draw the clipping window (using rectangle function)
}

void drawLine(PT p1, PT p2) {
    line(p1.x, p1.y, p2.x, p2.y);  // Draw a line from p1 to p2
}

PT setCode(PT p) {
    PT temp = p;
    temp.code[0] = (p.y < 150) ? '1' : '0';  // Top
    temp.code[1] = (p.y > 350) ? '1' : '0';  // Bottom
    temp.code[2] = (p.x > 450) ? '1' : '0';  // Right
    temp.code[3] = (p.x < 50) ? '1' : '0';   // Left
    return temp;
}

bool isVisible(PT p1, PT p2) {
    return !(p1.code[0] == '1' || p1.code[1] == '1' || p1.code[2] == '1' || p1.code[3] == '1' ||
             p2.code[0] == '1' || p2.code[1] == '1' || p2.code[2] == '1' || p2.code[3] == '1');
}

PT resetEndPoint(PT p, PT p2) {
    PT temp = p;
    float m = (p2.x - p.x) ? (float)(p2.y - p.y) / (p2.x - p.x) : 0;
    float k = (p2.y - p.y) ? (float)(p2.x - p.x) / (p2.y - p.y) : 0;

    if (p.code[3] == '1') temp.x = 50, temp.y = p.y + m * (50 - p.x);  // Left
    else if (p.code[2] == '1') temp.x = 450, temp.y = p.y + m * (450 - p.x);  // Right
    else if (p.code[0] == '1') temp.y = 150, temp.x = p.x + k * (150 - p.y);  // Top
    else if (p.code[1] == '1') temp.y = 350, temp.x = p.x + k * (350 - p.y);  // Bottom

    return temp;
}

int main() {
    PT p1, p2;
    cout << "\nEnter x1 and y1: ";
    cin >> p1.x >> p1.y;
    cout << "Enter x2 and y2: ";
    cin >> p2.x >> p2.y;

    int gd = DETECT, gm;
    initgraph(&gd, &gm, NULL);

    drawWindow();  // Draw the clipping window

    p1 = setCode(p1);
    p2 = setCode(p2);

    if (isVisible(p1, p2)) {
        drawLine(p1, p2);  // If both points are inside the window, draw the line
    } else {
        PT p3 = resetEndPoint(p1, p2);
        PT p4 = resetEndPoint(p2, p1);
        drawLine(p3, p4);  // Clip the line and draw the new line
    }

    delay(5000);  // Wait for 5 seconds
    closegraph();
    return 0;
}
