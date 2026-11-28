#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

vector<char> a; //정답
vector<char> b; //현재

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    a.resize(n);
    b.resize(n);
    char first;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        if (i == 0) { first = a[i]; }
        b[i] = first;
    }
   
    int answer = 1;

    for (int i = 1; i < n; i++) {
        if (a[i] != b[i]) {//정답 색이랑 현재 색이랑 다르면
            int j = i + 1; 
            while (j < n && a[j] == a[i]) j++; //이어지는 연속구간 구하기
            fill(b.begin() + i, b.begin() + j, a[i]); //채우기
            answer++;
        }
    }

    cout << answer;
}

/*
처음색으로 다 칠한뒤 연속 구간이 있는 만큼 재색칠하기.
*/