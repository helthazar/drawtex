#include "advanced_geometry.h"

double polygon_triangle_area(vector<point> v, point p) {
    int n = (int) v.size();
    double sum = 0;

    for (int i = 0; i < n; i++){
    	int j = (i + 1) % n;
        double cross = point_cross(p, v[i], v[j]);
        sum += cross;

        vector<point> tr = {p, v[i], v[j]};
        if (cross < 0) {
            drawQ.addPolygonNode(tr, "red", "green!50", 0.5);
        }
        else {
            drawQ.addPolygonNode(tr, "red", "red!50", 0.5);
        }
        drawQ.increaseTimer();
    }

    return fabs(sum) / 2.0;
}

void solve() {
    vector<point> v;
    for (int i = 0; i < x.size(); i++) {
        v.push_back(point(x[i], y[i]));
    }
    drawQ.addPolygonNode(v, "blue", "white!20", 0.5);

    point p = point(0.3, 1);
    drawQ.addNode()

    polygon_triangle_area(v, p);
}

int main() {
    solve();

    drawQ.draw();
}
