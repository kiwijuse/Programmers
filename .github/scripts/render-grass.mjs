// 풀이 커밋만 세서 잔디 SVG(라이트/다크)를 그린다.
// 일반 커밋(README 수정, 워크플로 손질 등)은 빠지고 프로그래머스/ 아래를 건드린 커밋만 집계된다.

import { execFileSync } from "node:child_process";
import { readFileSync, writeFileSync, mkdirSync, existsSync } from "node:fs";
import { join } from "node:path";

const ROOT       = process.cwd();
const README     = join(ROOT, "README.md");
const OUT_DIR    = join(ROOT, "assets");
const SOLVED_DIR = process.env.SOLVED_DIR || "프로그래머스";
const WEEKS      = 53;

const CELL = 11, GAP = 3, PITCH = CELL + GAP;
const PAD_L = 30, PAD_T = 22, PAD_B = 26;
const W = PAD_L + WEEKS * PITCH + 6;
const H = PAD_T + 7 * PITCH + PAD_B;

const THEMES = {
  light: { bg: "none", text: "#57606a", scale: ["#ebedf0", "#9be9a8", "#40c463", "#30a14e", "#216e39"] },
  dark:  { bg: "none", text: "#8b949e", scale: ["#161b22", "#0e4429", "#006d32", "#26a641", "#39d353"] },
};

// ── KST 날짜 헬퍼 ─────────────────────────────────────────────────
const KST = 9 * 3600 * 1000;
const dayKey = (ms) => new Date(ms + KST).toISOString().slice(0, 10);
const todayKey = dayKey(Date.now());
const keyToUTC = (k) => Date.parse(k + "T00:00:00Z");

// ── 풀이 커밋 날짜 수집 ───────────────────────────────────────────

// ── 격자 만들기 (마지막 열이 오늘이 든 주) ────────────────────────
function buildGrid(counts) {
  const todayUTC = keyToUTC(todayKey);
  const dow = new Date(todayUTC).getUTCDay();              // 0=일
  const lastSunday = todayUTC - dow * 86400000;
  const start = lastSunday - (WEEKS - 1) * 7 * 86400000;

  const cols = [];
  for (let w = 0; w < WEEKS; w++) {
    const col = [];
    for (let d = 0; d < 7; d++) {
      const ms = start + (w * 7 + d) * 86400000;
      const key = new Date(ms).toISOString().slice(0, 10);
      col.push(key > todayKey ? null : { key, n: counts.get(key) || 0 });
    }
    cols.push(col);
  }
  return { cols, start };
}

const bucket = (n) => (n === 0 ? 0 : n === 1 ? 1 : n <= 3 ? 2 : n <= 6 ? 3 : 4);

// ── 연속 기록 계산 ────────────────────────────────────────────────
function streaks(counts) {
  const days = [...counts.keys()].sort();
  if (days.length === 0) return { total: 0, active: 0, cur: 0, max: 0 };
  const total = [...counts.values()].reduce((a, b) => a + b, 0);
  const set = new Set(days);

  let max = 0, run = 0;
  for (let t = keyToUTC(days[0]); t <= keyToUTC(todayKey); t += 86400000) {
    const k = new Date(t).toISOString().slice(0, 10);
    run = set.has(k) ? run + 1 : 0;
    if (run > max) max = run;
  }
  // 현재 연속: 오늘부터 거꾸로 (오늘 아직 안 풀었으면 어제부터 인정)
  let cur = 0;
  let t = keyToUTC(todayKey);
  if (!set.has(todayKey)) t -= 86400000;
  while (set.has(new Date(t).toISOString().slice(0, 10))) { cur++; t -= 86400000; }

  return { total, active: days.length, cur, max };
}

// ── SVG 그리기 ────────────────────────────────────────────────────
const esc = (s) => String(s).replace(/&/g, "&amp;").replace(/</g, "&lt;").replace(/>/g, "&gt;");
const MONTHS = ["1월","2월","3월","4월","5월","6월","7월","8월","9월","10월","11월","12월"];

