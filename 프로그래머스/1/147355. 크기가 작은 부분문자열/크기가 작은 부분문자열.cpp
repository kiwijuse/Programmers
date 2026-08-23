#include <string>
#include <vector>

using namespace std;
int solution(string t, string p) {
    int answer = 0;
    int length = p.length();
    long long p_int = stoll(p);

    for (int i = 0;i < t.length() - length + 1;i++) {
        string t_str = "";
        for (int j = i;j < length+i;j++) {
            t_str += t[j];
        }
        if (p_int >= stoll(t_str)) {
            answer++;
        }
    }

    return answer;
}