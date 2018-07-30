#include "stl.h"

void solve() {
    double cy[] = {0, -0.75};

    int clen[] = {3, 2};

    vector<string> k = {"1", "31", "31", "213", "32"};
    vector<string> v = {"2", "42", "43", "534", "45"};

    for (int c = 0; c < 2; c++) {
        double ysum = 0;
        for (int ki = 0; ki < clen[c]; ki++) {
            int i = c * clen[0] + ki;
            int len = (int) v[i].length();
            double miny = 0;
            for (int j = 0; j < len; j++) {
                if (v[i][j] == '-') {
                    continue;
                }
                drawQ.addCircleNode(i * 10 + j + 1, to_string(k[i][j] - '0') + " \\nodepart\{lower\} " + to_string(v[i][j] - '0'), mx[j] + cx[c], ysum + my[j] + cy[c], "lightgray", "draw", 0.65);
                miny = min(miny, ysum + my[j]);
            }
            for (int j = 1; j < len; j++) {
                if (v[i][j] == '-') {
                    continue;
                }
                bool isRed = (len == 2 && j >= 1 || len >= 4 && j >= 3);
                drawQ.addEdge(i * 10 + (j + 1) / 2, i * 10 + j + 1, isRed ? "red" : "black", true);
            }
            ysum = miny - addy;
        }
    }
}

int main() {
    solve();

    drawQ.draw();
}