function renderSVG(grid, st, theme) {
  const T = THEMES[theme];
  const parts = [];

  parts.push(
    `<svg xmlns="http://www.w3.org/2000/svg" width="${W}" height="${H}" viewBox="0 0 ${W} ${H}" role="img" aria-label="풀이 잔디">`,
    `<style>text{font:10px -apple-system,BlinkMacSystemFont,"Segoe UI","Malgun Gothic",sans-serif;fill:${T.text}}</style>`
  );

  // 월 라벨
  let lastMonth = -1;
  grid.cols.forEach((col, w) => {
    const first = col.find((c) => c);
    if (!first) return;
    const d = new Date(keyToUTC(first.key));
    if (d.getUTCDate() <= 7 && d.getUTCMonth() !== lastMonth) {
      lastMonth = d.getUTCMonth();
      parts.push(`<text x="${PAD_L + w * PITCH}" y="${PAD_T - 8}">${MONTHS[lastMonth]}</text>`);
    }
  });

  // 요일 라벨 (월/수/금)
  [[1, "월"], [3, "수"], [5, "금"]].forEach(([d, label]) => {
    parts.push(`<text x="0" y="${PAD_T + d * PITCH + CELL - 1}">${label}</text>`);
  });

  // 셀
  grid.cols.forEach((col, w) => {
    col.forEach((cell, d) => {
      if (!cell) return;
      const x = PAD_L + w * PITCH;
      const y = PAD_T + d * PITCH;
      const fill = T.scale[bucket(cell.n)];
      const title = cell.n === 0 ? `${cell.key} · 없음` : `${cell.key} · 풀이 ${cell.n}회`;
      parts.push(
        `<rect x="${x}" y="${y}" width="${CELL}" height="${CELL}" rx="2" ry="2" fill="${fill}">` +
        `<title>${esc(title)}</title></rect>`
      );
    });
  });

  // 하단: 요약 + 범례
  const summary = st.total === 0
    ? "아직 기록 없음"
    : `풀이 ${st.total}회 · ${st.active}일 · 현재 ${st.cur}일 연속 · 최장 ${st.max}일`;
  parts.push(`<text x="0" y="${H - 8}">${esc(summary)}</text>`);

  const legendX = W - 6 - (5 * PITCH + 46);
  parts.push(`<text x="${legendX}" y="${H - 8}">적게</text>`);
  T.scale.forEach((c, i) => {
    parts.push(
      `<rect x="${legendX + 26 + i * PITCH}" y="${H - 17}" width="${CELL}" height="${CELL}" rx="2" ry="2" fill="${c}"/>`
    );
  });
  parts.push(`<text x="${legendX + 26 + 5 * PITCH + 3}" y="${H - 8}">많이</text>`);

  parts.push("</svg>");
  return parts.join("");
}

// ── README STREAK 블록 갱신 ───────────────────────────────────────

// ── main ──────────────────────────────────────────────────────────
const counts = commitCounts();
const grid = buildGrid(counts);
const st = streaks(counts);

mkdirSync(OUT_DIR, { recursive: true });
for (const theme of ["light", "dark"]) {
  writeFileSync(join(OUT_DIR, `grass-${theme}.svg`), renderSVG(grid, st, theme));
}

if (existsSync(README)) {
  const line = st.total === 0
    ? "`아직 기록 없음` — 첫 풀이가 올라오면 여기부터 채워진다."
    : `\`현재 ${st.cur}일 연속\` · \`최장 ${st.max}일\` · \`활동 ${st.active}일\` · \`풀이 커밋 ${st.total}회\``;
  writeFileSync(README, replaceBlock(readFileSync(README, "utf8"), "STREAK", line));
}

console.log(`잔디 갱신 · ${JSON.stringify(st)}`);

// README STREAK 블록 교체. 마커가 없으면 그냥 원본을 돌려준다.
function replaceBlock(md, name, body) {
  const open  = "<!-- " + name + ":START -->";
  const close = "<!-- " + name + ":END -->";
  const i = md.indexOf(open);
  const j = md.indexOf(close, i + open.length);
  if (i < 0 || j < 0) return md;
  return md.slice(0, i + open.length) + "\n" + body + "\n" + md.slice(j);
}

// 풀이 커밋만 세기.
// 프로그래머스/<레벨>/<문제>/<파일> 처럼 4단계 이상인 경로가 들어간 커밋만 인정한다.
// 그래야 폴더 안내용 README 같은 잡파일 커밋이 잔디를 채우지 않는다.
function commitCounts() {
  const counts = new Map();
  let raw = "";
  try {
    raw = execFileSync(
      "git",
      ["-c", "core.quotepath=false", "log", "--pretty=format:@%ct", "--name-only", "--", SOLVED_DIR],
      { cwd: ROOT, encoding: "utf8", maxBuffer: 1 << 26 }
    );
  } catch {
    return counts; // 히스토리가 없는 새 저장소
  }

  let day = null;
  let isSolution = false;
  const flush = () => {
    if (day && isSolution) counts.set(day, (counts.get(day) || 0) + 1);
  };

  for (const line of raw.split("\n")) {
    const s = line.trim();
    if (s.startsWith("@")) {
      flush();
      const ts = Number(s.slice(1));
      day = Number.isFinite(ts) && ts > 0 ? dayKey(ts * 1000) : null;
      isSolution = false;
      continue;
    }
    if (!s) continue;
    const parts = s.split("/");
    if (parts[0] === SOLVED_DIR && parts.length >= 4) isSolution = true;
  }
  flush();

  return counts;
}
