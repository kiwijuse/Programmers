# Programmers

프로그래머스에서 푼 문제를 쌓아두는 창고.<br>
실력이 늘어서라기보다 **손이 굳는 게 싫어서** 시작했다. 하루에 한 문제라도.

## 📌 오늘 뽑힌 문제

<!-- DAILY:START -->
> **2026-08-23** 치의 과제. 후보 295문제 중에서 뽑았다.

1. **[크기가 작은 부분 문자열 ](https://school.programmers.co.kr/learn/courses/30/lessons/147355)** · Lv.1 · 정답률 79%
2. **[기지국 설치](https://school.programmers.co.kr/learn/courses/30/lessons/12979)** · Lv.3 · 정답률 59%
3. **[이모티콘 할인행사](https://school.programmers.co.kr/learn/courses/30/lessons/150368)** · Lv.2 · 정답률 45%

<sub>매일 00:00 KST 자동 교체 · 마음에 안 들면 Actions → `daily` → Run workflow에서 reroll 체크</sub>
<!-- DAILY:END -->

## 🌱 풀이 잔디

<picture>
  <source media="(prefers-color-scheme: dark)" srcset="assets/grass-dark.svg?v=1787472274">
  <img alt="풀이 잔디" src="assets/grass-light.svg?v=1787472274">
</picture>

<!-- STREAK:START -->
`현재 1일 연속` · `최장 1일` · `활동 1일` · `풀이 커밋 1회`
<!-- STREAK:END -->

<sub>README 손질이나 워크플로 수정 같은 잡커밋은 안 세고, <code>프로그래머스/</code> 아래를 건드린 커밋만 잔디가 된다.</sub>

## 📚 풀이 목록

<!-- INDEX:START -->
> 아직 올라온 풀이가 없다. 백준허브로 문제를 하나 제출하면 이 표가 저절로 생긴다.
<!-- INDEX:END -->

## 🛠 어떻게 굴러가나

| 무엇 | 언제 | 하는 일 |
|---|---|---|
| `pick-daily.mjs` | 매일 00:00 KST · 수동 | 프로그래머스 공개 API에서 **안 푼 문제만** 골라 3개 추천 |
| `render-grass.mjs` | 풀이 커밋 시 · 매일 | 풀이 커밋 기록으로 잔디 SVG(라이트/다크) 생성 |
| `build-index.mjs` | 풀이 커밋 시 · 매일 | 폴더를 훑어 레벨별 풀이 표 갱신 |

풀이 파일 자체는 [백준허브](https://github.com/BaekjoonHub/BaekjoonHub) 확장이 채점 통과 시점에 알아서 커밋한다.
봇은 그 위에 얹혀서 README만 손본다.

**다시 뽑고 싶으면** → Actions 탭 → `daily` 워크플로 → Run workflow → `reroll` 체크.

설정은 [워크플로 파일](.github/workflows/daily.yml)의 `env`에서 바꾼다 — 난이도 범위(`LEVELS`), 언어 필터(`PICK_LANG`), 추천 개수(`PICK_COUNT`).

## 기록

### 2026-08-23

자동화부터 깔고 시작. 문제 고르느라 시간 쓰는 게 제일 아까웠어서, 아침에 열면 오늘 풀 것 세 개가 이미 정해져 있게 만들었다. 이제 핑계가 없다.
