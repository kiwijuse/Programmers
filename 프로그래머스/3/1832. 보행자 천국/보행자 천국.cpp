#include <vector>

using namespace std;

int MOD = 20170805;

int solution(int m, int n, vector<vector<int>> city_map) {
    int dp[500][500][2] = { 0 };
    dp[0][0][0] = 1;

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (i == 0 && j == 0) continue;
            if (j > 0) {
                if (city_map[i][j - 1] == 0) {
                    dp[i][j][0] = (dp[i][j - 1][0] + dp[i][j - 1][1]) % MOD;
                }
                else if (city_map[i][j - 1] == 2) {
                    dp[i][j][0] = dp[i][j - 1][0] % MOD;
                }
            }

            if (i > 0) {
                if (city_map[i - 1][j] == 0) {
                    dp[i][j][1] = (dp[i - 1][j][0] + dp[i - 1][j][1]) % MOD;
                }
                else if (city_map[i - 1][j] == 2) {
                    dp[i][j][1] = dp[i - 1][j][1] % MOD;
                }
            }
        }
    }
    return (dp[m - 1][n - 1][0] + dp[m - 1][n - 1][1]) % MOD;
}

/*
dp를 이용하여 왼쪽에서 온 경우의수 와 위에서 온 경우의수를 계속 합쳐서 마지막 도착지에서 리턴.
왼쪽에서 오는 경우, 위에서 오는경우 두가지 경우의수를 계산하여 합함
각각의 경우에서 이전 칸의 상태가 0 이라면 왼쪽, 위 에서온 경우를 합쳐 dp에 저장.
2라면 각각 온 경로만 현재칸에 다시 저장
마지막 좌표에 도달하면 왼족, 위에서 온 값을 더해서 리턴.
*/