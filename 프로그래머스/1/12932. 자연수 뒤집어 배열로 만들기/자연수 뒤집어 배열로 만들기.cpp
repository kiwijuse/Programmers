#include <string>
#include <vector>

using namespace std;

vector<int> solution(long long n) {
    vector<int> answer;
    string a = to_string(n);

    for (int i = a.length() - 1;i >= 0;i--) {
        answer.push_back(a[i] - 48);
    }
    return answer;
}

/* 자연수 n을 string 으로 변환후에
뒤에서부터 읽어서 배열에 집어넣음 
char -> int 변환은 ascii code를 이용
*/