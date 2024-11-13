#include <iostream>
#include <graphics.h>
using namespace std;

struct Point {
    int x, y;
    int code[4];
};

void drawWindow() {
    rectangle(150, 100, 450, 350);
}

void drawLine(Point p1, Point p2) {
    line(p1.x, p1.y, p2.x, p2.y);
}

Point setCode(Point p) {
    p.code[0] = (p.y < 100); // Top
    p.code[1] = (p.y > 350); // Bottom
    p.code[2] = (p.x > 450); // Right
    p.code[3] = (p.x < 150); // Left
    return p;
}

bool isVisible(Point p1, Point p2) {
    int outcode1 = (p1.code[0] | p1.code[1] | p1.code[2] | p1.code[3]);
    int outcode2 = (p2.code[0] | p2.code[1] | p2.code[2] | p2.code[3]);
    int common = (p1.code[0] & p2.code[0]) | (p1.code[1] & p2.code[1]) |
                 (p1.code[2] & p2.code[2]) | (p1.code[3] & p2.code[3]);

    if (outcode1 == 0 && outcode2 == 0) return true;  // Completely inside
    if (common != 0) return false;                    // Completely outside
    return true;                                      // Partially visible
}

Point clip(Point p1, Point p2) {
    float m = (float)(p2.y - p1.y) / (p2.x - p1.x);
    Point p = p1;

    if (p1.code[3]) p = {150, p1.y + m * (150 - p1.x)};       // Left
    else if (p1.code[2]) p = {450, p1.y + m * (450 - p1.x)};  // Right
    else if (p1.code[0]) p = {p1.x + (100 - p1.y) / m, 100};  // Top
    else if (p1.code[1]) p = {p1.x + (350 - p1.y) / m, 350};  // Bottom

    return setCode(p);
}

int main() {
    int gd = DETECT, gm;
    Point p1, p2;
    cout << "Enter x1 y1: "; cin >> p1.x >> p1.y;
    cout << "Enter x2 y2: "; cin >> p2.x >> p2.y;

    initgraph(&gd, &gm, "");
    drawWindow();
    delay(500);
    drawLine(p1, p2);
    delay(500);

    p1 = setCode(p1);
    p2 = setCode(p2);

    if (isVisible(p1, p2)) {
        if ((p1.code[0] | p1.code[1] | p1.code[2] | p1.code[3]) ||
            (p2.code[0] | p2.code[1] | p2.code[2] | p2.code[3])) {
            p1 = clip(p1, p2);
            p2 = clip(p2, p1);
        }
        cleardevice();
        drawWindow();
        drawLine(p1, p2);
    }

    delay(3000);
    closegraph();
    return 0;
}
