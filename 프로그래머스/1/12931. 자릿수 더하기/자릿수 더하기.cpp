#include <iostream>

using namespace std;
int solution(int n) {
    int answer = 0;
    string s = to_string(n);
    for (int i = 0;i < s.length();i++) {
        answer += s[i] - 48;
    }
    return answer;
}

/*
자연수 n을 string 으로 변환후에
뒤에서부터 읽어서 answer에 더함
더할때는 ascii code를 이용
*/