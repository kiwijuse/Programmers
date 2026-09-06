#include <string>
#include <vector>

using namespace std;

string solution(string new_id) {
    string answer = new_id;

    for (int i = 0;i < answer.length();i++) {
        if (answer[i] > 64 && answer[i] < 91) answer[i] += 32;
    }

    for (int i = answer.length() - 1; i >= 0; i--) {
        if (!((answer[i] > 96 && answer[i] < 123) || (answer[i] > 47 && answer[i] < 58) ||
            answer[i] == '-' || answer[i] == '.' || answer[i] == '_')) {
            answer.erase(i, 1);
        }
    }

    for (int i = answer.length() - 2; i >= 0; i--) {
        if (answer[i] == '.' && answer[i + 1] == '.') {
            answer.erase(i, 1);
        }
    }

    if (answer[0] == '.')answer.erase(0, 1);
    if (answer[answer.length()-1] == '.')answer.erase(answer.length() - 1, 1);

    if (answer.length() == 0)answer = "a";

    if (answer.length() > 15) {
        answer = answer.substr(0, 15);
        if (answer[14] == '.')answer.erase(14,1);
    }

    if (answer.length() <= 2) {
        while (answer.length() < 3) {
            answer += answer[answer.length() - 1];
        }
    }

    return answer;
}


/*
각 순서에 맞게 체크후 수정
*/

