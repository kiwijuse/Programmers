#include <iostream>
#include <sstream>
#include <string>
#include <cmath>
#include <queue>
#include <set>
#include <map>
using namespace std;

vector<string> solution(vector<string> record) {
    vector<string> answer;
    map<string, string> uid_map;
    queue<tuple<string, string>> q;
    for (int i = 0; i < record.size(); i++) {
        istringstream iss(record[i]);
        string action, uid, nickname;
        iss >> action >> uid >> nickname;
        if (action == "Enter") {
            uid_map[uid] = nickname;
            q.push({ action, uid });
        }
        else if (action == "Leave") {
            q.push({ action, uid });
        }
        else if (action == "Change") {
            uid_map[uid] = nickname;
        }
    }

    while (!q.empty()) {
        tuple<string, string> a = q.front();
        q.pop();

        string action = get<0>(a);
        string uid = get<1>(a);

        if (action == "Enter") {
            answer.push_back(uid_map[uid] + "님이 들어왔습니다.");
        } 
        else {
            answer.push_back(uid_map[uid] + "님이 나갔습니다.");
        }
    }

    return answer;
}