#include <string>
#include <vector>
#include <queue>
#include <set>
using namespace std;

int solution(string begin, string target, vector<string> words) {
    int answer = 0;

    set<string> correct_words;
    set<string> a;
    queue <tuple<int, string>> q;
    for (int i = 0; i < words.size();i++) {
        correct_words.insert(words[i]);
    }

    q.push({ 0,begin });

    while (!q.empty()) {
        int depth = get<0>(q.front());
        string word = get<1>(q.front());
        q.pop();
        if (word == target)return depth;
        for (int i = 0;i < 26;i++) {
            for (int j = 0;j < word.length();j++) {
                string new_word = word;
                new_word[j] = i + 97;
                if (correct_words.count(new_word) && !a.count(new_word)) {
                    q.push({ depth + 1, new_word });
                }
                a.insert(new_word);
            }
        }
    }

    return 0;
}