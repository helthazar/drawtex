#include "stl.h"

void solve() {
    double cy[] = {0, 0.5};

    vector<string> v = {"4", "43", "43", "314", "41", "415"};

    for (int k = 0; k < 2; k++) {
        double ysum = 0;
        for (int ki = 0; ki < 3; ki++) {
            int i = k * 3 + ki;
            int len = (int) v[i].length();
            double miny = 0;
            for (int j = 0; j < len; j++) {
                if (v[i][j] == '-') {
                    continue;
                }
                drawQ.addCircleNode(i * 10 + j + 1, to_string(v[i][j] - '0'), dx[j] + cx[k], ysum + dy[j] + cy[k], "lightgray", "draw");
                miny = min(miny, ysum + dy[j]);
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
