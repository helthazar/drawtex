#include "dp_advanced.h"

int a[] = {0, 2, 8, 7};
int w[] = {0, 1, 4, 2};

void solve() {
    for (int i = 0; i < 3; i++) {
        drawQ.addRectangleNode(20 + i, to_string(a[i + 1]), -1.25 + 0.5 * i, -0.5, "lightgray", "draw");
        drawQ.addRectangleNode(25 + i, to_string(w[i + 1]), -1.25 + 0.5 * i, -1.2, "lightgray", "draw");
    }
    int maxdp = 0;
    for (int j = 0; j <= 4; j++) {
        drawQ.addRectangleNode(j, to_string(dp[0][j]), -1.75, -2.5 - j * 0.5, "white", "draw");
    }
    for (int i = 1; i <= 3; i++) {
        for (int j = 0; j <= 4; j++) {
            dp[i][j] = dp[i - 1][j];
            if (j >= w[i])
                dp[i][j] = max(dp[i][j], dp[i - 1][j - w[i]] + a[i]);
            maxdp = max(maxdp, dp[i][j]);
            if (dp[i][j] == 0) {
                drawQ.addRectangleNode(i * 5 + j, to_string(dp[i][j]), -1.75 + 0.5 * i, -2.5 - j * 0.5, "white", "draw");
            }
            else {
                drawQ.addRectangleNode(i * 5 + j, to_string(dp[i][j]), -1.75 + 0.5 * i, -2.5 - j * 0.5, "lightgray", "draw");
            }
        }
    }
    drawQ.addRectangleNode(3 * 5 + 4, to_string(dp[3][4]), -1.75 + 0.5 * 3, -2.5 - 0.5 * 4, "darkgray", "draw", 2, "text = white");
}

int main() {
    solve();

    drawQ.draw();
}
