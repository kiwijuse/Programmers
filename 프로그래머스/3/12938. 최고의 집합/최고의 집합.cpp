#include <string>
#include <vector>

using namespace std;

vector<int> solution(int n, int s) {
    if (n > s)return { -1 };
    vector<int> answer;

    int q = s / n;
    int r = s % n;

    for (int i = 0; i < n - r; i++) {
        answer.push_back(q);
    }

    for (int i = 0; i < r; i++) {
        answer.push_back(q + 1);
    }

    return answer;
}

/*
이 문제의 핵심은 s를 최대한 균등한 n개로 만드는 것이다.
몫과 나머지를 구해서 몫+1 과 몫을 더해 s가 되는 집합 answer를 리턴한다.
*/