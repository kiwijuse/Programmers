#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int sz;            // 리프 개수 (N 이상인 2의 거듭제곱)
vector<int> t;     // 트리. t[1]이 맨 위, 리프는 t[sz] ~ t[sz + N - 1]
vector<int> a;

// 만들기: 리프에 값을 넣고, 아래에서 위로 최댓값 채우기
void build(const vector<int>& d) {
    int n = d.size();
    sz = 1;
    while (sz < n) sz *= 2;
    t.assign(2 * sz, 0);
    for (int i = 0; i < n; i++) t[sz + i] = d[i];
    for (int i = sz - 1; i >= 1; i--) t[i] = max(t[2 * i], t[2 * i + 1]);
}

// 지우기(값 바꾸기): i번 값을 v로 바꾸고 부모들만 다시 계산
void update(int i, int v) {
    i += sz;
    t[i] = v;
    for (i /= 2; i >= 1; i /= 2) t[i] = max(t[2 * i], t[2 * i + 1]);
}

// 찾기: [0, R] 안에서 값 > d 인 가장 왼쪽 위치. 없으면 -1
// node가 맡은 구간은 [l, r]
int query(int node, int l, int r, int R, int d) {
    if (l > R || t[node] <= d) return -1;   // 범위 밖이거나, 이 구간 최댓값이 d 이하
    if (l == r) return l;                   // 리프에 도착하면 그게 답
    int m = (l + r) / 2;
    int res = query(2 * node, l, m, R, d);  // 왼쪽 먼저
    if (res != -1) return res;
    return query(2 * node + 1, m + 1, r, R, d);  // 왼쪽에 없으면 오른쪽
}
// 호출: query(1, 0, sz - 1, end, d)


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, k;
    cin >> n >> k;
    a.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    build(a);
    int day = 0;
    int end = k - 1;
    while (t[1] != 0) {//최대값이 0 이 아니라면 아직 다 문제를 못푼것
        int first = query(1, 0, sz - 1, end, 0); // 하루의 첫 문제
        int d = a[first];
        update(first, 0);
        if (end + 1 < n) end++;
        int b;
        while ((b = query(1, 0, sz - 1, end, d)) != -1) {//풀수 있는 문제까지 풀기
            d = a[b];
            update(b, 0);
            if (end + 1 < n) end++;
        }
        day++;
    }

    cout << day;
}

/*
세그먼트 트리로 선택된 난이도보다 큰 제일 가까운 값을 구해서 해당 값을 0으로 초기화 시키면서
모든 노드가 0 이 될때까지 계산해서 날짜를 구함
*/