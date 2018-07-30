#include "graph_theory_advanced.h"

void floyd() {
    for (int k = 0; k < 3; k++) {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (d[i][j] <= d[i][k] + d[k][j]) {
                    if (d[i][j] == 0)
                        drawQ.addRectangleNode(9 * (k + 1) + 3 * i + j, "0", -1 + 0.5 * j, -1.75 - 0.5 * i - 1.7 * (k + 1), "white", "draw");
                    else if (d[i][j] == INF)
                        drawQ.addRectangleNode(9 * (k + 1) + 3 * i + j, "\\tiny $\\infty$", -1 + 0.5 * j, -1.75 - 0.5 * i - 1.7 * (k + 1), "white", "draw");
                    else
                        drawQ.addRectangleNode(9 * (k + 1) + 3 * i + j, to_string(d[i][j]), -1 + 0.5 * j, -1.75 - 0.5 * i - 1.7 * (k + 1), "lightgray", "draw");
                }
            }
        }
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (d[i][j] > d[i][k] + d[k][j]) {
                    d[i][j] = d[i][k] + d[k][j];
                    drawQ.addRectangleNode(9 * (k + 1) + 3 * i + j, to_string(d[i][j]), -1 + 0.5 * j, -1.75 - 0.5 * i - 1.7 * (k + 1), "darkgray", "draw", 2.0, "text = white");
                }
            }
        }
    }
}

void solve() {
    d[0][1] = 3;
    d[0][2] = 5;
    d[1][0] = 6;
    d[1][2] = 1;
    d[2][0] = 2;
    d[2][1] = INF;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (d[i][j] == 0)
                drawQ.addRectangleNode(3 * i + j, "0", -1 + 0.5 * j, -1.75 - 0.5 * i, "white", "draw");
            else if (d[i][j] == INF)
                drawQ.addRectangleNode(3 * i + j, "\\tiny $\\infty$", -1 + 0.5 * j, -1.75 - 0.5 * i, "white", "draw");
            else
                drawQ.addRectangleNode(3 * i + j, to_string(d[i][j]), -1 + 0.5 * j, -1.75 - 0.5 * i, "lightgray", "draw");
        }
    }

    floyd();
}

int main() {
    solve();

    drawQ.draw();
}
