#include <iostream>
#include <queue>
#include <string>
#include <algorithm>
#include <vector>
#include <tuple>
using namespace std;
int i, j, n, m, monster_count = 1, box_count, turn;
int player_hp = 20, player_dmg = 2, player_dfs = 2, player_lv = 1, player_exp;
int max_hp = 20,max_exp=5;
int weapon_dmg, armor_dfs, accessory_count;
int p_y, p_x,l_y,l_x;
char map[105][105], moving[5005];
string mov, death_reason;
vector <tuple<string, int, int, int, int>>monster_info[105][105];
vector <tuple<char, string>>box_info[105][105];
queue <pair<int, int>> q;
bool boss_kill, player_live = true, HR, RE, CO, EX, DX, HU, CU;
void game_start() {
    q.push({ p_y,p_x });
    while (!q.empty()) {
        if (turn >= mov.length())
            break;
        auto [y, x] = q.front();
        q.pop();
        int ny = y;
        int nx = x;
        if (moving[turn] == 'L')
            nx -= 1;
        else if (moving[turn] == 'R')
            nx += 1;
        else if (moving[turn] == 'U')
            ny -= 1;
        else if (moving[turn] == 'D')
            ny += 1;
        if (ny > n || ny < 1 || nx > m || nx < 1 || map[ny][nx] == '#') {//모서리나 벽이여서 갈수 없는경우
            ny = y;
            nx = x;
        }
        l_y = ny;
        l_x = nx;
        if (map[ny][nx] == '.') {//빈칸이면
            q.push({ ny,nx });
            turn++;
        }
        else if (map[ny][nx] == 'B') {//상자면
            auto [what, qwe] = box_info[ny][nx][0];
            if (what == 'W')//무기면
                weapon_dmg = stoi(qwe);            
            else if (what == 'A')//방어구면
                armor_dfs = stoi(qwe);
            else {//장신구면
                if (accessory_count < 4) {
                    if (qwe == "HR") {
                        if (HR == false) {
                            accessory_count++;
                            HR = true;
                        }
                    }
                    else if (qwe == "RE") {
                        if (RE == false) {
                            accessory_count++;
                            RE = true;
                        }
                    }
                    else if (qwe == "CO") {
                        if (CO == false) {
                            accessory_count++;
                            CO = true;
                        }
                    }
                    else if (qwe == "EX") {
                        if (EX == false) {
                            accessory_count++;
                            EX = true;
                        }
                    }
                    else if (qwe == "DX") {
                        if (DX == false) {
                            accessory_count++;
                            DX = true;
                        }
                    }
                    else if (qwe == "HU") {
                        if (HU == false) {
                            accessory_count++;
                            HU = true;
                        }
                    }
                    else if (qwe == "CU") {
                        if (CU == false) {
                            accessory_count++;
                            CU = true;
                        }
                    }
                }
            }
            map[ny][nx] = '.';
            q.push({ ny,nx });
            turn++;
        }
        else if (map[ny][nx] == '^') {//가시 함정이면
            if (DX)
                player_hp -= 1;
            else
                player_hp -= 5;
            if (player_hp <= 0) {//피가 다 닳았으면
                if (RE) {//부활 장신구가 있다면
                    RE = false;//부활장신구 사용
                    player_hp = max_hp;
                    q.push({ p_y,p_x });
                    accessory_count--;
                    turn++;
                }
                else {//장신구가 없다면 죽음
                    player_hp = 0;
                    death_reason = "YOU HAVE BEEN KILLED BY SPIKE TRAP..";
                    turn++;
                    player_live = false;
                    break;
                }
            }
            else {//피가 남아있으면
                q.push({ ny,nx });
                turn++;
            }
        }
        else if (map[ny][nx] == '&') {//몬스터면
            auto [m_name, m_dmg, m_dfs, m_hp, m_exp] = monster_info[ny][nx][0];
            if (CO && DX)
                m_hp-=max(1, (player_dmg + weapon_dmg) * 3 - m_dfs);
            else if(CO)
                m_hp -= max(1, (player_dmg + weapon_dmg) * 2 - m_dfs);
            else
                m_hp -= max(1, (player_dmg + weapon_dmg)- m_dfs);
            while (m_hp > 0 && player_hp > 0) {//몬스터와 둘중하나 죽을때 까지 전투
                player_hp -= max(1, (m_dmg)-(player_dfs+armor_dfs));
                if (player_hp <= 0)//플레이어 피가 다 달았다면
                    break;
                m_hp -= max(1, (player_dmg + weapon_dmg) - m_dfs);
            }

            if (player_hp <= 0) {
                if (RE) {//부활 장신구가 있다면
                    RE = false;//부활장신구 사용
                    player_hp = max_hp;
                    q.push({ p_y,p_x });
                    accessory_count--;
                    turn++;
                }
                else {//장신구가 없다면 죽음
                    player_hp = 0;
                    death_reason = "YOU HAVE BEEN KILLED BY " + m_name + "..";
                    turn++;
                    player_live = false;
                    break;
                }
            }
            if (m_hp <= 0) {//몬스터가 죽었다면
                map[ny][nx] = '.';
                turn++;
                if (HR) {
                    player_hp += 3;
                    if (player_hp > max_hp)
                        player_hp = max_hp;
                }
                if (EX)
                    player_exp += m_exp * 1.2;
                else
                    player_exp += m_exp;
                if (player_exp >= max_exp) {//레벨업하면
                    player_lv++;
                    player_exp = 0;
                    max_exp +=5;
                    max_hp += 5;
                    player_hp = max_hp;
                    player_dmg += 2;
                    player_dfs += 2;
                }
                q.push({ ny,nx });
            }
        }
        else if (map[ny][nx] == 'M') {//보스면
            auto [m_name, m_dmg, m_dfs, m_hp, m_exp] = monster_info[ny][nx][0];
            if (HU)
                player_hp = max_hp;
            int fight_turn = 0;
            while (m_hp > 0 && player_hp > 0) {//몬스터와 둘중하나 죽을때 까지 전투
                if(fight_turn==0 && CO && DX)
                    m_hp -= max(1, (player_dmg + weapon_dmg) * 3 - m_dfs);
                else if(fight_turn == 0 && CO)
                    m_hp -= max(1, (player_dmg + weapon_dmg) * 2 - m_dfs);
                else
                    m_hp -= max(1, (player_dmg + weapon_dmg) - m_dfs);
                if (m_hp <= 0)
                    break;                
                if (fight_turn == 0 && HU) {
                    fight_turn++;
                    continue;
                }
                else
                    player_hp -= max(1, (m_dmg)-(player_dfs + armor_dfs));
                if (player_hp <= 0) {//플레이어 피가 다 달았다면
                    break;
                }
                fight_turn++;
            }
            if (player_hp <= 0) {
                if (RE) {//부활 장신구가 있다면
                    RE = false;//부활장신구 사용
                    player_hp = max_hp;
                    q.push({ p_y,p_x });
                    accessory_count--;
                    turn++;
                }
                else {//장신구가 없다면 죽음
                    player_hp = 0;
                    death_reason = "YOU HAVE BEEN KILLED BY " + m_name + "..";
                    turn++;
                    player_live = false;
                    break;
                }
            }
            if (m_hp <= 0) {//몬스터가 죽었다면
                map[ny][nx] = '.';
                turn++;
                boss_kill = true;
                if (HR) {
                    player_hp += 3;
                    if (player_hp > max_hp)
                        player_hp = max_hp;
                }
                if (EX)
                    player_exp += m_exp * 1.2;
                else
                    player_exp += m_exp;
                if (player_exp >= max_exp) {//레벨업하면
                    player_lv++;
                    player_exp = 0;
                    max_exp += 5;
                    max_hp += 5;
                    player_hp = max_hp;
                    player_dmg += 2;
                    player_dfs += 2;
                }
                break;
            }
        }
    }
    if(player_live)
        map[l_y][l_x] = '@';
    for (i = 1; i <= n; i++) {
        for (j = 1; j <= m; j++) {
            cout << map[i][j];
        }
        cout << '\n';
    }
    cout << "Passed Turns : " << turn << '\n';
    cout << "LV : " << player_lv << '\n';
    cout << "HP : " << player_hp << '/' << max_hp << '\n';
    cout << "ATT : " << player_dmg << '+' << weapon_dmg << '\n';
    cout << "DEF : " << player_dfs << '+' << armor_dfs << '\n';
    cout << "EXP : " << player_exp << '/' << max_exp << '\n';
    if (player_live) {//살아있으면
        if (boss_kill)//보스를 죽였으면
            cout << "YOU WIN!";        
        else 
            cout << "Press any key to continue.";        
    }
    else
        cout << death_reason;    
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n >> m;
    for (i = 1; i <= n; i++) {
        for (j = 1; j <= m; j++) {
            cin >> map[i][j];
            if (map[i][j] == '&')
                monster_count++;
            else if (map[i][j] == 'B')
                box_count++;
            else if (map[i][j] == '@') {
                p_y = i;
                p_x = j;
                map[i][j] = '.';
            }
        }
    }
    cin >> mov;
    for (i = 0; i < mov.length(); i++) {
        moving[i] = mov[i];
    }
    for (i = 0; i < monster_count; i++) {
        int R, C, W, A, H, E;
        string S;
        cin >> R >> C >> S >> W >> A >> H >> E;
        monster_info[R][C].push_back({ S,W,A,H,E });
    }
    for (i = 0; i < box_count; i++) {
        int y, x;
        char a;
        string qq;
        cin >> y >> x >> a >> qq;
        box_info[y][x].push_back({ a,qq });
    }
    game_start();
}