#include "dp.h"

void solve() {
    dp[0] = 0;
    dp[1] = 1;

    for (int i = 2; i <= 4; i++) {
        dp[i] = dp[i - 1] + dp[i - 2];
    }
    for (int i = 0; i <= 4; i++) {
        drawQ.addRectangleNode(i, "", -0.5 + 0.5 * i, 0, "white", "draw");
    }
    for (int i = 0; i <= 4; i++) {
        drawQ.addRectangleNode(i, "", -0.5 + 0.5 * i, 0, "lightgray", "draw = blue, thick");
        drawQ.increaseTimer();
        if (i >= 2) {
            drawQ.addRectangleNode(i - 2, to_string(dp[i - 2]), -0.5 + 0.5 * (i - 2), 0, "lightgray", "draw = red, thick");
            drawQ.addRectangleNode(i - 1, to_string(dp[i - 1]), -0.5 + 0.5 * (i - 1), 0, "lightgray", "draw = red, thick");
            drawQ.increaseTimer();
        }
        if (i == 4) {
            drawQ.addRectangleNode(i, to_string(dp[i]), -0.5 + 0.5 * i, 0, "darkgray", "draw = blue, thick", 2.0, "text = white");
        }
        else {
            drawQ.addRectangleNode(i, to_string(dp[i]), -0.5 + 0.5 * i, 0, "lightgray", "draw = blue, thick");
        }
        drawQ.increaseTimer();
        if (i >= 2) {
            drawQ.addRectangleNode(i - 2, to_string(dp[i - 2]), -0.5 + 0.5 * (i - 2), 0, "lightgray", "draw");
            drawQ.addRectangleNode(i - 1, to_string(dp[i - 1]), -0.5 + 0.5 * (i - 1), 0, "lightgray", "draw");
        }
        if (i == 4) {
            drawQ.addRectangleNode(i, to_string(dp[i]), -0.5 + 0.5 * i, 0, "darkgray", "draw", 2.0, "text = white");
        }
        else {
            drawQ.addRectangleNode(i, to_string(dp[i]), -0.5 + 0.5 * i, 0, "lightgray", "draw");
        }
    }

}

int main() {
    solve();

    drawQ.draw();
}
