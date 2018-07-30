#include "dp_subsets.h"

const int INF = 1000000000;
int dp[1 << MAXN][MAXN];

void drawdp(int n, int t) {
    for (int mask = 0; mask < (1 << n); mask++) {
        string s = "";

        for (int i = 0; i < n; i++) {
            s.push_back('0' + ((mask >> i) & 1));

            string color = (dp[mask][i] != INF) ? "lightgray" : "white";
            string label = (dp[mask][i] != INF) ? to_string(dp[mask][i]) : "$\\infty$";
            drawQ.addRectangleNode(mask * n + i, label, -1.75 + 0.5 * i, 2 - 0.5 * mask, color, "draw");
        }
        reverse(s.begin(), s.end());
        drawQ.addNode((1 << n) * n + mask, "\\tiny \\alert{" + s + "}",  -2.5, 2 - 0.5 * mask);
    }
    for (int i = 0; i < n; i++) {
        drawQ.addNode((1 << n) * 2 * n + i, "\\tiny \\alert{" + to_string(i) + "}",  -1.75 + 0.5 * i, 2.5);

    }
}

int solve() {
    d[0][1] = d[1][0] = 4;
    d[0][2] = d[2][0] = 3;
    d[1][2] = d[2][1] = 2;

    int n = 3;
    int t = 3;
    for (int mask = 0; mask < (1 << n); mask++) {
        for (int i = 0; i < n; i++) {
            dp[mask][i] = INF;
        }
    }

    for (int i = 0; i < n; i++) {
        int mask = 1 << i;
        dp[mask][i] = 0;
    }

    if (t == 1) {
        drawdp(n, t);
    }

    for (int mask = 0; mask < (1 << n); mask++) {
        for (int i = 0; i < n; i++) {
            if (!(mask & (1 << i))) {
                continue;
            }

            for (int j = 0; j < n; j++) {
                if (mask & (1 << j)) {
                    continue;
                }

                int nmask = mask | (1 << j);
                dp[nmask][j] = min(dp[nmask][j], dp[mask][i] + d[i][j]);
            }
        }
    }

    if (t == 2) {
        drawdp(n, t);
    }

    int mask = (1 << n) - 1;
    int mindp = INF;

    for (int i = 0; i < n; i++) {
        mindp = min(mindp, dp[mask][i]);
    }

    if (t == 3) {
        drawdp(n, t);
    }

    return mindp;
}

int main() {
    solve();

    drawQ.draw();
}
