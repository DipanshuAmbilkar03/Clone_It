#include <iostream>
#include <graphics.h>
#include <vector>
#include <algorithm>

using namespace std;

class ConcavePolygon {
    vector<int> x, y;
    int n;

public:
    ConcavePolygon(int vertices) : n(vertices), x(vertices), y(vertices) {}

    void readVertices() {
        cout << "Enter the vertices (x y): \n";
        for (int i = 0; i < n; ++i) {
            cin >> x[i] >> y[i];
        }
    }

    void drawAndFill() {
        int gd = DETECT, gm;
        initgraph(&gd, &gm, "");

        int ymin = *min_element(y.begin(), y.end());
        int ymax = *max_element(y.begin(), y.end());

        // Draw polygon outline
        for (int i = 0; i < n; ++i) {
            line(x[i], y[i], x[(i + 1) % n], y[(i + 1) % n]);
        }

        // Scanline fill
        for (int yy = ymin; yy <= ymax; ++yy) {
            vector<int> intersections;

            // Find intersections with scanline
            for (int i = 0; i < n; ++i) {
                int x1 = x[i], y1 = y[i];
                int x2 = x[(i + 1) % n], y2 = y[(i + 1) % n];

                if (y1 != y2 && yy >= min(y1, y2) && yy <= max(y1, y2)) {
                    int xi = x1 + (yy - y1) * (x2 - x1) / (y2 - y1);
                    intersections.push_back(xi);
                }
            }

            // Sort and fill between pairs of intersections
            sort(intersections.begin(), intersections.end());
            for (size_t i = 0; i < intersections.size(); i += 2) {
                if (i + 1 < intersections.size()) {
                    line(intersections[i], yy, intersections[i + 1], yy);
                }
            }
            delay(20);
        }

        closegraph();
    }
};

int main() {
    int vertices;
    cout << "Enter the number of vertices of the polygon: ";
    cin >> vertices;

    if (vertices < 3) {
        cerr << "A polygon must have at least 3 vertices." << endl;
        return 1;
    }

    ConcavePolygon poly(vertices);
    poly.readVertices();
    poly.drawAndFill();

    return 0;
}
