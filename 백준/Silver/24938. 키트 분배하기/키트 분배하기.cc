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
    long long b = sum / s;
    long long answer = 0, carry = 0;
    for (int i = 0; i < s; i++) {
        carry += a[i] - b;
        answer += (carry < 0 ? -carry : carry);
    }

    cout << answer;


    return 0;

    /*
    현재 방의 키트 수가 초과면 다음방으로 넘기고, 없다면 다음방꺼를 가져온다. 
    결국 평균값으로 모든 방이 되려면 현재 방의 개수만 파악해서 얼만큼 옮겨야하는지 더한값이 정답.
    */
}