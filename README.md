# Programmers

프로그래머스에서 푼 문제를 모아두는 곳.

거창한 목표가 있는 건 아니다. 그냥 머리가 굳는 게 싫어서 시작했다. 하루에 한 문제라도.

## 랜덤 추천 문제

<!-- DAILY:START -->
> **2026-08-25** · 아직 안 푼 293문제 중에서 뽑았다.

1. **[H-Index](https://school.programmers.co.kr/learn/courses/30/lessons/42747)** · Lv.2 · 정답률 68%
2. **[구명보트](https://school.programmers.co.kr/learn/courses/30/lessons/42885)** · Lv.2 · 정답률 73%
3. **[봉인된 주문](https://school.programmers.co.kr/learn/courses/30/lessons/389481)** · Lv.3 · 정답률 29%

<sub>매일 자정에 새로 뽑힌다.</sub>
<!-- DAILY:END -->

## 연속 학습

<picture>
  <source media="(prefers-color-scheme: dark)" srcset="assets/grass-dark.svg?v=1787668124">
  <img alt="연속 학습 기록" src="assets/grass-light.svg?v=1787668124">
</picture>

<!-- STREAK:START -->
`현재 3일 연속` · `최장 3일` · `활동 3일` · `풀이 커밋 3회`
<!-- STREAK:END -->

<sub>README를 고치거나 설정을 만지는 커밋은 세지 않는다. <code>프로그래머스/</code> 아래에 풀이가 실제로 올라온 날만 칸이 채워진다.</sub>

## 풀이 목록

<!-- INDEX:START -->
**총 3문제** — `Lv.0 1` · `Lv.1 1` · `Lv.3 1`

<details open>
<summary><b>Level 0</b> · 1문제</summary>

| # | 문제 | 언어 | 풀이 |
|---:|---|---|---|
| 1 | [몫 구하기](https://school.programmers.co.kr/learn/courses/30/lessons/120805) | C++ | [코드](%ED%94%84%EB%A1%9C%EA%B7%B8%EB%9E%98%EB%A8%B8%EC%8A%A4/0/120805.%E2%80%85%EB%AA%AB%E2%80%85%EA%B5%AC%ED%95%98%EA%B8%B0) |

</details>

<details>
<summary><b>Level 1</b> · 1문제</summary>

| # | 문제 | 언어 | 풀이 |
|---:|---|---|---|
| 1 | [크기가 작은 부분문자열](https://school.programmers.co.kr/learn/courses/30/lessons/147355) | C++ | [코드](%ED%94%84%EB%A1%9C%EA%B7%B8%EB%9E%98%EB%A8%B8%EC%8A%A4/1/147355.%E2%80%85%ED%81%AC%EA%B8%B0%EA%B0%80%E2%80%85%EC%9E%91%EC%9D%80%E2%80%85%EB%B6%80%EB%B6%84%EB%AC%B8%EC%9E%90%EC%97%B4) |

</details>

<details>
<summary><b>Level 3</b> · 1문제</summary>

| # | 문제 | 언어 | 풀이 |
|---:|---|---|---|
| 1 | [단어 변환](https://school.programmers.co.kr/learn/courses/30/lessons/43163) | C++ | [코드](%ED%94%84%EB%A1%9C%EA%B7%B8%EB%9E%98%EB%A8%B8%EC%8A%A4/3/43163.%E2%80%85%EB%8B%A8%EC%96%B4%E2%80%85%EB%B3%80%ED%99%98) |

</details>
<!-- INDEX:END -->

## 자동화

문제를 풀고 제출하면 [백준허브](https://github.com/BaekjoonHub/BaekjoonHub)가 코드를 이 저장소로 올린다.
그 뒤는 GitHub Actions가 알아서 한다.

| 스크립트 | 언제 도는지 | 하는 일 |
|---|---|---|
| `pick-daily.mjs` | 매일 자정, 수동 실행 | 아직 안 푼 문제 중에서 세 개를 뽑는다 |
| `render-grass.mjs` | 풀이가 올라올 때, 매일 자정 | 커밋 기록을 읽어 잔디를 다시 그린다 |
| `build-index.mjs` | 풀이가 올라올 때, 매일 자정 | 폴더를 훑어 위 목록을 다시 만든다 |

추천이 마음에 안 들면 Actions 탭에서 `daily` 워크플로를 `reroll`을 켜고 돌리면 새로 뽑힌다.
난이도 범위와 언어, 뽑는 개수는 [daily.yml](.github/workflows/daily.yml)의 `env`에서 바꾼다.

## 기록

### 2026-08-23

자동화부터 깔고 시작했다. 막상 앉으면 뭘 풀지 고르다가 시간을 다 버리는 게 싫었다. 이제 아침에 열면 오늘 풀 문제가 이미 정해져 있다.

---

<sub>저장소 구성과 자동화 아이디어는 <a href="https://github.com/pill27211/programmers-daily">pill27211/programmers-daily</a>를 참고했다.</sub>
