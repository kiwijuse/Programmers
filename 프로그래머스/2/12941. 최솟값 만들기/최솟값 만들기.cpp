#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int solution(vector<int> A, vector<int> B)
{
    int answer = 0;

    sort(A.begin(), A.end());
    sort(B.begin(), B.end(), greater<int>());

    for (int i = 0; i < A.size(); i++) {
        answer += A[i] * B[i];
    }

    return answer;
}

/*
어떤 값에서 최솟값을 구하려면
배열을 정렬해서 항상 A 배열의 최솟값과 B 배열의 최댓값을
곱해서 더하면 최솟값이 나온다는 사실을 이용하여 풀이
*/