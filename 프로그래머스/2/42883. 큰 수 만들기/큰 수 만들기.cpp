#include <string>
#include <vector>
#include <algorithm>
using namespace std;

string solution(string number, int k) {
    string answer = "";

    for (int i = 0; i < number.length(); i++) {
        char current = number[i];

        while (!answer.empty() && k > 0 && answer.back() < current) {
            answer.pop_back();
            k--;
        }

        answer.push_back(current);
    }

    if (k > 0) {
        answer = answer.substr(0, answer.length() - k);
    }

    return answer;
}
/*
앞자리에 최대한 큰 수가 오도록 하는게 핵심
숫자의 순서를 유지하며 큰수가 최대한 이상적인 위치에 오도록 쳐냄
*/