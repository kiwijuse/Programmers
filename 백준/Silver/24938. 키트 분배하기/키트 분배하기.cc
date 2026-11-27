#include <iostream>

int a[200000];
using namespace std;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int s;
    cin >> s;
    long long sum = 0;
    for (int i = 0; i < s; i++) {
        cin >> a[i];
        sum += a[i];
    }
    int b = sum / s;
    long long answer = 0;
    for (int i = 0; i < s; i++) {
        if (a[i] > b) { //현재 방이 가지고 있는 개수가 맞춰야하는 값보다 많다면
            a[i + 1] += a[i] - b; //다음 방으로 넘김
            answer += a[i] - b;
            a[i] = b;
        }
        else if(a[i] <b) {
            a[i + 1] -= b - a[i]; //다음 방에서 가지고옴
            answer += b - a[i];
            a[i] = b;
        }
    }

    cout << answer;


    return 0;

    /*
    현재 방의 키트 수가 초과면 다음방으로 넘기고, 없다면 다음방꺼를 가져온다. 
    결국 평균값으로 모든 방이 되려면 현재 방의 개수만 파악해서 얼만큼 옮겨야하는지 더한값이 정답.
    */
}