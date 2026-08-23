// 오늘 풀 문제를 골라 README의 DAILY 블록에 써넣는다.
// - 프로그래머스 공개 챌린지 API에서 후보를 긁어온다
// - 이미 푼 문제(= 프로그래머스/ 아래 디렉터리)는 후보에서 뺀다
// - 날짜를 시드로 쓰기 때문에 같은 날 여러 번 돌려도 결과가 같다 (리롤 시에만 바뀜)

import { readFileSync, writeFileSync, existsSync, readdirSync } from "node:fs";
import { join } from "node:path";

const ROOT       = process.cwd();
const README     = join(ROOT, "README.md");
const STATE      = join(ROOT, ".github", "daily-state.json");
const SOLVED_DIR = join(ROOT, process.env.SOLVED_DIR || "프로그래머스");
const LEVELS     = (process.env.LEVELS || "1,2,3").split(",").map((s) => s.trim()).filter(Boolean);
const PICK_LANG  = (process.env.PICK_LANG || "cpp").trim();
const PICK_COUNT = Number(process.env.PICK_COUNT || 3);
const REROLL     = /^(true|1|yes)$/i.test(process.env.REROLL || "");

const API = "https://school.programmers.co.kr/api/v2/school/challenges/";
const UA  = "Mozilla/5.0 (compatible; programmers-daily-bot)";
const LESSON = (id) => `https://school.programmers.co.kr/learn/courses/30/lessons/${id}`;

// ── KST 기준 오늘 날짜 ────────────────────────────────────────────
const kstToday = () => new Date(Date.now() + 9 * 3600 * 1000).toISOString().slice(0, 10);

// ── 문자열 → 32bit 시드, mulberry32 PRNG ──────────────────────────
function seedOf(str) {
  let h = 2166136261 >>> 0;
  for (let i = 0; i < str.length; i++) {
    h ^= str.charCodeAt(i);
    h = Math.imul(h, 16777619) >>> 0;
  }
  return h >>> 0;
}
function rngFrom(seed) {
  let a = seed >>> 0;
  return () => {
    a = (a + 0x6d2b79f5) >>> 0;
    let t = Math.imul(a ^ (a >>> 15), 1 | a);
    t = (t + Math.imul(t ^ (t >>> 7), 61 | t)) ^ t;
    return ((t ^ (t >>> 14)) >>> 0) / 4294967296;
  };
}
function shuffled(arr, rand) {
  const a = arr.slice();
  for (let i = a.length - 1; i > 0; i--) {
    const j = Math.floor(rand() * (i + 1));
    [a[i], a[j]] = [a[j], a[i]];
  }
  return a;
}

// ── 이미 푼 문제 id 수집 ──────────────────────────────────────────
function solvedIds() {
  const ids = new Set();
  if (!existsSync(SOLVED_DIR)) return ids;
  for (const lv of readdirSync(SOLVED_DIR, { withFileTypes: true })) {
    if (!lv.isDirectory()) continue;
    for (const p of readdirSync(join(SOLVED_DIR, lv.name), { withFileTypes: true })) {
      if (!p.isDirectory()) continue;
      const m = /^(\d+)\./.exec(p.name);
      if (m) ids.add(Number(m[1]));
    }
  }
  return ids;
}

// ── API에서 레벨별 문제 목록 긁어오기 ─────────────────────────────
async function fetchLevel(level) {
  const out = [];
  for (let page = 1; page <= 50; page++) {
    const qs = new URLSearchParams({ page: String(page), order: "recent" });
    let url = `${API}?${qs}&levels%5B%5D=${encodeURIComponent(level)}`;
    if (PICK_LANG) url += `&languages%5B%5D=${encodeURIComponent(PICK_LANG)}`;

    const res = await fetch(url, { headers: { Accept: "application/json", "User-Agent": UA } });
    if (!res.ok) throw new Error(`API ${res.status} — level ${level}, page ${page}`);
    const json = await res.json();
    for (const p of json.result || []) out.push(p);
    if (!json.totalPages || page >= json.totalPages) break;
  }
  return out;
}

// ── README 블록 갈아끼우기 ────────────────────────────────────────

// ── main ──────────────────────────────────────────────────────────
const today = kstToday();

let state = { date: "", spin: 0, ids: [] };
if (existsSync(STATE)) {
  try { state = { ...state, ...JSON.parse(readFileSync(STATE, "utf8")) }; } catch { /* 깨졌으면 새로 */ }
}
// 날짜가 바뀌면 리롤 카운터를 0으로, 같은 날 리롤이면 +1
const spin = state.date === today ? (REROLL ? state.spin + 1 : state.spin) : 0;

const solved = solvedIds();
const pool = [];
for (const lv of LEVELS) {
  for (const p of await fetchLevel(lv)) {
    if (!solved.has(p.id)) pool.push(p);
  }
}

if (pool.length === 0) {
  console.error("후보가 비었습니다. LEVELS / PICK_LANG 설정을 확인하세요.");
  process.exit(1);
}

const rand = rngFrom(seedOf(`${today}#${spin}#${LEVELS.join(",")}`));
const picks = shuffled(pool, rand).slice(0, Math.min(PICK_COUNT, pool.length));

const lines = picks.map(
  (p, i) => `${i + 1}. **[${p.title}](${LESSON(p.id)})** · Lv.${p.level}` +
            (p.acceptanceRate != null ? ` · 정답률 ${p.acceptanceRate}%` : "")
);

const body = [
  `> **${today}** 치의 과제. 후보 ${pool.length}문제 중에서 뽑았다.`,
  ``,
  ...lines,
  ``,
  `<sub>매일 00:00 KST 자동 교체${spin > 0 ? ` · 오늘 ${spin}번 다시 뽑음` : ""} · 마음에 안 들면 Actions → \`daily\` → Run workflow에서 reroll 체크</sub>`,
].join("\n");

writeFileSync(README, replaceBlock(readFileSync(README, "utf8"), "DAILY", body));
writeFileSync(STATE, JSON.stringify({ date: today, spin, ids: picks.map((p) => p.id) }, null, 2) + "\n");

console.log(`${today} (spin ${spin}) · 후보 ${pool.length} · 선택: ${picks.map((p) => p.title).join(", ")}`);

// README의 <!-- NAME:START --> ~ <!-- NAME:END --> 사이를 통째로 갈아끼운다.
function replaceBlock(md, name, body) {
  const open  = "<!-- " + name + ":START -->";
  const close = "<!-- " + name + ":END -->";
  const i = md.indexOf(open);
  const j = md.indexOf(close, i + open.length);
  if (i < 0 || j < 0) throw new Error("README에 " + name + " 마커가 없습니다.");
  return md.slice(0, i + open.length) + "\n" + body + "\n" + md.slice(j);
}
