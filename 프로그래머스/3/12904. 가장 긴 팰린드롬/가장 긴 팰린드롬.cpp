#include <iostream>
#include <string>
#include <algorithm>
using namespace std;
int solution(string s) {
    int answer = 0;

    for (int i = 0; i < s.length(); i++) {

        int left = i;
        int right = i;
        while (left >= 0 && right < s.length() && s[left] == s[right]) {
            left--;
            right++;
        }
        int len1 = right - left - 1;
        answer = max(answer, len1);

        left = i;
        right = i + 1;
        while (left >= 0 && right < s.length() && s[left] == s[right]) {
            left--;
            right++;
        }
        int len2 = right - left - 1;
        answer = max(answer, len2);
    }

    return answer;
}

/*
for 문 돌면서 해당 자리로부터 투포인터를 돌려서
팰린드롭인지 검사하는 방식 이때 홀수의 경우 짝수의 경우를 나눠서 검사함
제일 긴 길이를 answer 에 계속 푸쉬하며 진행.
*/