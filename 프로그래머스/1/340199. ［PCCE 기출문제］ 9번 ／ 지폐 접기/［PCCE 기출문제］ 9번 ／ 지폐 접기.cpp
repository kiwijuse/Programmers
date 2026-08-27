#include <string>
#include <vector>
#include <queue>
#include <tuple>
using namespace std;

int solution(vector<int> wallet, vector<int> bill) {
    int answer = 0;
    queue <tuple<int, int, int>> q;
    q.push({ 0, bill[0], bill[1] });
    q.push({ 0, bill[1], bill[0] });

    while (!q.empty()) {
        int depth = get<0>(q.front());
        int x = get<1>(q.front());
        int y = get<2>(q.front());

        q.pop();
        if (wallet[0] >= x && wallet[1] >= y) {
            return depth;
        }

        if (x >= y) {
            q.push({ depth + 1, x / 2, y });
        }
        else {
            q.push({ depth + 1, x, y / 2 });
        }

    }

    return answer;
}