#include "dp_advanced.h"

int c[] = {0, 1, 2, 3, 4};

void solve() {
    for (int i = 0; i < 4; i++) {
        drawQ.addRectangleNode(25 + i, to_string(c[i + 1]), -1.25 + 0.5 * i, -1.2, "lightgray", "draw");
    }
    dp[0][0] = 1;
    for (int j = 0; j <= 5; j++) {
        drawQ.addRectangleNode(j, to_string(dp[0][j]), -1.75, -2.5 - j * 0.5, "white", "draw");
    }
    for (int i = 1; i <= 4; i++) {
        for (int j = 0; j <= 4; j++) {
            dp[i][j] = dp[i - 1][j];
            if (j >= c[i])
                dp[i][j] += dp[i][j - c[i]];
            if (dp[i][j] == 0) {
                drawQ.addRectangleNode(i * 5 + j, to_string(dp[i][j]), -1.75 + 0.5 * i, -2.5 - j * 0.5, "white", "draw");
            }
            else {
                drawQ.addRectangleNode(i * 5 + j, to_string(dp[i][j]), -1.75 + 0.5 * i, -2.5 - j * 0.5, "lightgray", "draw");
            }
        }
    }
    drawQ.addRectangleNode(4 * 5 + 4, to_string(dp[4][4]), -1.75 + 0.5 * 4, -2.5 - 0.5 * 4, "darkgray", "draw", 2, "text = white");
}

int main() {
    solve();

    drawQ.draw();
}
