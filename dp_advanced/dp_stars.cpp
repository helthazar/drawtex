#include "dp_advanced.h"

int a[] = {3, 4, 5, 2};

void solve() {
    for (int i = 0; i < 4; i++) {
        drawQ.addRectangleNode(20 + i, to_string(a[i]), -1.75 + 0.5 * i, -1, "lightgray", "draw");
    }

    for (int len = 0; len < 4; len++) {
        for (int i = 0; i + len < 4; i++) {
            int j = i + len;
            dp[i][j] = 0;
            for (int s = i + 1; s < j; s++) {
                dp[i][j] = max(dp[i][j], dp[i][s] + dp[s][j] + a[i] * a[j]);
            }
            if (dp[i][j] == 0) {
                drawQ.addRectangleNode(i * 4 + j, to_string(dp[i][j]), -1.75 + 0.5 * j, -2.5 - i * 0.5, "white", "draw");
            }
            else {
                drawQ.addRectangleNode(i * 4 + j, to_string(dp[i][j]), -1.75 + 0.5 * j, -2.5 - i * 0.5, "lightgray", "draw");
            }
        }
    }
    drawQ.addRectangleNode(0 * 4 + 3, to_string(dp[0][3]), -1.75 + 0.5 * 3, -2.5 - 0 * 0.5, "darkgray", "draw", 2, "text = white");
}

int main() {
    solve();

    drawQ.draw();
}
