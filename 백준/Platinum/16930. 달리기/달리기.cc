#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <queue>
using namespace std;
int map[1005][1005];
int depth[1005][1005];
int dx[] = { 1,-1,0,0 };
int dy[] = { 0,0,-1,1 };
int n, m, k;
void bfs(int fy, int fx) {
	queue<pair<int, int>>q;
	q.push(make_pair(fy, fx));
	depth[fy][fx] = 1;
	while (!q.empty()) {
		int y = q.front().first;
		int x = q.front().second;
		q.pop();
		for (int i = 0; i < 4; i++) {
			for (int j = 1; j <= k; j++) {
				int nx = x + (dx[i] * j);
				int ny = y + (dy[i] * j);
				if (nx < 1 || nx > m || ny < 1 || ny > n || map[ny][nx] == 35 )
					break;
				if (depth[ny][nx] != 0 && depth[ny][nx] <= depth[y][x]) {
					break;
				}
				if (map[ny][nx] == 46 && depth[ny][nx] == 0) {
					q.push(make_pair(ny, nx));
					depth[ny][nx] = depth[y][x] + 1;
				}
			}
		}
	}
}



int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	vector <pair<int, int>>v;
	cin >> n >> m >> k;
	for (int i = 1; i <= n; i++) {//y
		string s;
		cin >> s;
		for (int j = 1; j <= m; j++) {//x
			map[i][j] = s[j - 1];
		}
	}
	
	int x1, y1, x2, y2;
	cin >> x1 >> y1 >> x2 >> y2;
	bfs(x1, y1);
	cout << depth[x2][y2] - 1;
}