#include "dp.h"

string convert(int x) {
    if (x == 0) {
        return "";
    }
    return to_string(x);
}

void drawdp() {
    for (int i = 0; i <= 4; i++) {
        if (i < 2) {
            dp[i] = i;
        }
        if (i + 1 <= 4) {
            dp[i + 1] += dp[i];
        }
        if (i + 2 <= 4) {
            dp[i + 2] += dp[i];
        }
    }
    for (int i = 0; i <= 4; i++) {
        if (i == 4) {
            drawQ.addRectangleNode(i, convert(dp[i]), -0.5 + 0.5 * i, 0, "darkgray", "draw", 2.0, "text = white");
        }
        else {
            drawQ.addRectangleNode(i, to_string(dp[i]), -0.5 + 0.5 * i, 0, "lightgray", "draw");
        }
    }
}

void solve() {
    drawdp();
    return;
    for (int i = 0; i <= 4; i++) {
        drawQ.addRectangleNode(i, convert(dp[i]), -0.5 + 0.5 * i, 0, "white", "draw");
    }
    for (int i = 0; i <= 4; i++) {
        if (i < 2) {
            drawQ.addRectangleNode(i, convert(dp[i]), -0.5 + 0.5 * i, 0, "lightgray", "draw = blue, thick");
            dp[i] = i;
            drawQ.increaseTimer();
        }
        drawQ.addRectangleNode(i, to_string(dp[i]), -0.5 + 0.5 * i, 0, "lightgray", "draw = blue, thick");
        if (i == 4) {
            drawQ.addRectangleNode(i, convert(dp[i]), -0.5 + 0.5 * i, 0, "darkgray", "draw = blue, thick", 2.0, "text = white");
        }
        drawQ.increaseTimer();
        if (i == 0) {
            drawQ.addRectangleNode(i, to_string(dp[i]), -0.5 + 0.5 * i, 0, "lightgray", "draw");
            continue;
        }
        if (i + 1 <= 4) {
            drawQ.addRectangleNode(i + 1, convert(dp[i + 1]), -0.5 + 0.5 * (i + 1), 0, "lightgray", "draw = red, thick");
            if (i + 2 <= 4) {
                drawQ.addRectangleNode(i + 2, convert(dp[i + 2]), -0.5 + 0.5 * (i + 2), 0, "lightgray", "draw = red, thick");
            }
            drawQ.addRectangleNode(i, convert(dp[i]), -0.5 + 0.5 * i, 0, "lightgray", "draw = blue, thick");
            drawQ.increaseTimer();
            dp[i + 1] += dp[i];
            drawQ.addRectangleNode(i + 1, convert(dp[i + 1]), -0.5 + 0.5 * (i + 1), 0, "lightgray", "draw = red, thick");
            if (i + 2 <= 4) {
                dp[i + 2] += dp[i];
                drawQ.addRectangleNode(i + 2, convert(dp[i + 2]), -0.5 + 0.5 * (i + 2), 0, "lightgray", "draw = red, thick");
            }
            drawQ.addRectangleNode(i, convert(dp[i]), -0.5 + 0.5 * i, 0, "lightgray", "draw = blue, thick");
            drawQ.increaseTimer();
            drawQ.addRectangleNode(i, convert(dp[i]), -0.5 + 0.5 * i, 0, "lightgray", "draw");
            drawQ.addRectangleNode(i + 1, convert(dp[i + 1]), -0.5 + 0.5 * (i + 1), 0, "lightgray", "draw");
            if (i + 2 <= 4) {
                drawQ.addRectangleNode(i + 2, convert(dp[i + 2]), -0.5 + 0.5 * (i + 2), 0, "lightgray", "draw");
            }
        }
        if (i == 4) {
            drawQ.addRectangleNode(i, convert(dp[i]), -0.5 + 0.5 * i, 0, "darkgray", "draw", 2.0, "text = white");
        }
    }

}

int main() {
    solve();

    drawQ.draw();
}
