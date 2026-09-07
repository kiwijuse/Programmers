#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

vector<string> solution(vector<string> players, vector<string> callings) {
    unordered_map<string, int> player_idx;

    for (int i = 0; i < players.size(); i++) {
        player_idx[players[i]] = i;
    }

    for (int i = 0; i < callings.size(); i++) {
        string current_player = callings[i];
        int current_idx = player_idx[current_player];

        int front_idx = current_idx - 1;
        string front_player = players[front_idx];
        swap(players[current_idx], players[front_idx]);

        player_idx[current_player] = front_idx;
        player_idx[front_player] = current_idx;
    }

    return players;
}