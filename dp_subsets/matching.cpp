#include "dp_subsets.h"

int dp[1 << MAXN];

void solve() {
    d[0][1] = d[1][0] = 1;
    d[0][2] = d[2][0] = 1;
    d[1][2] = d[2][1] = 1;
    d[2][3] = d[3][2] = 1;

    dp[0] = 1;
    int maxw = 0;

    int n = 4;
    for (int mask = 0; mask < (1 << n); mask++) {
        string s = "";

        for (int i = 0; i < n; i++) {
            s += '0' + ((mask >> i) & 1);

            if (!(mask & (1 << i))) {
                continue;
            }

            for (int j = 0; j < n; j++) {
                if (!(mask & (1 << j))) {
                    continue;
                }

                int smask = mask ^ (1 << i) ^ (1 << j);
                dp[mask] = max(dp[mask], dp[smask] & d[i][j]);
            }
        }
        reverse(s.begin(), s.end());

        int ilen = mask % (1 << (n - 1));
        int jlen = mask / (1 << (n - 1));

        string color = (dp[mask] != 0) ? "lightgray" : "white";
        drawQ.addRectangleNode(mask, to_string(dp[mask]), -1.75 + 1.75 * jlen, -2 - 0.5 * ilen, color, "draw");
        drawQ.addNode((1 << n) + mask, "\\tiny \\alert{" + s + "}",  -2.5 + 1.75 * jlen, -2 - 0.5 * ilen);
    }
}

int main() {
    solve();

    drawQ.draw();
}
